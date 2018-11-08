#include <iostream>

void print2DArray(int** data, int N) {
    for (int j=0; j<N; j++) {
        for (int i=0; i<N; i++) {
            std::cout << "v(" <<j<<","<<i<<")="<<data[j][i] << " ";
        }
        std::cout << std::endl;
    }
}

void rotate2D90Degrees(int** data, int N) {
    if (data == NULL) return;
    
    for (int j=0; j < N; j++) {
        for (int i=0; i <N; i++) {
            int temp = data[j][i];
            data[j][i] = data[i][N-j-1];
            data[N-i-1][i] = temp;
        }
    }
}

int main() {
    int N = 2;
    int** d = new int*[N];
    for (int i=0; i<N; i++) {
        d[i] = new int[N];
    }
    d[0][0] = 1;
    d[0][1] = 2;
    d[1][0] = 3;
    d[1][1] = 4;
    print2DArray(d, 2);
    rotate2D90Degrees(d, 2);
    print2DArray(d, 2);
    return 0;
}