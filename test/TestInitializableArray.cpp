#include <iostream>
#include <chrono>

#include "InitializableArray.hpp"

int main(int argc, char const *argv[])
{
    unsigned long long int size = 1000000000;

    using clock = std::chrono::high_resolution_clock;
    {
        auto start = clock::now();

        arr::InitializableArray<int> a(size, 1);

        auto stop = clock::now();
        auto load_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        std::cerr << "Array of size " << a.size() << " initialized in " << load_time.count() << " ns" << std::endl;
        int i = 2;
        a.insert(0, i);
        auto tot = 0;
        for (int i = 0; i < a.size(); ++i)
        {
            tot += a[i];
        }
        std::cout << tot << std::endl;
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