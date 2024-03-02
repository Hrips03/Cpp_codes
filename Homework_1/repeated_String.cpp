#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'repeatedString' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. STRING s
 *  2. LONG_INTEGER n
 */

long repeatedString(string s, long n) {
    long count = 0;
    int quantity = 0;
    
    if(s == "a"){
        count += n;
        return count;
    }
    
    if(n < s.length()){
        for (int i = 0; i < n; i++){
            if(s[i] == 'a')
                count++; 
        }  
        return count;
    }
    
    for (int i = 0; i < s.length(); i++) {
        if(s[i] == 'a')
            quantity++;
    }
    
    if(quantity == 0)
        return 0;
        
    long div = n/s.length();
    count = div * quantity;
    int remaining = n - s.length() * div;
    
    quantity = 0;
    for (int i = 0; i < remaining; i++) {
        if(s[i] == 'a')
            quantity++;
    }
    count += quantity;
    
    return count;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string n_temp;
    getline(cin, n_temp);

    long n = stol(ltrim(rtrim(n_temp)));

    long result = repeatedString(s, n);

    fout << result << "\n";

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
