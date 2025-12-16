#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ranges>

using namespace std;

class Solution
{
private:
    int getNumRolls(vector<vector<bool>> grid)
    {
        const vector<pair<int, int>> DIRECTIONS = {
            pair(-1, -1),
            pair(-1, 0),
            pair(-1, 1),
            pair(0, -1),
            pair(0, 1),
            pair(1, -1),
            pair(1, 0),
            pair(1, 1),
        };
        const size_t NUM_ROWS = grid.size();
        const size_t NUM_COLS = grid[0].size();

        int ans = 0;

        for (size_t r = 0; r < NUM_ROWS; r++)
        {
            for (size_t c = 0; c < NUM_COLS; c++)
            {
                if (grid[r][c])
                {
                    int num_rolls = 0;

                    // Check adjacent cells
                    for (auto &&d : DIRECTIONS)
                    {
                        int dr = d.first;
                        int dc = d.second;

                        int new_row = r + dr;
                        int new_col = c + dc;

                        if (0 <= new_row && new_row < NUM_ROWS && 0 <= new_col && new_col < NUM_COLS && grid[new_row][new_col])
                            num_rolls++;
                    }

                    if (num_rolls < 4)
                        ans++;
                }
            }
        }

        return ans;
    }

public:
    int
    solve(ifstream &file)
    {
        string line;
        vector<vector<bool>> grid; // Paper locations

        while (file >> line)
        {
            // Convert string into gridrow
            vector<bool> row;
            row.reserve(line.size());

            for (auto &&c : line)
            {
                row.push_back(c == '@');
            }

            grid.push_back(row);
        }

        return getNumRolls(grid);
    }

    void test()
    {
        ifstream testfile("day_4/mock.txt");
        const int ANSWER = 13;
        int result = solve(testfile);

        cout << "Your result for the test case was: " << result << endl;
        cout << "The correct answer is: " << ANSWER << endl;
        assert(result == ANSWER && "Test case not passed");

        testfile.close();
    }

    int run()
    {
        ifstream infile("day_4/input.txt");

        int ans = solve(infile);

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