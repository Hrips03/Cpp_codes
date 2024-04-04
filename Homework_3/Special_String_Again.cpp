#include <bits/stdc++.h>

using namespace std;

// Complete the substrCount function below.
long substrCount(int n, string s)
{
    long result = s.length();

    for (int i = 0; i < s.length(); i++)
    {
        int counter = 0;
        while (i + 1 < s.length() && s[i] == s[i + 1])
        {
            counter++;
            i++;
        }
        result += (counter * (counter + 1)) / 2;

        int pointer = 1;
        while (i - pointer >= 0 && i + pointer < s.length() && s[i + pointer] == s[i - 1] && s[i - pointer] == s[i - 1])
        {
            result++;
            pointer++;
        }
    }

    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string s;
    getline(cin, s);

    long result = substrCount(n, s);

    fout << result << "\n";

    fout.close();

    return 0;
}
