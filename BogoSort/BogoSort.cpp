#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <random>
using namespace std;
using namespace chrono;

bool isSorted(const vector<int> &arr)
{
    for (size_t i = 1; i < arr.size(); ++i)
        if (arr[i - 1] > arr[i])
            return false;

    return true;
}

void bogoSort(vector<int> &arr)
{
    random_device rd;
    mt19937 gen(rd());
    while (!isSorted(arr))
        shuffle(arr.begin(), arr.end(), gen);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cerr << "Usage: ./BogoSort <input.txt> <output.txt>\n";
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
    bogoSort(arr);
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