#include <bits/stdc++.h> 
using namespace std;
 
int main() {
    int testcases; cin >> testcases;
    for (int t = 0; t < testcases; t++) {
        int length; cin >> length;
        string inputstring; cin >> inputstring;
        bool possible = false;
        string sofar = "";
        string testString = "";
        for (int j = length - 1; j >= length - 4; j--) testString += inputstring[j];
        reverse(testString.begin(), testString.end());
        if (testString == "2020") possible = true;
        for (int i = 0; i < 4; i++) {
            sofar += inputstring[i];
            string revString;
            for (int j = length - 1; j >= length - (4 - (int)sofar.size()); j--) {
                revString += inputstring[j];
            }
            reverse(revString.begin(), revString.end());
            if (sofar + revString == "2020") possible = true;
        }
        if (possible == true) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }
}

