#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

ifstream in("input.in");
ofstream out("output.out");
bool lambda=0;
void tokenize(std::string const &str, const char *delim,
              std::vector<std::string> &out) {
    char *token = strtok(const_cast<char *>(str.c_str()), delim);
    while (token != nullptr) {
        out.push_back(std::string(token));
        token = strtok(nullptr, delim);
    }
}

void generateWords(vector<string> v[], string input, int length) {
    bool ok=1;


    for (int i = 0; i < input.length(); i++) {
        if(isupper(input[i]))
        {
            ok=0;
            int x=input[i]-'A';
            for (auto it = v[x].begin(); it != v[x].end(); ++it) {
                string string1=input,string2=*it;
                string1.erase(i,1);
                string1.insert(i,string2);
                if(string1.length()<=length+lambda)
                    generateWords(v,string1,length);
            }
        }
    }
    int pos=input.find('&');
    while (input.find('&') != std::string::npos)
    {
        input.erase(pos,1);
        pos=input.find('&');
    }
    if(ok==1 && input.length()<=length && !input.empty())
        {
            cout << input;
            cout << '\n';
        }
}

int main() {

    char neterminal[30] = {0};
    vector<string> v[26];
    string input;
    bool line = 1;
    int x;
    while (in >> input) {
        line = !line;
        if (line == 0) {
            x = input[0] - 'A';
        } else if (line == 1) {
            const char *delim = "|";
            tokenize(input, delim, v[x]);
            if(input.find('&') != std::string::npos)
                lambda=1;
        }
    }

    for (int x = 0; x < 26; x++) {
        if (!v[x].empty()) {
            cout << char(x + 'A') << ": ";
            for (auto i = v[x].begin(); i != v[x].end(); ++i) {
                cout << *i << " ";
            }
            cout << '\n';
        }
    }
    cout << '\n';

    string start = {"S"};

    int len;
    cout << "n= ";
    cin >> len;
    generateWords(v,start,len);
    if(lambda)
        cout << "ε";

    return 0;
}