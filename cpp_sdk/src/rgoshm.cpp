#include "rgoshm.h"
#include "shared_data.h"
#include <string>
#include <iostream>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

// name - mapped region name
// data - passing data
#ifdef __cplusplus
extern "C" {
#endif
void SendData(const char *name, const char *data) {
    boost::interprocess::shared_memory_object shm(
            boost::interprocess::open_or_create,
            name,
            boost::interprocess::read_write
    );

    try {
        shm.truncate(200000000);

        boost::interprocess::mapped_region region(
                shm,
                boost::interprocess::read_write
        );
        void *addr = region.get_address();
        auto *tq = new(addr)trace_queue;

        for (int i = 0; i < 2; ++i) {
            boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(tq->mutex);
            if (tq->message_in) {
                tq->cond_full.wait(lock);
            }

            // write data to the region
            std::sprintf(tq->data, "%s", data);

            // notify to the other process that there is a message
            tq->cond_empty.notify_one();

            // mark message buffer is full
            tq->message_in = true;
        }

    } catch (boost::interprocess::interprocess_exception &err) {
        std::cout << err.what() << std::endl;
    }
}
#ifdef __cplusplus
}
#endif

// Receive data from the memory region
#ifdef __cplusplus
extern "C" {
#endif
char *ReceiveData(char *name) {
    boost::interprocess::shared_memory_object shm(
            boost::interprocess::open_only,
            "data",
            boost::interprocess::read_write
    );

    try {
        boost::interprocess::mapped_region region(
                shm,
                boost::interprocess::read_write
        );

        void *addr = region.get_address();

        auto *tq = static_cast<trace_queue *>(addr);

        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(tq->mutex);
        if (!tq->message_in) {
            tq->cond_empty.wait(lock);
        }

        // notify other processes that the buffer is empty
        tq->message_in = false;
        tq->cond_full.notify_one();

        char *ret_str = static_cast<char *>(malloc(sizeof(tq->data)));
        memcpy(ret_str, tq->data, sizeof(tq->data));
        return ret_str;
    } catch (boost::interprocess::interprocess_exception &err) {
        std::cout << err.what() << std::endl;
    }
    // no data
    return nullptr;
}
#ifdef __cplusplus
}
#endif
