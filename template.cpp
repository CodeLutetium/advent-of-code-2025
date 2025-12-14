#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream infile("input.txt");

    string line;
    getline(infile, line);

    int ans = 0;

    cout << "The answer is: " << ans << endl;

    infile.close();

    return 0;
}