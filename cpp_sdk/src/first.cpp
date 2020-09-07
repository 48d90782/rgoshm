#include "first.h"
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <iostream>
#include <cstdio>
#include "shared_data.h"


using namespace boost::interprocess;

int main() {
    // RAII
    struct shm_remove {
        shm_remove() {
            shared_memory_object::remove(SHARED_MEMORY_NAME);
        }

        ~shm_remove() {
            shared_memory_object::remove(SHARED_MEMORY_NAME);
        }
    } remover;

    shared_memory_object shm(
            create_only,
            SHARED_MEMORY_NAME,
            read_write
    );


    try {
        shm.truncate(sizeof(trace_queue));

        mapped_region region(
                shm,
                read_write
        );

        void *addr = region.get_address();
        auto *data = new(addr)trace_queue;

        const int NumMsg = 100;

        for (int i = 0; i < NumMsg; ++i) {
            scoped_lock<interprocess_mutex> lock(data->mutex);
            if (data->message_in) {
                data->cond_full.wait(lock);
            }
            if ((NumMsg - 1) == i) {
                std::sprintf(data->items, "%s", "last message");
            } else {
                std::sprintf(data->items, "%s_%d", "my_trace", i);
            }

            // notify to the other process that there is a message
            data->cond_empty.notify_one();

            // mark message buffer is full
            data->message_in = true;
        }


    } catch (interprocess_exception &err) {
        std::cout << err.what() << std::endl;
        return 1;
    }

    return EXIT_SUCCESS;
}