#include <bits/stdc++.h>
using namespace std;

bool prefixNonNegative(const vector<int>& a) {
    int sum = 0;
    for (int x : a) {
        sum += x;
        if (sum < 0) return false;
    }
    return true;
}

bool prefixNonPositive(const vector<int>& a) {
    int sum = 0;
    for (int x : a) {
        sum += x;
        if (sum > 0) return false;
    }
    return true;
}

int main() {
    vector<vector<int>> tests = {
        {1, -1, 1, -1},   
        {1, -1, -1, 1},    
        {1, 1, -1, -1},   
        {-1, 1, 1},        
        {1, -1, -1},       
        {}                 
    };

    cout << "Non-negative prefix sums:\n";
    for (size_t i = 0; i < tests.size(); ++i) {
        cout << "test " << i << ": ";
        for (int v : tests[i]) cout << v << ' ';
        cout << " -> " << (prefixNonNegative(tests[i]) ? "OK" : "BAD") << '\n';
    }

    cout << "\nNon-positive prefix sums:\n";
    for (size_t i = 0; i < tests.size(); ++i) {
        cout << "test " << i << ": ";
        for (int v : tests[i]) cout << v << ' ';
        cout << " -> " << (prefixNonPositive(tests[i]) ? "OK" : "BAD") << '\n';
    }

    return 0;
}
