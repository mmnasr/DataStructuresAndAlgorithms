#include <iostream>
#include <map>
#include <cassert>

using namespace std;
inline int max(int a, int b) {
    if (a > b) 
        return a;
    return b;
}

int maxLengthSumZero(int* arr, int n) {
    if ( (n == 0) || (arr == NULL) ) 
        return 0;
    map<int, int> hash;
    int sum = 0;
    int max_len = 0;
    for (int i=0; i<n; i++) {
        sum += arr[i];
        if (arr[i]==0 && max_len==0) 
            max_len = 1; 
        if (sum == 0) 
            max_len = i+1; 
        if (hash.find(sum) != hash.end() ) {
            max_len = max(max_len, i-hash[sum]);
        }  else {
            hash[sum] = i;
        }
    }
    return max_len;
}

int main() {
    int test[]={1,-2,2,-1,10,-3,-2,-1};
    int size = sizeof(test) / sizeof(test[0]);
    //assert(maxLengthSumZero(test, 3)==2 && "failed test 1");
    
    cout << maxLengthSumZero(test, size) << endl;
    return 0;
}