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
    void printv(vector<int> v)
    {
        for (auto &&i : v)
        {
            cout << i << ',';
        }
        cout << endl;
    }

    long getGrandTotal(vector<vector<int>> &numbers, vector<char> &operators)
    {
        long ans = 0;

        for (size_t i = 0; i < operators.size(); i++)
        {
            long temp = 0; // sub answers to the current problem
            if (operators[i] == '*')
            {
                temp = 1; // Set temp to 1 for multiplication
                for (auto &&row : numbers)
                {
                    temp *= row[i];
                }
            }
            else
            {
                for (auto &&row : numbers)
                {
                    temp += row[i];
                }
            }

            ans += temp;
        }

        return ans;
    }

public:
    long solve(ifstream &file)
    {
        string line;
        vector<vector<int>> numbers;
        vector<char> operators;

        while (getline(file, line) && line.find('+') == string::npos && line.find('*') == string::npos)
        {
            vector<int> row;
            int curr = 0; // Current number that we are processing
            size_t i = 0;

            // Advance to the first digit
            for (; line[i] == ' '; i++)
                ;

            // Process the line
            while (i < line.size())
            {
                if (line[i] == ' ')
                {
                    // End of the digit
                    row.push_back(curr);
                    curr = 0;

                    // Advance to the next digit
                    for (; i < line.size() && line[i] == ' '; i++)
                        ;
                }
                else
                {
                    curr *= 10;
                    curr += line[i] - '0';
                    i++;
                }
            }

            // Flush the last number
            if (curr > 0)
                row.push_back(curr);

            numbers.push_back(row);
        }

        // Debug: print numbers
        // for (auto &&row : numbers)
        // {
        //     for (auto &&n : row)
        //     {
        //         cout << n << ',';
        //     }
        //     cout << endl;
        // }

        // Process operators. Operators should be in line already due to above while loop
        for (size_t i = 0; i < line.size(); i++)
        {
            // Advance to next operator
            for (; i < line.size() && line[i] == ' '; i++)
                ;

            if (i < line.size())
                operators.push_back(line[i]);
        }

        // for (auto &&i : operators)
        // {
        //     cout << i << ",";
        // }
        // cout << endl;

        return getGrandTotal(numbers, operators);
    }

    void test()
    {
        ifstream testfile("day_6/mock.txt");
        const int ANSWER = 4277556;
        int result = solve(testfile);

        cout << "Your result for the test case was: " << result << endl;
        cout << "The correct answer is: " << ANSWER << endl;
        assert(result == ANSWER && "Test case not passed");

        testfile.close();
    }

    int run()
    {
        ifstream infile("day_6/input.txt");

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