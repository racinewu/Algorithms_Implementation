#include <iostream>
#include <random>
#include <vector>
#include <fstream>
using namespace std;

int main()
{
    int N, dimRange, low, high;
    cout << "Enter number of matrices: ";
    cin >> N;
    cout << "Enter dimension range (max size): ";
    cin >> dimRange;
    cout << "Enter value range (low high): ";
    cin >> low >> high;

    if (N < 1 || dimRange < 1 || low > high)
    {
        cerr << "Invalid input.\n";
        return 1;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dimDis(1, dimRange);
    uniform_int_distribution<> valDis(low, high);

    vector<int> dims(N + 1);
    for (int i = 0; i <= N; ++i)
        dims[i] = dimDis(gen);

    ofstream outfile("matrices.txt");
    if (!outfile)
    {
        cerr << "Failed to open output file.\n";
        return 1;
    }

    outfile << N << "\n";

    for (int i = 0; i < N; ++i)
    {
        int rows = dims[i];
        int cols = dims[i + 1];
        outfile << rows << " " << cols << "\n";

        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < cols; ++c)
            {
                outfile << valDis(gen);
                if (c != cols - 1)
                    outfile << " ";
            }
            outfile << "\n";
        }
    }
    outfile.close();

    cout << "Generated " << N << " valid matrices to matrices.txt\n";

    return 0;
}
