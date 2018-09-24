#include <iostream> 
#include <stack>

std::stack<int> nextGreaterElementSimple(int* data, int n) {
    std::stack<int> nge;
    for (int i=0; i<n; i++) {
        int next = -1;
        for (int j=i+1; j<n; j++) {
            if (data[j] > data[i]) {
                next = data[j];
                break;
            }
        }
        nge.push(next);
    }
    return nge;
}

std::stack<int> nextGreaterElement(int* data, int n) {
    std::stack<int> temp;
    std::stack<int> nge;
    temp.push(data[0]);
    for (int i=1; i<n; i++) {
        if (data[i] > temp.top()) {
            
        }
        temp.push(data[i]);
    }
}
int main(int argc, char *argv[]) {
    
    
    return 0;
}