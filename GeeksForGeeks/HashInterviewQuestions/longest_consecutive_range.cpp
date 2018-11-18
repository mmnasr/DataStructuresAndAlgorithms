#include <iostream>
#include <unordered_set>
#include <cassert>

using namespace std;
inline int max(int a, int b) {
    if (a > b) 
        return a;
    return b;
}

int longestConsecutiveRangeCount(int* data, int n) {
    if ( (data == NULL) || (n == 0) )
        return 0;
    unordered_set<int> hash;
    for (int i=0; i<n; i++) 
        hash.insert(data[i]);
    int max_len = 0;
    for (int i=0; i<n; i++) {
        // check if current element is the first on the consecutive range.
        if (hash.find(data[i]-1)  == hash.end() ) {
            int j = data[i];
            while (hash.find(j) != hash.end() ) {
                j++;
            }
            max_len = max(max_len, j-data[i]);
        }
    }
    return max_len;       
}

int main() {
    int data[] = {1,2,3,0,5};
    int size = sizeof(data) / sizeof(data[0]);
    
    cout << longestConsecutiveRangeCount(data, size) << endl;
    assert(longestConsecutiveRangeCount(data, size)==3 && "test 1 failed");
    
    return 0;
}