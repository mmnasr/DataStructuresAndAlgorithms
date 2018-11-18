#include <iostream> 
#include <unordered_set>
#include <cassert>

using namespace std;

bool hasPairSum(int* data, int n, int sum) {
    if ( (n <= 1) || (data == NULL) )
        return false;
    unordered_set<int> s;
    bool found = false;
    for (int i=0; i<n; i++) {
        int temp = sum - data[i];
        if ( s.find(temp) != s.end() ) {
            cout << "Found pair with sum " << sum << " (" << data[i] << "," << temp << ")" << endl;
            found = true;
        }
        s.insert(data[i]);
    }
    return found;
}

int main() {
    int test[2] = {1,2};
    assert(hasPairSum(test, 2, 3)==true && "Test 1 failed");
    assert(hasPairSum(test, 2, 2)==false && "Test 2 failed");
    assert(hasPairSum(NULL, 2, 2)==false && "Test 3 failed");
    cout << "Test cases ended" << endl;
    int data[5] = {2,-2,-1,-4,-5};
    cout << hasPairSum(data, 2, 0) << endl;
    return 0;
}