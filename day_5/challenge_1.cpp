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

    // Binary search to check if target is in list of intervals
    // O(log n) time complexity, use this.
    bool bsearch(vector<pair<long, long>> &intervals, long target)
    {
        size_t left = 0;
        size_t right = intervals.size() - 1;

        // Optimization: completely out of range
        if (target < intervals[left].first || target > intervals[right].second)
            return false;

        while (left >= 0 && right < intervals.size() && left <= right)
        {
            size_t mid = left + (right - left) / 2;
            pair<long, long> interval = intervals[mid];

            // Success: target is in the interval (inclusive of start and end)
            if (target >= interval.first && target <= interval.second)
                return true;

            if (target < interval.first)
            {
                // Target is on the left
                right = mid - 1;
            }
            else
            {
                // Target is on the right
                left = mid + 1;
            }
        }

        return false;
    }

    // O(N) time complexity, used for sanity check to make sure bsearch is implemented correctly.
    bool linsearch(vector<pair<long, long>> &intervals, long target)
    {
        for (auto &&interval : intervals)
        {
            if (target >= interval.first && target <= interval.second)
                return true;
        }
        return false;
    }

    void mergeIntervals(vector<pair<long, long>> &intervals)
    {
        sort(intervals.begin(), intervals.end(), [](const auto &a, const auto &b)
             { return a.first < b.first; });

        // Merge prev and curr if curr.start <= prev.end
        for (size_t i = 1; i < intervals.size();)
        {
            if (intervals[i].first <= intervals[i - 1].second - 1)
            {
                intervals[i - 1].second = intervals[i].second;
                intervals.erase(intervals.begin() + i);
            }
            else
            {
                i++;
            }
        }

        // debug: print intervals
        // for (auto &&i : intervals)
        // {
        //     cout << i.first << "-" << i.second << endl;
        // }
    }

    int getNumFreshIngredients(vector<pair<long, long>> &intervals, vector<long> &ids)
    {
        int ans = 0;

        for (auto &&id : ids)
        {
            if (bsearch(intervals, id))
            {
                ans++;
            }
        }

        return ans;
    }

public:
    int solve(ifstream &file)
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

        // Process the ingredient IDs after the whitespace
        vector<long> ids;
        while (file >> line)
        {
            ids.push_back(stol(line));
        }

        return getNumFreshIngredients(intervals, ids);
    }

    void test()
    {
        ifstream testfile("day_5/mock.txt");
        const int ANSWER = 3;
        int result = solve(testfile);

        cout << "Your result for the test case was: " << result << endl;
        cout << "The correct answer is: " << ANSWER << endl;
        assert(result == ANSWER && "Test case not passed");

        testfile.close();
    }

    int run()
    {
        ifstream infile("day_5/input.txt");

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