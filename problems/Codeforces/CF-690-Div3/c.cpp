#include <bits/stdc++.h> 
using namespace std;

string bestSum(int length, int sum, int target, int digit, string sofar) {
    if (sum == target) {
        return sofar;
    } else {
        if (digit == 10) return "10000000000000";
        string firstChoice = bestSum(length + 1, sum + digit, target, digit + 1, sofar + (to_string(digit)));
        string secondChoice = bestSum(length, sum, target, digit + 1, sofar);
        if ((int) firstChoice.size() < (int) secondChoice.size()) return firstChoice;
        else if ((int) firstChoice.size() > (int) secondChoice.size()) return secondChoice;
        else {
            return min(firstChoice, secondChoice);
        }
    }
}

int main() {
    int testcases; cin >> testcases;
    for (int i = 0; i < testcases; i++) {
        int number; cin >> number;
        string answer = bestSum(0, 0, number, 1, "");
        if (answer == "10000000000000") cout << -1 << '\n';
        else cout << bestSum(0, 0, number, 1, "") << '\n';
    }
}
