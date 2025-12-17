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

    long getGrandTotal(vector<string> &numbers, string &operators)
    {

        long ans = 0;
        vector<int> operands;
        operands.reserve(numbers.size()); // number of rows in numbers == number of operands

        for (int i = numbers[0].size() - 1; i >= 0; i--)
        {
            // Get the number
            int number = 0;
            for (size_t j = 0; j < numbers.size(); j++)
            {
                if (numbers[j][i] != ' ')
                {
                    number *= 10;
                    number += numbers[j][i] - '0';
                }
            }

            if (number > 0)
                operands.push_back(number);

            // Process operands if operators[i] is an operator
            if (operators[i] == '*')
            {
                long temp = 1;
                for (auto &&num : operands)
                {
                    temp *= num;
                }
                ans += temp;
                operands.clear();
            }
            else if (operators[i] == '+')
            {
                long temp = 0;
                for (auto &&num : operands)
                {
                    temp += num;
                }
                ans += temp;
                operands.clear();
            }
        }

        return ans;
    }

public:
    long solve(ifstream &file)
    {
        string line;

        vector<string> numbers;
        string operators;

        // Greedily load all lines into memory except the last line
        while (getline(file, line) && line.find('+') == string::npos && line.find('*') == string::npos)
        {
            numbers.push_back(line);
        }

        operators = line;

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
        const int ANSWER = 3263827;
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