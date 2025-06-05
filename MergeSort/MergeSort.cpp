#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
using namespace std;
using namespace chrono;

void merge(vector<int> &arr, int l, int m, int r)
{
    vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);
    int i = 0, j = 0, k = l;
    while (i < left.size() && j < right.size())
        arr[k++] = (left[i] <= right[j]) ? left[i++] : right[j++];

    while (i < left.size())
        arr[k++] = left[i++];

    while (j < right.size())
        arr[k++] = right[j++];
}

void mergeSort(vector<int> &arr, int l, int r)
{
    if (l >= r)
        return;

    int m = (l + r) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        cerr << "Usage: ./MergeSort <input.txt> <output.txt>\n";
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
    mergeSort(arr, 0, arr.size() - 1);
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