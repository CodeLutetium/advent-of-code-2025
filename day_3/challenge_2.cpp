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
    const int NUM_LARGEST = 12;

    void printv(vector<size_t> v)
    {
        for (auto &&i : v)
        {
            cout << i << ',';
        }
        cout << endl;
    }

    long getMaxJoltage(vector<int> batteries)
    {
        // Indexes of the digits we are going to use
        vector<size_t> indexes;
        indexes.reserve(NUM_LARGEST);
        for (size_t i = batteries.size() - NUM_LARGEST; i < batteries.size(); i++)
        {
            indexes.push_back(i);
        }
        // printv(indexes);

        // We can search the remaining range from [left, right)
        size_t left = 0;

        // For each index, shift left as much possible
        for (size_t i = 0; i < NUM_LARGEST; i++)
        {
            size_t largest_idx = indexes[i];

            // Find greatest digit in the range [left, curr_idx]
            size_t curr = indexes[i];
            while (curr >= left)
            {
                if (batteries[curr] >= batteries[largest_idx])
                {
                    largest_idx = curr;
                }

                if (curr == 0)
                    break;

                curr--;
            }

            // Update the left bound so we dont hit it in the next iteration
            left = largest_idx + 1;

            // Update indexes with newfound largest digit on the left
            indexes[i] = largest_idx;
        }

        long ans = 0;
        for (auto &&i : indexes)
        {
            ans *= 10;
            ans += batteries[i];
        }

        return ans;
    }

public:
    long solve(ifstream &file)
    {
        string line;
        long ans = 0;

        while (file >> line)
        {
            // Convert string into array
            vector<int> batteries;
            batteries.reserve(line.size());

            for (size_t i = 0; i < line.size(); i++)
            {
                batteries.push_back(line[i] - '0');
            }

            ans += getMaxJoltage(batteries);
        }
        return ans;
    }

    void test()
    {
        ifstream testfile("day_3/mock.txt");
        const long ANSWER = 3121910778619;
        long long result = solve(testfile);
        cout << "Your result for the test case was: " << result << endl;
        cout << "The correct answer is: " << ANSWER << endl;
        assert(result == ANSWER && "Test case not passed");

        testfile.close();
    }

    int run()
    {
        ifstream infile("day_3/input.txt");

        long long ans = solve(infile);

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