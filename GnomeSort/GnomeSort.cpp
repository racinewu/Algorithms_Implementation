#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
using namespace std;
using namespace chrono;

void gnomeSort(vector<int> &arr)
{
    int index = 0;
    int n = arr.size();
    while (index < n)
    {
        if (index == 0 || arr[index] >= arr[index - 1])
            index++;
        else
        {
            swap(arr[index], arr[index - 1]);
            index--;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cerr << "Usage: ./GnomeSort <input.txt> <output.txt>\n";
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
    gnomeSort(arr);
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