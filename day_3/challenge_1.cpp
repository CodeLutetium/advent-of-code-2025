#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

class Solution
{
private:
    long getMaxJoltage(vector<int> batteries)
    {
        // Look for index of largest two numbers
        int max_l = batteries[0], max_r = batteries[1];

        if (batteries.size() == 2)
            return max_l * 10 + max_r;

        for (size_t i = 2; i < batteries.size(); i++)
        {
            int curr = batteries[i]; // Joltage of current battery
            if (curr > max_r)
            {
                // Set left digit to old right digit if old right is larger
                if (max_r > max_l)
                    max_l = max_r;
                max_r = curr;
            }
            else
            {
                if (max_r > max_l)
                {
                    max_l = max_r;
                    max_r = curr;
                }
            }
        }

        // [l][r] = l * 10 + r
        cout << max_l * 10 + max_r << endl;
        return max_l * 10 + max_r;
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

            for (auto &&i : batteries)
            {
                cout << i << ' ';
            }
            cout << endl;
            ans += getMaxJoltage(batteries);
        }
        return ans;
    }

    void test()
    {
        ifstream testfile("day_3/mock.txt");
        const long ANSWER = 357;
        // cout << solve(testfile) << endl;
        assert(solve(testfile) == ANSWER && "Test case not passed");

        testfile.close();
    }

    int run()
    {
        ifstream infile("day_3/input.txt");

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