#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
using namespace std;
using namespace chrono;

void countingSortByDigit(vector<int> &arr, int exp)
{
    vector<int> output(arr.size());
    vector<int> count(10, 0);
    for (int val : arr)
        count[(val / exp) % 10]++;

    for (int i = 1; i < 10; ++i)
        count[i] += count[i - 1];

    for (int i = arr.size() - 1; i >= 0; --i)
    {
        int digit = (arr[i] / exp) % 10;
        output[--count[digit]] = arr[i];
    }
    arr = output;
}

void radixSort(vector<int> &arr)
{
    if (arr.empty())
        return;
    int max_val = *max_element(arr.begin(), arr.end());
    for (int exp = 1; max_val / exp > 0; exp *= 10)
        countingSortByDigit(arr, exp);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cerr << "Usage: ./RadixSort <input.txt> <output.txt>\n";
        return 1;
    }

    string inputFile = argv[1];
    string outputFile = argv[2];

    vector<int> arr;
    int x;

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
    radixSort(arr);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Execution: " << duration.count() << " ms" << endl;

    ofstream outfile(outputFile);
    if (!outfile)
    {
        cerr << "Failed to open " << outputFile << '\n';
        return 1;
    }

    for (int val : arr)
        outfile << val << '\n';
    outfile.close();

    return 0;
}
