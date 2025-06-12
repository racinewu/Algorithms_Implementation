#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<vector<int>> lcsLength(const vector<char> &X, const vector<char> &Y)
{
    int m = X.size();
    int n = Y.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp;
}

vector<char> constructLCS(const vector<char> &X, const vector<char> &Y, const vector<vector<int>> &dp)
{
    int i = X.size();
    int j = Y.size();
    vector<char> lcs_seq;

    while (i > 0 && j > 0)
    {
        if (X[i - 1] == Y[j - 1])
        {
            lcs_seq.push_back(X[i - 1]);
            --i;
            --j;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
            --i;
        else
            --j;
    }

    reverse(lcs_seq.begin(), lcs_seq.end());
    return lcs_seq;
}

int main()
{
    string str1, str2;
    cout << "Input 1st string: " << endl;
    cin >> str1;
    cout << "Input 2nd string: " << endl;
    cin >> str2;

    vector<char> X(str1.begin(), str1.end());
    vector<char> Y(str2.begin(), str2.end());

    vector<vector<int>> dp = lcsLength(X, Y);
    vector<char> lcs_seq = constructLCS(X, Y, dp);

    cout << "LCS length: " << dp[X.size()][Y.size()] << "\n";
    cout << "LCS sequence: ";
    for (char c : lcs_seq)
        cout << c;
    cout << "\n";

    return 0;
}
