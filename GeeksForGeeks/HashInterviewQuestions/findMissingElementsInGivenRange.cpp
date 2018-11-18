#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;
int countMissingElementsInRange_MethodSort(int* data, int n, int low, int high) {
    if ( (n == 0) || (data == NULL) ) 
        return 0;
    sort(data, data+n);        
    return 0;
}

int countMissingElementsInRange_MethodHash(int* data, int n, int low, int high) {
    if ( (n == 0) || (data == NULL) ) 
        return 0;
    unordered_set<int> hash;
    for (int i=0; i<n; i++) {
        hash.insert(data[i]);
    }    
    int count = 0;
    for (int i=low; i<high; i++) {
        if ( hash.find(i) == hash.end() ) {
            cout << "Elements not found in array: " << i << endl;
            count++;
        }
    }
    return count;
}

int main() {

    int test[] = {1,2,0,5};
    int size = sizeof(test) / sizeof(test[0]);
    int low = 0;
    int high = 8;
    cout << countMissingElementsInRange_MethodHash(test, size, low, high) << endl;
    return 0;
    
}
