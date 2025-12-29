#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ranges>

class Solution
{
private:
public:
    int solve(std::ifstream &file)
    {
        std::string line;
        getline(file, line);

        return 0;
    }

    void test()
    {
        std::ifstream testfile("day_10/mock.txt");
        const int ANSWER = 0;
        int result = solve(testfile);

        std::cout << "Your result for the test case was: " << result << std::endl;
        std::cout << "The correct answer is: " << ANSWER << std::endl;
        assert(result == ANSWER && "Test case not passed");

        testfile.close();
    }

    int run()
    {
        std::ifstream infile("day_10/input.txt");

        int ans = solve(infile);

        std::cout << "The answer is: " << ans << std::endl;

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