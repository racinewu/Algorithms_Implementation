#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
using namespace std;
using namespace chrono;

void beadSort(vector<int> &arr)
{
    if (arr.empty())
        return;

    int n = arr.size();
    int maxVal = 0;
    for (int num : arr)
        if (num > maxVal)
            maxVal = num;

    vector<vector<bool>> beads(n, vector<bool>(maxVal, false));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < arr[i]; ++j)
            beads[i][j] = true;

    for (int j = 0; j < maxVal; ++j)
    {
        int count = 0;
        for (int i = 0; i < n; ++i)
            count += beads[i][j];
        for (int i = 0; i < n; ++i)
            beads[i][j] = i >= n - count;
    }

    for (int i = 0; i < n; ++i)
    {
        int val = 0;
        while (val < maxVal && beads[i][val])
            ++val;
        arr[i] = val;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cerr << "Usage: ./BeadSort <input.txt> <output.txt>\n";
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
    beadSort(arr);
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
