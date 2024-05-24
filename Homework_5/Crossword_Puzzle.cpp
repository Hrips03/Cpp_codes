#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'crosswordPuzzle' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts following parameters:
 *  1. STRING_ARRAY crossword
 *  2. STRING words
 */

vector<string> crosswordPuzzle(vector<string> crossword, string words) {
    vector<int> arrOfLengths;
    int maxLengthInRows = 0, maxLengthInColumns = 0;
    for (int i = 0; i < 10; i++){
        maxLengthInRows = 0;
        for (int j = 0; j < 10; j++){
             int index = i * 10 + j;
            if (crossword[index] == "-") 
                maxLengthInRows++;
        }
        arrOfLengths.push_back(maxLengthInRows);
    }
    
    for (int j = 0; j < 10; j++){
        maxLengthInColumns = 0;
        for (int i = 0; i < 10; i++){
            int index = i * 10 + j;
            if (crossword[index] == "-") 
                maxLengthInColumns++;
        }
        arrOfLengths.push_back(maxLengthInColumns);
    }
    
    int maxLengthInCrossword = *max_element(arrOfLengths.begin(), arrOfLengths.end());
    cout << "max = " << maxLengthInCrossword << endl;
    
    vector<string> arrOfWords;
    string word = "";
    cout << words.length() << endl;
    for (int i = 0; i < words.length(); i++){
        if(words[i] != ';')
            word += words[i];
        else{
            arrOfWords.push_back(word);
            word = "";
        }
    }
    for (int i = 0; i < arrOfWords.size(); i++)
        cout << arrOfWords[i] << endl;
        
    vector<string> result = {"hey"};
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    vector<string> crossword(10);

    for (int i = 0; i < 10; i++) {
        string crossword_item;
        getline(cin, crossword_item);

        crossword[i] = crossword_item;
    }

    string words;
    getline(cin, words);

    vector<string> result = crosswordPuzzle(crossword, words);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

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
