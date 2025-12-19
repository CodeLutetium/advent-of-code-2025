#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <ranges>
#include <sstream>
#include <queue>

using namespace std;

class Compare
{
public:
    // Operator for max heap
    bool operator()(pair<double, pair<size_t, size_t>> &a, pair<double, pair<size_t, size_t>> &b)
    {
        return a.first < b.first;
    }
};

// Weighted Quick Union with Path Compression (WQUPC) implementation
// Source: SC2101 Week 7 notes
class UnionFind
{
    vector<size_t> parents;
    vector<size_t> sizes; // number of elements in tree rooted at i

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
        }
        else
        {
            // j has a larger tree, make i the subtree
            sizes[j] += sizes[i];
            parents[i] = j;
        }
    }

    // Multiply size of n largest circuits
    int64_t nlargest_mul(size_t n)
    {
        int64_t ans = 1;
        priority_queue<size_t, vector<size_t>, greater<size_t>> heap; // min heap containing n largest circuits

        for (size_t i = 0; i < parents.size(); i++)
        {
            // This is the root
            if (parents[i] == i)
            {
                heap.push(sizes[i]);
                ans *= sizes[i];
            }

            // Check if heap exceeds size
            while (heap.size() > n)
            {
                ans /= heap.top();
                heap.pop();
            }
        }

        return ans;
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
    connect(vector<vector<int64_t>> &boxes, size_t num_connections)
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

                for (; heap.size() > num_connections; heap.pop())
                    ;
            }
        }

        UnionFind connections(NUM_BOXES);

        while (!heap.empty())
        {
            pair<int64_t, pair<size_t, size_t>> top = heap.top();
            // cout << top.first << " - " << top.second.first << "," << top.second.second << endl;
            connections.merge_sets(top.second.first, top.second.second);

            heap.pop();
        }
        // connections.print_parents();
        // connections.print_sizes();

        return connections.nlargest_mul(N_LARGEST_CIRCUITS);
    }

public:
    int64_t solve(ifstream &file, size_t num_connections)
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

        return connect(boxes, num_connections);
    }

    void test()
    {
        ifstream testfile("day_8/mock.txt");
        const int64_t ANSWER = 40;
        int64_t result = solve(testfile, 10);

        cout << "Your result for the test case was: " << result << endl;
        cout << "The correct answer is: " << ANSWER << endl;
        assert(result == ANSWER && "Test case not passed");
    }

    int run()
    {
        ifstream infile("day_8/input.txt");

        int64_t ans = solve(infile, 1000);

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