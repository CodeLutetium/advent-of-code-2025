#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>

using namespace std;

class Solution
{

private:
    int getNumDigits(long n)
    {
        return n > 0 ? (int)log10l(n) + 1 : 1;
    }

    bool isValidId(long digits)
    {
        // Single digits always valid
        if (digits < 10)
            return true;

        // Convert digits to string
        string dstring = to_string(digits);

        // Generate a list of divisors
        vector<int> divisors;
        for (size_t i = dstring.size() / 2; i > 0; i--)
        {
            if (dstring.size() % i == 0)
                divisors.push_back(i);
        }

        // Check if there are repeated digits in the pairs
        for (auto &&length : divisors)
        {
            string substring = dstring.substr(0, length);
            bool flag = false; // flip to true if substring does not match
            for (size_t i = length; i < dstring.size(); i += length)
            {
                // No match
                if (dstring.substr(i, length) != substring)
                {
                    flag = true;
                    continue;
                }
            }

            if (!flag)
                return flag;
        }

        return true;
    }

public:
    int run()
    {
        ifstream infile("day_2/input.txt");
        // ifstream infile("day_2/mock.txt");

        long ans = 0;

        string line;
        getline(infile, line);

        stringstream ss(line);
        const char delimiter = ',';
        string range; // current range we are dealing with

        while (getline(ss, range, delimiter))
        {
            string lower_str = range.substr(0, range.find('-'));
            string upper_str = range.substr(range.find('-') + 1);

            long lower = stol(lower_str);
            long upper = stol(upper_str);

            for (long i = lower; i <= upper; i++)
            {
                if (!isValidId(i))
                {
                    ans += i;
                }
            }
        }

        cout << "The answer is: " << ans << endl;

        infile.close();

        return 0;
    }
};

int main()
{
    Solution challenge2;
    return challenge2.run();
}