// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


#include <iostream>

#include <boost/type_index.hpp>

#include "my_string.hpp"



template<typename T>
inline std::string type(T var);

void print(const char* str);

template<typename T, size_t size>
void print(const T* str);

template<typename T, size_t size>
void print(const T (&str)[size] );

int main() {
    my_str_t my_str_1(3, '1');
    my_str_1.print();

    my_str_t my_str_2("22222");
    my_str_2.print();

    std::string temp = "33333";
    my_str_t my_str_3(temp);
    my_str_3.print();

    my_str_t my_str_4(my_str_1);
    my_str_4.print();

    my_str_t my_str_5(my_str_1);
    my_str_5 = my_str_2;
    my_str_5.print();

    return 0;

    // init char pointer
    const char * str = "11";
    const char * str_1 = "1\0";
    print(str_1);
    //    std::cout << type(str_1) << '\n';



    // init char array
    char str_2[10] {'1','1'};
    std::cout << str_2[2] << "|\n";


    //dunamically init char array
    int size = 4;
    int* str_3 = new int[size];//{'1','1'};
    print<int, 4>(str_3);

    return 0;
}




template<typename T>
inline std::string type(T var){
    auto ti = boost::typeindex::type_id_with_cvr<decltype(var)>();
    return ti.pretty_name();
}

void print(const char* str){
    size_t i = 0;
    while(str[i] != '\0'){
        std::cout << str[i];
        ++i;
    }
    std::cout<<'\n';
}

template<typename T, size_t size>
void print(const T* str){
    std::cout<<"print(const T* str)\n";
    for (size_t i = 0; i < size; ++i){
        std::cout << str[i] << " i " << i << ", ";
    }
    std::cout<<'\n';
}

template<typename T, size_t size>
void print(const T (&str)[size] ){

    for (size_t i =0; i < size; ++i){
        std::cout << str[i];
    }
    std::cout<<"|\n";
}

