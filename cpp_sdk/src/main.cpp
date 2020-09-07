#include "main.h"
#include <cstdlib>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
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

void sample2() {
    boost::interprocess::managed_shared_memory managed_shm {boost::interprocess::open_or_create, "shm", 1024};
    int *i = managed_shm.find_or_construct<int>("Integer")();
    boost::interprocess::named_mutex named_mtx{boost::interprocess::open_or_create, "mtx"};
    named_mtx.lock();
    ++(*i);
    std::cout << *i << std::endl;
    named_mtx.unlock();
}

int main() {
    sample2();

    return EXIT_SUCCESS;
}