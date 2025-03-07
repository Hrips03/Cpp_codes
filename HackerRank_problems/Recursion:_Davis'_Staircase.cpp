#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'stepPerms' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER n as parameter.
 */
std::map<int, int> stairs;
int stepPerms(int n) {
    stairs[1] = 1;
    stairs[2] = 2;
    stairs[3] = 4;
    
    for (int i = 4; i <= n; i++) {
        stairs[i] = stairs[i - 1] + stairs[i - 2] + stairs[i - 3];
    }
    return stairs[n];
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s_temp;
    getline(cin, s_temp);

    int s = stoi(ltrim(rtrim(s_temp)));

    for (int s_itr = 0; s_itr < s; s_itr++) {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        int res = stepPerms(n);

        fout << res << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
