#include "second.h"
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <iostream>
#include <cstring>
#include "shared_data.h"

using namespace  boost::interprocess;
int main() {
    shared_memory_object shm (
            open_only,
            SHARED_MEMORY_NAME,
            read_write
            );

    try {
        mapped_region region (
                shm,
                read_write
        );

        void *addr = region.get_address();

        auto *tq = static_cast<trace_queue*>(addr);

        std::cout << addr << std::endl;

        bool end_loop = false;

        do {
            scoped_lock<interprocess_mutex> lock(tq->mutex);
            if (!tq->message_in) {
                tq->cond_empty.wait(lock);
            }

            if (std::strcmp(tq->data, "last message") == 0) {
                end_loop = true;
            } else {
                //print message
                std::cout << tq->data << std::endl;

                // notify other processes that the buffer is empty
                tq ->message_in = false;
                tq->cond_full.notify_one();
            }
        } while (!end_loop);

    } catch (interprocess_exception &err) {
        std::cout << err.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}