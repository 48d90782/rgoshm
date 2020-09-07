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
        shm.truncate(10000);

        boost::interprocess::mapped_region region(
                shm,
                boost::interprocess::read_write
        );
        void *addr = region.get_address();
        auto *tq = new(addr)trace_queue;
        const int NumMsg = 100;

        for (int i = 0; i < NumMsg; ++i) {
            boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(tq->mutex);
            if (tq->message_in) {
                tq->cond_full.wait(lock);
            }
            if ((NumMsg - 1) == i) {
                std::sprintf(tq->items, "%s", "last message");
            } else {
                std::sprintf(tq->items, "%s_%d", "my_trace", i);
            }

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

#ifdef __cplusplus
extern "C" {
#endif
char *ReceiveData(char *name) {
    boost::interprocess::shared_memory_object shm(
            boost::interprocess::open_only,
            name,
            boost::interprocess::read_write
    );

    try {
        boost::interprocess::mapped_region region(
                shm,
                boost::interprocess::read_write
        );

        void *addr = region.get_address();

        auto *data = static_cast<trace_queue *>(addr);

        std::cout << addr << std::endl;

        bool end_loop = false;

        do {
            boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(data->mutex);
            if (!data->message_in) {
                data->cond_empty.wait(lock);
            }

            if (std::strcmp(data->items, "last message") == 0) {
                end_loop = true;
            } else {
                //print message
                std::cout << data->items << std::endl;

                // notify other processes that the buffer is empty
                data->message_in = false;
                data->cond_full.notify_one();
            }
        } while (!end_loop);
        return data->items;

    } catch (boost::interprocess::interprocess_exception &err) {
        std::cout << err.what() << std::endl;
    }
    return nullptr;
}
#ifdef __cplusplus
}
#endif

extern "C" int RemoveSegment(void *address) {
    return 0;
}

extern "C" {
void Send(const char *message) {
//        auto *data = new(region_address)trace_queue;
//        for (int i = 0; i < 100; ++i) {
//            boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock()
//        }
}
}

extern "C" {
char *Receive() {

    return "fasdf";
}
}