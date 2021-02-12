#include <bits/stdc++.h> 
using namespace std;

int main() {
    int testcases; cin >> testcases;
    for (int t = 0; t < testcases; t++) {
        int elements; cin >> elements;
        vector<int> arr(elements);
        for (int i = 0; i < elements; i++) cin >> arr[i];
        vector<int> result;
        for (int i = 0; i < elements / 2; i++) {
            result.push_back(arr[i]);
            result.push_back(arr[elements - i - 1]);
        }
        if (elements % 2 == 1) result.push_back(arr[elements / 2]);
        for (int i = 0; i < (int) result.size(); i++) cout << result[i] << " ";
        cout << '\n';
    }
}
