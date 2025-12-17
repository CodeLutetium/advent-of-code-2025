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

    void printv(unordered_set<int> &v)
    {
        for (auto &&i : v)
        {
            cout << i << ",";
        }
        cout << endl;
    }

    int numSplits(vector<string> &grid)
    {
        // Indexes of all the beams
        unordered_set<int> beams;
        int ans = 0;

        // Locate the starting position
        beams.insert(grid[0].find(STARTING_CHAR));

        for (size_t row = 1; row < grid.size(); row++)
        {
            unordered_set<int> beamcpy = beams;

            for (auto &&beam : beamcpy)
            {
                // Base case: No splitting
                if (grid[row][beam] == EMPTY_CHAR)
                {
                    grid[row][beam] = BEAM_CHAR;
                }
                // Splitter reached
                else if (grid[row][beam] == SPLITTER_CHAR)
                {
                    // Add neighbouring indexes to beams
                    beams.erase(beam);
                    beams.insert(beam + 1);
                    beams.insert(beam - 1);

                    grid[row][beam + 1] = BEAM_CHAR;
                    grid[row][beam - 1] = BEAM_CHAR;
                    ans++;
                }
            }
        }

        // Print out the grid
        for (auto &&row : grid)
        {
            cout << row << endl;
        }

        return ans;
    }

public:
    int solve(ifstream &file)
    {
        string line;
        vector<string> grid;

        while (getline(file, line))
        {
            grid.push_back(line);
        }

        return numSplits(grid);
    }

    void test()
    {
        ifstream testfile("day_7/mock.txt");
        const int ANSWER = 21;
        int result = solve(testfile);

        cout << "Your result for the test case was: " << result << endl;
        cout << "The correct answer is: " << ANSWER << endl;
        assert(result == ANSWER && "Test case not passed");

        testfile.close();
    }

    int run()
    {
        ifstream infile("day_7/input.txt");

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