#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream infile("day_1/input.txt");
    // ifstream infile("day_1/mock.txt");

    // Left and right limits of the safe
    const int LEFT_LIMIT = 0;
    const int RIGHT_LIMIT = 99;
    const int INITIAL_POSITION = 50;

    int position = INITIAL_POSITION;
    int ans = 0;
    string line;

    while (infile >> line)
    {
        const int clicks = stoi(line.substr(1, line.size()));
        ans += clicks / 100; // add number of rotations

        const int mod_val = clicks % 100;
        const int old_position = position;

        if (line[0] == 'L')
        {
            // Rotate leftwards
            position -= mod_val;
            if (position < LEFT_LIMIT)
            {
                position += 100;

                if (old_position != LEFT_LIMIT)
                    ans++;
            }

            if (position == LEFT_LIMIT)
                ans++;
        }
        else
        {
            // Rotate rightwards
            position += mod_val;
            if (position > RIGHT_LIMIT)
            {
                position -= 100;
                ans++;
            }
        }
        cout << position << endl;

        // cout << position << endl;
        line = ""; // Reset string
    }

    cout << "Answer is " << ans << endl;

    infile.close();
    return 0;
}