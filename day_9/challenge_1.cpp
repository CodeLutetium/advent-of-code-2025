#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ranges>
#include <limits>
#include <sstream>

using namespace std;

class Solution
{
private:
public:
    // Brute force method: store all points and compare them
    int64_t solve(ifstream &file)
    {
        string line;
        vector<pair<int64_t, int64_t>> points;
        points.reserve(500);

        while (getline(file, line))
        {
            stringstream ss(line);
            string coordinate_str;

            getline(ss, coordinate_str, ',');
            int64_t x = stol(coordinate_str);
            getline(ss, coordinate_str, ',');
            int64_t y = stol(coordinate_str);

            points.push_back(pair(x, y));
        }

        file.close();

        int64_t max_area = 0;

        for (size_t i = 0; i < points.size() - 1; i++)
        {
            for (size_t j = i + 1; j < points.size(); j++)
            {
                int64_t area = (abs(points[i].first - points[j].first) + 1) * (abs(points[i].second - points[j].second) + 1);
                max_area = max(area, max_area);
            }
        }

        return max_area;
    }

    void test()
    {
        ifstream testfile("day_9/mock.txt");
        const int ANSWER = 50;
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