/* Stacks: https://en.wikipedia.org/wiki/Stack_(abstract_data_type) */
/* A C++ implementation of stacks using pointers. */
/* By: Mohamad Nasr-Azadani, mmnasr@gmail.com */
/* LIFO data access */
/***************************************************************************************/
/***************************************************************************************/

#include <iostream>

template <class T>
class mystack {
    private:
        T* data;
        size_t size_; /* stack size. Accessible to user */
        size_t capacity; /* stack capacity. Adds extra memory for future allocation. Not accessible to user */
        void updateCapacityPrivate(void); /* update capacity when size surpasses capacity. It is an expensive operation */
        
    public:
        mystack();
        ~mystack();
        void push(T value); 
        size_t size(void); 
        bool empty(void); 
        void display(void); 
        void pop(void);
        T* top(void);
};

template <class T>
mystack<T>::mystack()
{
    size_ = 0; 
    capacity = 1;
    data = new T[capacity]; 
}

template <class T>
mystack<T>::~mystack()
{
    delete []data; 
    data = NULL;
}
template <class T> 
bool mystack<T>::empty(void)
{
    return (!size_); 
}

template <class T>
size_t mystack<T>::size(void)
{
    return size_; 
}

template <class T>
void mystack<T>::push(T value) 
{
    data[size_] = value;
    size_++; 
    if (size_ == capacity) 
    {
        updateCapacityPrivate(); 
    }
}

template <class T> 
void mystack<T>::updateCapacityPrivate(void)
{
    capacity = (size_t) (1.2 * size_ + 1);
    T* data_temp = new T[capacity];
    if (data_temp == NULL) {
        std::cout << "Cannot allocate memory for size: " << capacity << std::endl;
        return;
    }
    for (size_t i=0; i != size_; ++i) 
    {
        data_temp[i] = data[i];
    }
    T* delPtr = data; 
    data = data_temp; 
    delete []delPtr; 
    delPtr = NULL; 
}

template <class T>
void mystack<T>::display(void)
{
    for (size_t i=0; i != size_; ++i) 
    {
        std::cout << data[i] << " " ;
    }
    std::cout << std::endl;
}

template <class T>
void mystack<T>::pop(void) 
{
    if (size_) size_--;
}

template <class T>
T* mystack<T>::top(void) 
{
    if (size_) {
        return &data[size_-1];
    }
    return NULL; 
}

int main(int argc, char *argv[]) 
{  
    mystack<size_t> st; 
    std::cout << "Stack is empty: " << st.empty() << std::endl; 
    st.push(2);     
    st.push(4);     
    st.push(5);     
    st.push(6);     
    st.push(7);     
    st.display(); 
    size_t *top = st.top();
    *top = *top +1 ;
    st.display(); 
    std::cout << "Popping the last value " << std::endl;
    st.pop(); 
    st.display(); 
    std::cout << "Stack size: " << st.size() << std::endl; 
    return 0 ;
}
