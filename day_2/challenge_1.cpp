#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

int getNumDigits(long n)
{
    return n > 0 ? (int)log10l(n) + 1 : 1;
}

int main()
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

        // Optimization: skip if range is guaranteed to have no mirrors
        if (lower_str.size() == upper_str.size() && lower_str.size() % 2 != 0 && upper_str.size() % 2 != 0)
            continue;

        long lower = stol(lower_str);
        long upper = stol(upper_str);

        // Calculate current, the number we will start checking from
        int num_digits_lower = lower_str.size();
        int mirror_length = (int)(num_digits_lower + 1) / 2; // Perform ceiling division
        long current_half = lower / (long)pow(10, mirror_length);
        long current = current_half * (long)pow(10, mirror_length) + current_half;

        // cout << current << " has " << getNumDigits(current) << " digits" << endl;
        while (current <= upper)
        {
            // Check if current number is a mirror.
            if (getNumDigits(current) % 2 == 0 && current >= lower)
                ans += current;

            // Increment current
            current_half += 1;
            current = current_half * (long)pow(10, mirror_length) + current_half;
        }
    }

    cout << "The answer is: " << ans << endl;

    infile.close();

    return 0;
}