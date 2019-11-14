#include <iostream>
#include <vector>
#include <chrono>

template <class T>
void swap(T & a, T & b){
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}

template <class T>
void slow_swap(T & a, T & b){
    T tmp = a;
    a = b;
    b = tmp;
}


int main(){

    std::vector<int> a;

    std::vector<int> b;

    constexpr auto vector_size = 1'000'000;
    constexpr auto swap_count = 1000;

    auto start = std::chrono::high_resolution_clock::now(); 
    for (auto i = 0; i < vector_size; i++) {
        a.push_back(i);
        b.push_back(-i);
    }
    auto stop = std::chrono::high_resolution_clock::now(); 

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 
  
    std::cout << "Time taken to fill: " << duration.count() << " microseconds" << std::endl; 


    start = std::chrono::high_resolution_clock::now(); 
    for (auto i = 0; i < swap_count; i++){
        swap(a, b);
    }
    stop = std::chrono::high_resolution_clock::now(); 
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken to swap: " << duration.count() << " microseconds" << std::endl;


    start = std::chrono::high_resolution_clock::now(); 
    for (auto i = 0; i < swap_count; i++){
        slow_swap(a, b);
    }
    stop = std::chrono::high_resolution_clock::now(); 
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken to slow swap: " << duration.count() << " microseconds" << std::endl; 

    return EXIT_SUCCESS;
}