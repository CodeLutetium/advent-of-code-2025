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
    // Utility function to print elements in vector
    void printv(vector<long> v)
    {
        for (auto &&i : v)
        {
            cout << i << ',';
        }
        cout << endl;
    }

    void mergeIntervals(vector<pair<long, long>> &intervals)
    {
        sort(intervals.begin(), intervals.end(), [](const auto &a, const auto &b)
             { return a.first < b.first; });

        // Merge prev and curr if curr.start <= prev.end
        for (size_t i = 1; i < intervals.size();)
        {
            if (intervals[i].first <= intervals[i - 1].second)
            {
                intervals[i - 1].second = max(intervals[i].second, intervals[i - 1].second);
                intervals.erase(intervals.begin() + i);
            }
            else
            {
                i++;
            }
        }

        // debug: print intervals
        for (auto &&i : intervals)
        {
            cout << i.first << "-" << i.second << endl;
        }
    }

    long getNumFreshIngredients(vector<pair<long, long>> &intervals)
    {
        long ans = 0;

        for (auto &&interval : intervals)
        {
            long num_ids = interval.second - interval.first + 1;
            cout << num_ids << endl;
            ans += interval.second - interval.first + 1;
            // cout << ans << endl;
        }

        return ans;
    }

public:
    long long solve(ifstream &file)
    {
        string line;
        vector<pair<long, long>> intervals;

        // Process intervals
        while (getline(file, line) && line != "")
        {
            // Obtain start and end
            string s_start = line.substr(0, line.find("-"));
            string s_end = line.substr(line.find("-") + 1);
            long start = stol(s_start);
            long end = stol(s_end);

            intervals.push_back(pair(start, end));
        }

        mergeIntervals(intervals);

        return getNumFreshIngredients(intervals);
    }

    void test()
    {
        ifstream testfile("day_5/mock.txt");
        const int ANSWER = 14;
        int result = solve(testfile);

        cout << "Your result for the test case was: " << result << endl;
        cout << "The correct answer is: " << ANSWER << endl;
        assert(result == ANSWER && "Test case not passed");

        testfile.close();
    }

    int run()
    {
        ifstream infile("day_5/input.txt");

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