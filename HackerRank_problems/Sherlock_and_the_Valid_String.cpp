#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'isValid' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string isValid(string s)
{
    if (s.length() == 1)
        return "YES";

    std::map<char, int> duplicates;
    for (const char letter : s)
        duplicates[letter]++;

    int total_pairs = duplicates.size();
    int current_pair = 0;

    for (const auto pair : duplicates)
    {
        std::cout << pair.first << "^" << pair.second;
        if (++current_pair < total_pairs)
            std::cout << " , ";
    }
    std::cout << std::endl;

    int count = 0;
    const auto pair = duplicates.begin()->second;
    cout << " pair = " << pair << endl;
    for (const auto pair1 : duplicates)
        if (abs(pair - pair1.second) >= 1)
        {
            count++;
        }

    cout << "count = " << count << endl;
    if (count == 1 || count == 0)
        return "YES";
    else
        return "NO";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = isValid(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
