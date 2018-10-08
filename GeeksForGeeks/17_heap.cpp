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
    void heapifyPrivate(int* arr, int n, int i);
    
public:
    MinHeap(int n);
    ~MinHeap();
    bool isOverflow(void);
    void decreaseKey(int idx, int keynew);
    void insert(int key);
    void print(void);
    bool isEmpty(void);
    int min(void);
    void heapify(int* arr, int n);
    void sort(int* arr, int n);
    int extractMin(void);
};

MinHeap::MinHeap(int n) {
    this->size = 0;
    this->capacity = n;
    this->data = new int[n];
}

MinHeap::~MinHeap() {
    delete []this->data;
}

void MinHeap::insert(int key) {
    if (this->isOverflow()) {
        std::cout << "Overflow. Cannot insert new key:" << key << std::endl;
        return;
    }
    int i = this->size;
    this->data[i] = key;
    this->size++;
    
    /* insert new key at the end, then check for all the parents to and swap if the new key is less than the parent */
    while (i != 0 && this->data[this->parentPrivate(i)] > this->data[i]) {
        this->swapPrivate( &this->data[i], &this->data[this->parentPrivate(i)]);
        i = this->parentPrivate(i); 
    } /* while */
}

void MinHeap::decreaseKey(int idx, int keynew) {
    
    
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

void MinHeap::heapify(int* arr, int n) {
    if (n <= 0) {
        std::cout << "Cannot heapify an empty array." << std::endl;
        return; 
    }
    for (int i=n/2-1; i>=0; i--) {
        this->heapifyPrivate(arr, n, i); 
    }
}

void MinHeap::heapifyPrivate(int* arr, int n, int i) {
    int smallest = i;
    int l = this->leftPrivate(i);
    int r = this->rightPrivate(i);
    
    if (l < n && arr[l] < arr[i] ) 
        smallest = l;
        
    if (r < n && arr[r] < arr[smallest]) 
        smallest = r;
        
    if (smallest != i) {
        this->swapPrivate(&arr[i], &arr[smallest]);
        this->heapifyPrivate(arr, n, smallest);
    }
}

void MinHeap::sort(int* arr, int n) {
    if (n <= 0) {
        std::cout << "Cannot sort an empty array." << std::endl;
        return; 
    }
    this->heapify(arr, n);
    // One by one extract an element from heap 
    for (int i=n-1; i>=0; i--) 
    { 
        // Move current root to end 
        this->swapPrivate(&arr[0], &arr[i]); 
  
        // call min heapify on the reduced heap 
        this->heapifyPrivate(arr, i, 0); 
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
        this->heapify(this->data, this->size-1);
    }
    this->size--;
    return min;
}

int kthSmallestElement(int* arr, int n, int k) {
    MinHeap h(n); 
    h.heapify(arr, n);
    int val = 0;
    for (int s=0; s < k; s++) {
        val = h.extractMin();
    }
    return val;
}

int main(int argc, char* argv[]) {

    MinHeap h(10);
    h.insert(4);
    h.insert(2);
    h.insert(3);
    h.insert(0);
    h.print();
    
    std::cout << "Min: " << h.min() << std::endl;
    std::cout << "extract min: " << h.extractMin() << std::endl; 
    std::cout << "extract min: " << h.extractMin() << std::endl; 
    std::cout << "extract min: " << h.extractMin() << std::endl; 
    std::cout << "extract min: " << h.extractMin() << std::endl; 
    h.print();
    
    MinHeap hn(10); 
    int arr[]={5,2,4,1,3,0};
    int size = 6;
    std::cout << "2nd smallest element: " << kthSmallestElement(arr, size, 2) << std::endl; 
    
    hn.sort(arr, size);
    //hn.heapify(arr, size);
    for (int i=0; i<size; i++) {
        std::cout << "i: " << i << " " << arr[i] <<std::endl;
    }
    
    return 0;
}