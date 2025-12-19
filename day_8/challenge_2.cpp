#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <ranges>
#include <sstream>
#include <queue>
#include <unordered_set>

using namespace std;

class Compare
{
public:
    // Operator for min heap
    bool operator()(pair<double, pair<size_t, size_t>> &a, pair<double, pair<size_t, size_t>> &b)
    {
        return a.first > b.first;
    }
};

// Weighted Quick Union with Path Compression (WQUPC) implementation
// Source: SC2101 Week 7 notes
class UnionFind
{
    vector<size_t> parents;
    vector<size_t> sizes;        // number of elements in tree rooted at i
    unordered_set<size_t> roots; // unique groups

private:
public:
    UnionFind(size_t size)
    {
        parents.resize(size);
        sizes.resize(size);

        // Initialize each member with itself as its parent
        for (size_t i = 0; i < size; i++)
        {
            parents[i] = i;
            sizes[i] = 1;
            roots.insert(i);
        }
    }

    void print_sizes()
    {
        for (auto &&i : sizes)
        {
            cout << i << ',';
        }
        cout << endl;
    }

    void print_parents()
    {
        for (auto &&i : parents)
        {
            cout << i << ',';
        }
        cout << endl;
    }

    // Look for root of i
    size_t find(size_t i)
    {
        while (parents[i] != i)
        {
            parents[i] = parents[parents[i]]; // path compression
            if (roots.contains(i))
                roots.erase(i);

            i = parents[i];
        }

        return i;
    }

    // Check if i and j are connected
    bool connected(size_t i, size_t j)
    {
        return find(i) == find(j);
    }

    // Union two indexes
    void merge_sets(size_t a, size_t b)
    {
        // Look for root
        size_t i = find(a);
        size_t j = find(b);

        if (i == j)
            return;

        if (sizes[i] > sizes[j])
        {
            // i has a larger tree, make j the subtree
            sizes[i] += sizes[j];
            parents[j] = i;
            roots.erase(j);
        }
        else
        {
            // j has a larger tree, make i the subtree
            sizes[j] += sizes[i];
            parents[i] = j;
            roots.erase(i);
        }
    }

    // Returns true when all junction boxes are connected
    bool is_single_group()
    {
        return roots.size() == 1;
    }
};

class Solution
{
private:
    void printv(vector<int64_t> &v)
    {
        for (auto &&i : v)
        {
            cout << i << ',';
        }
        cout << endl;
    }

    // Calculate euclidean distance between two coordinates (without sqrt)
    double get_distance(vector<int64_t> a, vector<int64_t> b)
    {
        int64_t distance = 0;
        for (size_t i = 0; i < 3; i++)
        {
            int64_t diff = a[i] - b[i];
            distance += diff * diff;
        }

        return distance;
    }

    int64_t
    connect(vector<vector<int64_t>> &boxes)
    {
        const int64_t NUM_BOXES = boxes.size();
        const int64_t N_LARGEST_CIRCUITS = 3;

        // Max heap of distance, idx 1, idx 2 of the two coordinates.
        // Stores only num_connections connections in max_heap.
        // This implementation reduced memory consumption from 19.0 MB (0.253s) to 172.6 kB (0.604s) (heaptrack)
        priority_queue<pair<double, pair<size_t, size_t>>, vector<pair<double, pair<size_t, size_t>>>, Compare>
            heap;

        // Add coordinates into heap, ordered by their distance
        for (size_t i = 0; i < NUM_BOXES - 1; i++)
        {
            for (size_t j = i + 1; j < NUM_BOXES; j++)
            {
                heap.push(pair(get_distance(boxes[i], boxes[j]), pair(i, j)));
            }
        }

        UnionFind connections(NUM_BOXES);

        pair<size_t, size_t> *last_coordinates;

        while (!connections.is_single_group())
        {
            pair<int64_t, pair<size_t, size_t>> top = heap.top();
            // cout << top.first << " - " << top.second.first << "," << top.second.second << endl;
            connections.merge_sets(top.second.first, top.second.second);

            last_coordinates = &top.second;
            heap.pop();
        }
        // connections.print_parents();
        // connections.print_sizes();

        return boxes[last_coordinates->first][0] * boxes[last_coordinates->second][0];
    }

public:
    int64_t solve(ifstream &file)
    {
        string line;
        vector<vector<int64_t>> boxes; // Coordinates of junction boxes
        boxes.reserve(1000);

        while (getline(file, line))
        {
            vector<int64_t> coordinates;
            coordinates.reserve(3);

            stringstream ss(line);
            string coordinate; // x/y/z coordinate

            while (getline(ss, coordinate, ','))
            {
                coordinates.push_back(stoi(coordinate));
            }

            boxes.push_back(coordinates);
        }

        file.close();

        return connect(boxes);
    }

    void test()
    {
        ifstream testfile("day_8/mock.txt");
        const int64_t ANSWER = 25272;
        int64_t result = solve(testfile);

        cout << "Your result for the test case was: " << result << endl;
        cout << "The correct answer is: " << ANSWER << endl;
        assert(result == ANSWER && "Test case not passed");
    }

    int run()
    {
        ifstream infile("day_8/input.txt");

        int64_t ans = solve(infile);

        cout << "The answer is: " << ans << endl;

        return 0;
    }
};

int main()
{
    Solution challenge;
    challenge.test();
    return challenge.run();
}