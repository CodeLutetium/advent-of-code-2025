#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <ranges>
#include <limits>
#include <sstream>

using namespace std;

class Solution
{
    struct Point
    {
        int32_t x;
        int32_t y;

        bool operator==(const Point &other) const
        {
            return x == other.x && y == other.y;
        }

        friend std::ostream &operator<<(std::ostream &outs, const Point &point)
        {
            return outs << point.x << ',' << point.y;
        }

        // hash function
        inline std::size_t operator()(const Point &p) const
        {
            return (p.x * 100000) ^ p.y;
        }
    };

private:
    void draw_line(vector<vector<int32_t>> &grid, Point start, Point end)
    {
        const int32_t startX = min(start.x, end.x);
        const int32_t endX = max(start.x, end.x);
        const int32_t startY = min(start.y, end.y);
        const int32_t endY = max(start.y, end.y);

        if (startX == endX)
        {
            // Points lie parallel to y axis - draw vertical line
            for (size_t i = startY; i <= endY; i++)
            {
                grid[i][startX] = 1;
            }
        }
        else
        {
            // Points lie parallel to x axis - draw horizontal line
            for (size_t i = startX; i <= endX; i++)
            {
                grid[startY][i] = 1;
            }
        }
    }

    // Check if two points are valid (covers entire shape)
    bool is_valid(vector<vector<int32_t>> &grid, Point a, Point b)
    {
        const int32_t startX = min(a.x, b.x);
        const int32_t endX = max(a.x, b.x);
        const int32_t startY = min(a.y, b.y);
        const int32_t endY = max(a.y, b.y);

        for (size_t row = startY; row <= endY; row++)
        {
            for (size_t col = startX; col <= endX; col++)
            {
                if (grid[row][col] == 0)
                    return false;
            }
        }

        return true;
    }

public:
    /**
     * 1. compress coordinates
     * 2. for each pair of coordinates, check if there are any points in the rectangle that are outside the shape (grid[i][j] == 0)
     */
    int64_t solve(ifstream &file)
    {
        string line;
        vector<Point> points;
        points.reserve(500);

        while (getline(file, line))
        {
            stringstream ss(line);
            string coordinate_str;

            getline(ss, coordinate_str, ',');
            int32_t x = stol(coordinate_str);
            getline(ss, coordinate_str, ',');
            int32_t y = stol(coordinate_str);

            points.push_back(Point(x, y));
        }

        file.close();

        // 1. Compress coordinates
        // Create copy for sorting
        vector<Point> ptscpy = points;

        // Compress x axis coordinates
        vector<int32_t> revX;                         // revX[i] retrieves original x coordinate
        unordered_map<int32_t, int32_t> x_compressed; // given uncompressed coordinate, return compressed coordinate
        sort(ptscpy.begin(), ptscpy.end(), [](auto &a, auto &b)
             { return a.x < b.x; });
        auto last = unique(ptscpy.begin(), ptscpy.end());

        size_t num_unique_x = last - ptscpy.begin();
        x_compressed.reserve(num_unique_x);
        for (size_t i = 0; i < num_unique_x; i++)
        {
            revX.push_back(ptscpy[i].x);
            x_compressed[ptscpy[i].x] = i;
        }

        // Compress y axis coordinates
        vector<int32_t> revY;
        unordered_map<int32_t, int32_t> y_compressed;
        sort(ptscpy.begin(), ptscpy.end(), [](auto &a, auto &b)
             { return a.y < b.y; });
        last = unique(ptscpy.begin(), ptscpy.end());

        int num_unique_y = last - ptscpy.begin();
        y_compressed.reserve(num_unique_y);
        for (size_t i = 0; i < num_unique_y; i++)
        {
            revY.push_back(ptscpy[i].y);
            y_compressed[ptscpy[i].y] = i;
        }

        // Compress all points
        vector<Point> pts_compressed;
        unordered_set<Point, Point> pts_set; // store compressed pts in a set to allow for O(1) lookup time
        pts_compressed.reserve(points.size());
        for (auto &&point : points)
        {
            int32_t new_x = x_compressed[point.x];
            int32_t new_y = y_compressed[point.y];
            pts_compressed.push_back(Point(new_x, new_y));
            pts_set.insert(Point(new_x, new_y));
        }

        const size_t MAX_X = revX.size() - 1;
        const size_t MAX_Y = revY.size() - 1;

        // Initialize grid and draw all lines
        vector<vector<int32_t>> grid(revY.size(), vector<int32_t>(revX.size()));

        // Draw the lines
        for (size_t i = 0; i < pts_compressed.size() - 1; i++)
        {
            draw_line(grid, pts_compressed[i], pts_compressed[i + 1]);
        }
        draw_line(grid, pts_compressed[0], pts_compressed[pts_compressed.size() - 1]); // Connect first and last points

        // Fill the grid
        for (auto &&row : grid)
        {
            int32_t is_inside = -1;
            for (auto &&i : row)
            {
                if (i == 1)
                    is_inside *= -1;
                else if (i == 0 && is_inside == 1)
                    i = is_inside;
            }
        }

        // 2. Compare each pair
        int64_t max_area = 0;
        for (size_t i = 0; i < pts_compressed.size() - 1; i++)
        {
            // Since we have already sorted by size, we start the search from opposite ends to hopefully speed things up
            for (size_t j = pts_compressed.size() - 1; j > i; j--)
            {
                if (is_valid(grid, pts_compressed[i], pts_compressed[j]))
                {
                    // Reverse coordinates
                    int32_t x1 = revX[pts_compressed[i].x];
                    int32_t x2 = revX[pts_compressed[j].x];
                    int32_t y1 = revY[pts_compressed[i].y];
                    int32_t y2 = revY[pts_compressed[j].y];
                    // cout << "Valid: " << x1 << ',' << y1 << " and " << x2 << ',' << y2 << endl;

                    int64_t area = (abs(x1 - x2) + 1) * (abs(y1 - y2) + 1);
                    max_area = max(area, max_area);
                }
            }
        }

        return max_area;
    }

    void test()
    {
        ifstream testfile("day_9/mock.txt");
        const int ANSWER = 24;
        int result = solve(testfile);

        cout << "Your result for the test case was: " << result << endl;
        cout << "The correct answer is: " << ANSWER << endl;
        assert(result == ANSWER && "Test case not passed");

        testfile.close();
    }

    int run()
    {
        ifstream infile("day_9/input.txt");

        int64_t ans = solve(infile);

        cout << "The answer is: " << ans << endl;

        infile.close();

        return 0;
    }
};

int main()
{
    Solution challenge;
    challenge.test();
    return challenge.run();
}