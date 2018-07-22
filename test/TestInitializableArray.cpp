#include <iostream>
#include <chrono>
#include <iterator>

#include "InitializableArray.hpp"

int main(int argc, char const *argv[])
{
    unsigned long long int size = 1000000;

    using clock = std::chrono::high_resolution_clock;
    {
        auto start = clock::now();

        arr::InitializableArray<int> a(size, 1);

        auto stop = clock::now();
        auto load_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        std::cerr << "Array of size " << a.size() << " initialized in " << load_time.count() << " ns" << std::endl;
        a.insert(0, 2);
        auto tot = 0;
        for (int i = 0; i < a.size(); ++i)
        {
            tot += a[i];
        }
        std::cout << tot << std::endl;

        a.insert(0, 0);
        tot = 0;
        for (int i = 0; i < a.size(); ++i)
        {
            tot += a[i];
        }
        std::cout << tot << std::endl;

        a.clear();
        tot = 0;
        for (int i = 0; i < a.size(); ++i)
        {
            tot += a[i];
        }
        std::cout << tot << std::endl;

        auto it = a.begin();
        std::cout << *it << std::endl;

        tot = 0;
        for(auto&& i : a) {
            tot += i;
        }
        std::cout << tot << std::endl;

        std::cout << std::distance(a.begin(), a.end()) << std::endl;
        std::cout << std::distance(a.end(), a.end()) << std::endl;
        std::cout << std::distance(a.end(), a.begin()) << std::endl;

    }

    {
        auto start = clock::now();

        std::vector<int> a(size, 1);

        auto stop = clock::now();
        auto load_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        std::cerr << "Array of size " << a.size() << " initialized in " << load_time.count() << " ns" << std::endl;
        auto tot = 0;
        for(auto&& i : a) {
            tot += i;
        }
        std::cout << tot << std::endl;
    }
    return 0;
}