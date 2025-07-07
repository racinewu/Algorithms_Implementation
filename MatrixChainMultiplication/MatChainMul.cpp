#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <sstream>
#include <iomanip>
#include <cmath>
using namespace std;

void printOptimalParens(const vector<vector<int>> &s, int i, int j, string &res)
{
    if (i == j)
        res += "A" + to_string(i + 1);
    else
    {
        res += "(";
        printOptimalParens(s, i, s[i][j], res);
        res += " x ";
        printOptimalParens(s, s[i][j] + 1, j, res);
        res += ")";
    }
}

vector<vector<int>> multiply(const vector<vector<int>> &A, const vector<vector<int>> &B)
{
    int m = A.size(), n = A[0].size(), p = B[0].size();
    vector<vector<int>> C(m, vector<int>(p, 0));
    for (int i = 0; i < m; ++i)
        for (int k = 0; k < n; ++k)
            for (int j = 0; j < p; ++j)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

vector<vector<int>> chainMultiply(vector<vector<vector<int>>> &matrices, vector<vector<int>> &s, int i, int j)
{
    if (i == j)
        return matrices[i];
    auto left = chainMultiply(matrices, s, i, s[i][j]);
    auto right = chainMultiply(matrices, s, s[i][j] + 1, j);
    return multiply(left, right);
}

int numDigits(int n)
{
    if (n == 0)
        return 1;
    return static_cast<int>(log10(abs(n))) + 1;
}

void printMatrixFormatted(const vector<vector<int>> &mat, ofstream &outfile)
{
    int maxVal = 0;
    for (auto &row : mat)
        for (int val : row)
            maxVal = max(maxVal, abs(val));
    int width = numDigits(maxVal) + 1;

    outfile << "Final Result Matrix (" << mat.size() << "x" << mat[0].size() << "):\n";
    for (auto &row : mat)
    {
        for (int val : row)
            outfile << setw(width) << val << " ";
        outfile << "\n";
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cerr << "Usage: ./MatChainMul <input.txt> <output.txt>\n";
        return 1;
    }

    string inputFile = argv[1];
    string outputFile = argv[2];

    ifstream infile(inputFile);
    if (!infile)
    {
        cerr << "Failed to open " << inputFile << '\n';
        return 1;
    }

    ofstream outfile(outputFile);
    if (!outfile)
    {
        cerr << "Failed to open " << outputFile << '\n';
        return 1;
    }

    int N;
    infile >> N;
    vector<int> dims;
    vector<vector<vector<int>>> matrices;

    for (int i = 0; i < N; ++i)
    {
        int r, c;
        infile >> r >> c;
        if (i == 0)
            dims.push_back(r);
        dims.push_back(c);
        vector<vector<int>> mat(r, vector<int>(c));
        for (int x = 0; x < r; ++x)
            for (int y = 0; y < c; ++y)
                infile >> mat[x][y];
        matrices.push_back(mat);
    }
    infile.close();

    int n = N;
    vector<vector<int>> m(n, vector<int>(n, 0));
    vector<vector<int>> s(n, vector<int>(n, 0));

    for (int l = 2; l <= n; ++l)
        for (int i = 0; i <= n - l; ++i)
        {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; ++k)
            {
                int cost = m[i][k] + m[k + 1][j] + dims[i] * dims[k + 1] * dims[j + 1];
                if (cost < m[i][j])
                {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }

    string order;
    printOptimalParens(s, 0, n - 1, order);
    cout << "Optimal Parenthesization: " << order << "\n";
    cout << "Minimum Multiplication Cost: " << m[0][n - 1] << "\n";

    auto result = chainMultiply(matrices, s, 0, n - 1);
    printMatrixFormatted(result, outfile);

    return 0;
}
