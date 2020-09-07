#include "main.h"
#include <cstdlib>
#include <boost/interprocess/shared_memory_object.hpp>
#include <iostream>

void sample1() {
    boost::interprocess::shared_memory_object shdmem{boost::interprocess::open_or_create, "Boost",
                                                     boost::interprocess::read_write};

    shdmem.truncate(1024);
    std::cout << shdmem.get_name() << std::endl;
    boost::interprocess::offset_t size;

    if (shdmem.get_size(size))
        std::cout << size << std::endl;
}

int main() {
    sample1();

    return EXIT_SUCCESS;
}