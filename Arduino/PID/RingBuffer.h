#include <iostream>

template <class T>
class RingBuffer {

private:
    T * buffer;
    int head = 0;
    int tail = 0;
    // T getHead();
    // T getBuffer();

public:
    RingBuffer(size_t size) : buffer(new T[size]), capacity(size) {
        for (int i = 0; i < size; i++) {
            buffer[i] = 0;
        }
    }

    
    void add(T);
    T get(size_t);
    // bool isFull();
    size_t capacity;


    ~RingBuffer(void) {
        delete buffer;
    }
};

// Method to access data at arbitrary position
template <class T>
T RingBuffer<T>::get(size_t index) {
    if(index > capacity) {
        // BAD
    }

    if(index < (capacity - head)) {
        index = head + index;
    } else {
        index = index - (capacity - head);
    }

    return buffer[index];
};

// Method to add data, moves the head variable one step after adding data, moves tail if buffer is full
template <class T>
void RingBuffer<T>::add(T input) {
    // if(isFull()) {
    //     tail = (tail + 1) % capacity;
    // }
    
    head = (head + 1) % capacity;
    buffer[head] = input;
};




//
//int main() {
////    //RingBuffer<int> circle(3);
////    //int x = 100;
////    //int y = 200;
////    //int z = 300;
////    //
////    //circle.add(x);
////    //circle.add(y);
////    //circle.add(z);
////
////    //for (int i = 0; i <= 2; i++)
////    //    std::cout << circle.buffer[i];
////
////    //std::cout << "\n";
////
////    //circle.add(z);
////    //circle.add(156);
////
////    //for (int i = 0; i <= 2; i++)
////    //    std::cout << circle.buffer[i];
////
////    //std::cout << "\n";
////    //std::cout << circle.get(0) << std::endl;
////    //std::cout << circle.get(1) << std::endl;
////
////    int b = 5;
////
////    int* a;
////    a = &b;
////
////    std::cout << *a;
////
////    {RingBuffer<int> circle(2);
////    circle.add(0);
////    circle.add(0);
////    a = circle.buffer;
////    std::cout << *a; }
////
////    std::cout << *a;
//    RingBuffer<int> circle(3);
//    int x = 1;
//    int y = 2;
//    int z = 3;
//
//    for (int i = 0; i <= 2; i++)
//        std::cout << circle.buffer[i];
//
//    circle.add(x);
//    circle.add(y);
//    circle.add(z);
//    for (int i = 0; i <= 2; i++)
//        std::cout << circle.buffer[i];
//
////
////
//    return 0;
//};
