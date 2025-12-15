#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

class Solution
{
private:
public:
    int solve(ifstream &file)
    {
        string line;
        getline(file, line);

        return 0;
    }

    void test()
    {
        ifstream testfile("day_X/mock.txt");
        const int ANSWER = 0;

        assert(solve(testfile) == ANSWER && "Test case not passed");

        testfile.close();
    }

    int run()
    {
        ifstream infile("day_X/input.txt");

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