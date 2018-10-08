#include <iostream> 

class MinHeap {
private:
    int *data;  /* pointer to array */
    int capacity; /* maximum possible size */
    int size; /* current number of elements */
    void swapPrivate(int* a, int* b);
    int parentPrivate(int i) { return (i-1)/2; }
    int leftPrivate(int i) { return (2*i+1); }
    int rightPrivate(int i) {return (2*i+2); }
    void heapifyPrivate(int i);
    
public:
    MinHeap(int n);
    MinHeap(int* arr, int n); 
    ~MinHeap();
    bool isOverflow(void);
    void print(void);
    bool isEmpty(void);
    int min(void);
    void heapify(void);
    void sort(int* arr, int n);
    int extractMin(void);
};

MinHeap::MinHeap(int n) {
    this->size = 0;
    this->capacity = n;
    this->data = new int[n];
}

MinHeap::MinHeap(int* arr, int n) {
    this->size = n;
    this->capacity = n;
    this->data = new int[n];
    for (int i=0; i<this->size; i++) 
        this->data[i] = arr[i];
    this->heapify();
}

MinHeap::~MinHeap() {
    delete []this->data;
}

bool MinHeap::isOverflow(void) {
    return (this->size >= this->capacity);
}

void MinHeap::swapPrivate(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void MinHeap::print(void) {
    if (this->isEmpty()) {
        std::cout << "Empty heap. Nothing to print. " << std::endl;
        return;
    }
    for (int i=0; i<this->size; i++) {
        std::cout << "i:" << i << " " << this->data[i] << std::endl;
    }
}

bool MinHeap::isEmpty(void) {
    return (this->size == 0);
}

int MinHeap::min(void) {
    if (this->isEmpty()) {
        std::cout << "Empty heap. No minimum. " << std::endl;
        return -1;
    }
    return this->data[0];
}

void MinHeap::heapify(void) {
    if (this->isEmpty()) {
        std::cout << "Cannot heapify empty head." << std::endl;
        return; 
    }
    for (int i=this->size/2-1; i>=0; i--) {
        this->heapifyPrivate(i); 
    }
}

void MinHeap::heapifyPrivate(int i) {
    int* arr = this->data;
    int smallest = i;   /* current parent index */
    int n = this->size; /* array size */
    int l = this->leftPrivate(i);
    int r = this->rightPrivate(i);
    
    if (l < n && arr[l] < arr[i] ) 
        smallest = l;
        
    if (r < n && arr[r] < arr[smallest]) 
        smallest = r;
        
    if (smallest != i) {
        this->swapPrivate(&arr[i], &arr[smallest]);
        this->heapifyPrivate(smallest);
    }
}

int MinHeap::extractMin(void) {
    if (this->isEmpty() ) {
        std::cout << "Empty heap. Nothing to extract" << std::endl;
        return -1;
    }
    int min = this->data[0];
    if (this->size > 1) {
        this->data[0] = this->data[this->size-1];
        this->size--;
        this->heapify();
    } else {
        this->size--;
    }
    return min;
}

int kthSmallestElement(int* arr, int n, int k) {
    MinHeap h(arr, n);
    //h.print();
    int val = 0;
    for (int s=0; s < k; s++) {
        val = h.extractMin();
    }
    return val;
}

int main(int argc, char* argv[]) {

    int arr[]={1,10,-2,3,-1};
    int size = 5;
    std::cout << "1st smallest element: " << kthSmallestElement(arr, size, 1) << std::endl; 
    std::cout << "2nd smallest element: " << kthSmallestElement(arr, size, 2) << std::endl; 
    std::cout << "3rd smallest element: " << kthSmallestElement(arr, size, 3) << std::endl; 
    std::cout << "4th smallest element: " << kthSmallestElement(arr, size, 4) << std::endl; 
    std::cout << "5th smallest element: " << kthSmallestElement(arr, size, 5) << std::endl; 
    std::cout << "6th smallest element: " << kthSmallestElement(arr, size, 6) << std::endl; 
    
    return 0;
}