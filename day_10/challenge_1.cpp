#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ranges>
#include <sstream>
#include <cstdint>

class Solution
{
private:
    // Solve the problem recursively using dfs
    // Intuition: we either press or dont press the button, if you press 2x it has no effect.
    int32_t dfs(int32_t num_presses, int32_t endstate, int32_t state, std::vector<int32_t> &buttons, int32_t i)
    {
        if (state == endstate)
            return num_presses;

        if (i >= buttons.size())
            return INT32_MAX; // No solution found

        return std::min(
            dfs(num_presses + 1, endstate, state ^ buttons[i], buttons, i + 1),
            dfs(num_presses, endstate, state, buttons, i + 1));
    }

public:
    int64_t solve(std::ifstream &file)
    {
        std::string line;
        int64_t ans = 0;

        while (getline(file, line))
        {
            std::stringstream ss(line);
            // Get end state
            std::string buffer;
            getline(ss, buffer, ' ');
            buffer = buffer.substr(1, buffer.size() - 2);

            // Convert endstate to integer
            int32_t endstate = 0;
            size_t endstate_sz = buffer.size();
            for (auto &&state : buffer)
            {
                endstate = endstate << 1;
                if (state == '#')
                    endstate += 1;
            }

            std::vector<int32_t> buttons;

            while (getline(ss, buffer, ' '))
            {
                // Check if it is enclosed in round brackets
                if (buffer[0] == '(')
                {
                    buffer = buffer.substr(1, buffer.size() - 2);
                    std::stringstream btn_ss(buffer);
                    std::string btn_str;
                    int32_t button = 0;

                    while (getline(btn_ss, btn_str, ','))
                    {
                        int32_t light = std::stoi(btn_str);
                        button += 1 << (endstate_sz - light - 1);
                    }

                    buttons.push_back(button);
                }
            }

            ans += dfs(0, endstate, 0, buttons, 0);
        }
        file.close();

        return ans;
    }

    void test()
    {
        std::ifstream testfile("day_10/mock.txt");
        const int ANSWER = 7;
        int result = solve(testfile);

        std::cout << "Your result for the test case was: " << result << std::endl;
        std::cout << "The correct answer is: " << ANSWER << std::endl;
        assert(result == ANSWER && "Test case not passed");
    }

    int run()
    {
        std::ifstream infile("day_10/input.txt");

        int64_t ans = solve(infile);

        std::cout << "The answer is: " << ans << std::endl;

        return 0;
    }
};

int main()
{
    Solution challenge;
    challenge.test();
    return challenge.run();
}