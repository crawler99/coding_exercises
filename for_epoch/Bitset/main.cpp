#include <iostream>
#include <string>
#include "Bitset.hpp"

template<size_t N>
void print(const std::string &name, const Bitset<N> &bitSet)
{
    std::cout << "\n-> " << name << ": ";
    auto size = bitSet.getSize();
    for(size_t i = 0; i < size; ++i)
    {
        std::cout << (bitSet.isSet(i)? "1" : "0");
    }
}

int main()
{
    unsigned int step = 0;

    std::cout << "\n[" << ++step << "] Construct a new bit set named bs10_1 with 10 bits inside ...";
    Bitset<10> bs10_1;
    // Bitset<5> bs5_1(bs10_1); // won't compile
    print("bs10_1", bs10_1);

    std::cout << "\n\n[" << ++step << "] Set the 1st, 4th, 7th and 10th bits of bs10_1 ...";
    std::cout<< "\nold 1st bit: " << bs10_1.set(0);
    std::cout<< "\nold 4th bit: " << bs10_1.set(3);
    std::cout<< "\nold 7th bit: " << bs10_1.set(6);
    std::cout<< "\nold 10th bit: " << bs10_1.set(9);
    print("bs10_1", bs10_1);

    std::cout << "\n\n[" << ++step << "] Copy construct bs10_2 from bs10_1 ...";
    auto bs10_2(bs10_1);
    print("bs10_2", bs10_2);

    std::cout << "\n\n[" << ++step << "] Assign bs10_2 to bs10_3 ...";
    Bitset<10> bs10_3;
    bs10_3 = bs10_2;
    print("bs10_3", bs10_3);

    std::cout << "\n\n[" << ++step << "] Unset the 4th bit of bs10_3 ...";
    std::cout<< "\nold 4th bit: " << bs10_3.clear(3);
    print("bs10_3", bs10_3);

    std::cout << "\n\n[" << ++step << "] Invert the 2nd and 7th bits of bs10_3 ...";
    std::cout<< "\nold 2nd bit: " << bs10_3.invert(1);
    std::cout<< "\nold 7th bit: " << bs10_3.invert(6);
    print("bs10_3", bs10_3);

    std::cout << "\n\n[" << ++step << "] Move-Construct bs10_3 to bs10_4 ...";
    auto bs10_4(std::move(bs10_3));
    print("bs10_4", bs10_4);

    std::cout << "\n\n[" << ++step << "] Move-Assign bs10_4 to bs10_1 ...";
    bs10_1 = std::move(bs10_4);
    print("bs10_1", bs10_1);

    std::cout << "\n\n[" << ++step << "] Reset bs10_1 ...";
    bs10_1.reset();
    print("bs10_1", bs10_1);

    std::cout << "\n\n[" << ++step << "] Accessing an invalid bit position from bs10_1 ...";
    try
    {
        std::cout<< "\nold 100th bit: " << bs10_1.set(100);
    }
    catch (std::exception &e)
    {
        std::cout << "\n-> Exception caught: " << e.what();
    }

    std::cout << "\n\n[" << ++step << "] Construct a very bit bit set which would exhaust the memory ...";
    try
    {
        Bitset<99999999999999> bsBig;
    }
    catch (std::bad_alloc &e)
    {
        std::cout << "\n-> Exception caught: " << e.what() << "\n\n";
    }

    return 0;
}
