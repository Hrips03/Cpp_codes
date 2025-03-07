#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'makeAnagram' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING a
 *  2. STRING b
 */

int makeAnagram(string a, string b)
{
    std::map<char, int> duplicatesInA;
    for (const char letter : a)
        duplicatesInA[letter]++;

    std::map<char, int> duplicatesInB;
    for (const char letter : b)
        duplicatesInB[letter]++;

    // int total_pairs1 = duplicatesInA.size();
    // int current_pair1 = 0;

    // for (const auto pair : duplicatesInA) {
    //     std::cout << pair.first << "^" << pair.second;
    //     if (++current_pair1 < total_pairs1)
    //         std::cout << " , ";
    // }
    // std::cout << std::endl;

    // int total_pairs2 = duplicatesInB.size();
    // int current_pair2 = 0;

    // for (const auto pair : duplicatesInB) {
    //     std::cout << pair.first << "^" << pair.second;
    //     if (++current_pair2 < total_pairs2)
    //         std::cout << " , ";
    // }
    // std::cout << std::endl;

    vector<int> arr;

    for (const auto pair1 : duplicatesInA)
    {
        bool found = false;
        for (const auto pair2 : duplicatesInB)
        {
            if (pair1.first == pair2.first)
            {
                if (pair1.second - pair2.second != 0)
                    arr.push_back(abs(pair1.second - pair2.second));
                found = true;
            }
        }
        if (!found)
        {
            cout << "pair1.first = " << pair1.first << endl;
            arr.push_back(pair1.second);
        }
    }

    for (const auto pair2 : duplicatesInB)
    {
        bool found = false;
        for (const auto pair1 : duplicatesInA)
        {
            if (pair1.first == pair2.first)
            {
                found = true;
            }
        }
        if (!found)
        {
            cout << "pair2.first = " << pair2.first << endl;
            arr.push_back(pair2.second);
        }
    }

    int sum = 0;
    for (int i = 0; i < arr.size(); i++)
        sum += arr[i];

    return sum;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string a;
    getline(cin, a);

    string b;
    getline(cin, b);

    int res = makeAnagram(a, b);

    fout << res << "\n";

    fout.close();

    return 0;
}
