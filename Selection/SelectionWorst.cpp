#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int findMedian(vector<int> &arr, int start, int n)
{
    sort(arr.begin() + start, arr.begin() + start + n);
    return arr[start + n / 2];
}

int partition(vector<int> &arr, int low, int high, int pivot)
{
    int i;
    for (i = low; i < high; ++i)
    {
        if (arr[i] == pivot)
            break;
    }
    swap(arr[i], arr[high]);

    i = low;
    for (int j = low; j < high; ++j)
    {
        if (arr[j] <= pivot)
        {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[high]);

    return i;
}

int select(vector<int> &arr, int low, int high, int k)
{
    if (low == high)
        return arr[low];

    int n = high - low + 1;
    vector<int> medians((n + 4) / 5);

    for (int i = 0; i < n / 5; ++i)
        medians[i] = findMedian(arr, low + i * 5, 5);
    if (n % 5)
        medians[n / 5] = findMedian(arr, low + (n / 5) * 5, n % 5);

    int medOfMed = (medians.size() == 1) ? medians[0]
                                         : select(medians, 0, medians.size() - 1, medians.size() / 2);

    int pos = partition(arr, low, high, medOfMed);
    int order = pos - low + 1;

    if (order == k)
        return arr[pos];
    else if (k < order)
        return select(arr, low, pos - 1, k);
    else
        return select(arr, pos + 1, high, k - order);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cerr << "Usage: ./SelectionWorst <input.txt> <i-th>\n";
        return 1;
    }

    string inputFile = argv[1];
    int k = stoi(argv[2]);

    ifstream infile(inputFile);
    if (!infile)
    {
        cerr << "Failed to open " << inputFile << '\n';
        return 1;
    }

    vector<int> arr;
    int x;
    while (infile >> x)
        arr.push_back(x);
    infile.close();

    if (k < 1 || k > arr.size())
    {
        cerr << "Error: i-th number out of range.\n";
        return 1;
    }

    int minVal = *min_element(arr.begin(), arr.end());
    int maxVal = *max_element(arr.begin(), arr.end());
    int kthElement = select(arr, 0, arr.size() - 1, k);

    cout << "Min = " << minVal << " Max = " << maxVal << endl;
    cout << "The " << k << "-th = " << kthElement << endl;

    return 0;
}
