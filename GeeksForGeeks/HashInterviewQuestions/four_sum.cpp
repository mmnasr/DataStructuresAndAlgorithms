#include <iostream> 
#include <map>
#include <utility>
#include <cassert>
#include <vector>

// Practice questions: 
// https://www.geeksforgeeks.org/find-four-elements-a-b-c-and-d-in-an-array-such-that-ab-cd/

using namespace std;

bool findTwoTwoSumPairs(int* data, int n) {
    if ( (data == NULL) || (n < 4) ) return false;
    map<int, pair<int, int> > hash;
    bool found = false;
    for (int i=0; i < n; i++) {
        for (int j=i+1; j<n; j++) {
            int sum = data[i] + data[j];
            if (hash.find(sum) == hash.end()) {
                hash[sum] = make_pair(i,j);
            } else {
                pair<int,int> prev = hash[sum];
                cout << "pairs found:" << data[i] << "+" << data[j] 
                << "=" << data[prev.first] << "+" << data[prev.second] << endl;
                found = true;
            }
        }
    }        
    return found;
}

void printPairs(map<int, vector<pair<int, int> > > hash, int* data) {
    map<int, vector<pair<int, int> > >::iterator sum_it;
    for (sum_it=hash.begin(); sum_it != hash.end(); sum_it++) {
        int sum = sum_it->first;
        /* No other pair found. Continue to next sum in the hash table. */
        if (sum_it->second.size() <= 1) 
            continue;
        vector<pair<int, int> >::iterator it_pair; 
        cout << "Pairs w/ equal sum: {" << sum << "}\n  ";
        for (it_pair=hash[sum].begin(); it_pair != hash[sum].end(); it_pair++) {
            pair<int, int> prev = *it_pair;
            cout << "(" << data[prev.first] << "," << data[prev.second] << ") ";
        }
        cout << endl;
    }
}

bool findTwoTwoSumPairsAllCases(int* data, int n) {
    if ( (data == NULL) || (n < 4) ) return false;
    map<int, vector<pair<int, int> > > hash;
    bool found = false;
    for (int i=0; i < n; i++) {
        for (int j=i+1; j<n; j++) {
            int sum = data[i] + data[j];
            if (hash.find(sum) == hash.end()) {
                hash[sum].push_back(make_pair(i,j));
            } else {
                hash[sum].push_back(make_pair(i,j));
                found = true;
            }
        }
    }        
    if (found) {
        printPairs(hash, data);
    }
    return found;
}

int main() {
    int test[] = {1,2,3,0,5,-2};
    //assert(findTwoTwoSumPairs(test, 3)==false && "Test 1 failed");
    
    // cout << findTwoTwoSumPairs(test, 6) << endl;
    cout << findTwoTwoSumPairsAllCases(test, 6);
    return 0;
}