#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
using namespace std;
using namespace chrono;

void bucketSort(vector<float> &arr)
{
    int n = arr.size();
    vector<vector<float>> buckets(n);
    for (float val : arr)
    {
        int index = n * val;
        buckets[index].push_back(val);
    }

    for (auto &bucket : buckets)
        sort(bucket.begin(), bucket.end());

    int idx = 0;
    for (auto &bucket : buckets)
        for (float val : bucket)
            arr[idx++] = val;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cerr << "Usage: ./BucketSort <input.txt> <output.txt>\n";
        return 1;
    }

    string inputFile = argv[1];
    string outputFile = argv[2];

    vector<float> arr;
    float x;

    ifstream infile(inputFile);
    if (!infile)
    {
        cerr << "Failed to open " << inputFile << '\n';
        return 1;
    }

    while (infile >> x)
        arr.push_back(x);
    infile.close();

    auto start = high_resolution_clock::now();
    bucketSort(arr);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Execution: " << duration.count() << " ms" << endl;

    ofstream outfile(outputFile);
    if (!outfile)
    {
        cerr << "Failed to open " << outputFile << '\n';
        return 1;
    }

    for (float val : arr)
        outfile << val << '\n';
    outfile.close();

    return 0;
}