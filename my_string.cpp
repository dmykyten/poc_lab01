// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


#include <string>
#include <iostream>

#include "my_string.hpp"

void my_str_t::print(){
    std::string temp;
    temp += "my_str_t : (data_m = |";
    for (size_t i = 0; i < capacity_m + 1; ++i){
        temp += data_m[i];
    }
    temp +=  + "|, \n\t    ";
    temp += "size_m = " + std::to_string(size_m) + ", \n\t    "
          + "capacity_m = " + std::to_string(capacity_m);
    std::cout << temp << ")\n";
}

my_str_t::my_str_t(size_t size, char initial): size_m{size},
                                               capacity_m{size - (size % 16) + 15},
                                               data_m{ new( std::nothrow ) char[capacity_m + 1] }
{
    // capacity_m = (size & (~15ull)) + 16ull;
    // capacity_m = size - (size % 16) + 16; - the same
//    data_m = new( std::nothrow ) char[capacity_m + 1];
    if (!data_m){
        std::cout << "Allocation error: my_str_t(size_t size, char initial)" << std::endl;
    }
    for (size_t i = 0; i < size; ++i){
        data_m[i] = initial;
    }
}

my_str_t::my_str_t (const char* cstr){

    size_t size = 0;
    while(cstr[size] != '\0'){
        ++size;
    }
    size_m = size;
    capacity_m = size - (size % 16) + 15;
    data_m = new( std::nothrow ) char[capacity_m + 1];

    if (!data_m){
        std::cout << "Allocation error in: my_str_t (const char* cstr)" << std::endl;
    }
    // {
    for (size_t i = 0; i < size_m; ++i){
        data_m[i] = cstr[i];
    }
    // } memcpy()?
}

my_str_t::my_str_t (const std::string& str): size_m{str.size()},
                                             capacity_m{size_m - (size_m % 16) + 15},
                                             data_m{ new( std::nothrow ) char[capacity_m + 1] }
{
//    data_m = new( std::nothrow ) char[capacity_m + 1];

    if (!data_m){
        std::cout << "Allocation error in: my_str_t (const std::string& str)" << std::endl;
    }
    if (str.empty()){
        return;
    }
    // {
    const char * temp = str.c_str();
    for (size_t i = 0; i < size_m; ++i){
        data_m[i] = temp[i];
    }
    // } memcpy()?
}

my_str_t::my_str_t (const my_str_t& mystr): size_m{mystr.size_m},
                                            capacity_m{mystr.capacity_m},
                                            data_m{ new( std::nothrow ) char[capacity_m + 1] }
{
//    data_m = new( std::nothrow ) char[capacity_m + 1];

    if (!data_m){
        std::cout << "Allocation error in: my_str_t (const my_str_t& mystr)" << std::endl;
    }
    // {
    char* temp = mystr.data_m;
    for (size_t i = 0; i < size_m; ++i){
        data_m[i] = temp[i];
    }
    // } memcpy()?
}


my_str_t& my_str_t::operator=(const my_str_t& mystr)
{
    size_m = mystr.size_m;
    capacity_m = mystr.capacity_m;
    data_m = new( std::nothrow ) char[capacity_m + 1];

    if (!data_m){
        std::cout << "Allocation error in: operator=(const my_str_t& mystr)" << std::endl;
    }
    // {
    char* temp = mystr.data_m;
    for (size_t i = 0; i < size_m; ++i){
        data_m[i] = temp[i];
    }
    // } memcpy()?
    return *this;
}


my_str_t::my_str_t (my_str_t&& mystr): size_m{mystr.size_m},
                                       capacity_m{mystr.capacity_m},
                                       data_m{std::move(mystr.data_m)}
{
//    data_m = mystr.data_m;

    mystr.size_m = 0;
    mystr.capacity_m = 15;
    mystr.data_m = new( std::nothrow ) char[16];

    if (!mystr.data_m){
        std::cout << "Allocation error in: my_str_t (my_str_t&& mystr)" << std::endl;
    }
}


my_str_t& my_str_t::operator=(my_str_t&& mystr){

    size_m = mystr.size_m;
    capacity_m = mystr.capacity_m;
    data_m = mystr.data_m;

    mystr.size_m = 0;
    mystr.capacity_m = 15;
    mystr.data_m = new( std::nothrow ) char[16];

    if (!mystr.data_m){
        std::cout << "Allocation error in: operator=(my_str_t&& mystr)" << std::endl;
    }
    return *this;
}


void my_str_t::swap (my_str_t& other) noexcept {
    size_t temp_size = size_m;
    size_t temp_capacity = capacity_m;
    char * temp_data = data_m;

    size_m = other.size_m;
    capacity_m = other.capacity_m;
    data_m = other.data_m;

    other.size_m = temp_size;
    other.capacity_m = temp_capacity;
    other.data_m = temp_data;
}

//char& operator[](size_t idx);
//const char& operator[](size_t idx) const;

my_str_t::~my_str_t(){
    delete[] data_m;
}