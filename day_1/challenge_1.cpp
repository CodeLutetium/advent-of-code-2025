#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream infile("day_1/input.txt");
    // ifstream infile("day_1/mock.txt");

    // Left and right limits of the safe
    int LEFT_LIMIT = 0;
    int RIGHT_LIMIT = 99;

    int position = 50; // default position of the dial
    int ans = 0;
    string line;

    while (infile >> line) {
        // cout << line << endl;
        int clicks = stoi(line.substr(1, line.size()));
        if (line[0] == 'L') {
            // Rotate leftwards
            position -= clicks;
            while (position < LEFT_LIMIT) {
                position += 100;
            }
        } else {
            // Rotate rightwards
            position += clicks;
            while (position > RIGHT_LIMIT) {
                position -= 100;
            }
        }
        // Check if position is 0.
        if (position == 0) {
            ans++;
        }
        // cout << position << endl;
        line = ""; // Reset string
    }

    cout << "Answer is " << ans << endl;

    infile.close();
    return 0;
}