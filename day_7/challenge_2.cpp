#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ranges>
#include <unordered_set>

using namespace std;

class Solution
{
private:
    const char STARTING_CHAR = 'S';
    const char EMPTY_CHAR = '.';
    const char BEAM_CHAR = '|';
    const char SPLITTER_CHAR = '^';

    void printv(vector<int> &v)
    {
        for (auto &&i : v)
        {
            cout << i << ",";
        }
        cout << endl;
    }

    long dp(vector<string> &grid, int start)
    {
        vector<long> dp(grid[0].size());
        dp[start]++;

        for (auto &&row : grid)
        {
            for (size_t i = 0; i < row.size(); i++)
            {
                if (row[i] == SPLITTER_CHAR)
                {
                    dp[i - 1] += dp[i];
                    dp[i + 1] += dp[i];
                    dp[i] = 0;
                }
            }
            // printv(dp);
        }

        long ans = 0;
        for (auto &&i : dp)
        {
            ans += i;
        }
        return ans;
    }

public:
    long solve(ifstream &file)
    {
        string line;
        vector<string> grid;

        while (getline(file, line))
        {
            grid.push_back(line);
        }

        // Get column of starting position
        size_t start = grid[0].find(STARTING_CHAR);

        // return dfs(grid, 1, start);
        return dp(grid, start);
    }

    void test()
    {
        ifstream testfile("day_7/mock.txt");
        const int ANSWER = 40;
        int result = solve(testfile);

        cout << "Your result for the test case was: " << result << endl;
        cout << "The correct answer is: " << ANSWER << endl;
        assert(result == ANSWER && "Test case not passed");

        testfile.close();
    }

    int run()
    {
        ifstream infile("day_7/input.txt");

        long ans = solve(infile);

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