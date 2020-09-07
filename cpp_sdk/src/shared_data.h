#define SHARED_MEMORY_NAME "shared_memory"

#ifndef SHM_SHARED_DATA_H
#define SHM_SHARED_DATA_H

#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>

struct trace_queue {
    enum {
        LineSize = 200000000
    };

    trace_queue() : message_in(false) {}

    //mutex to protect access to the queue
    boost::interprocess::interprocess_mutex mutex;

    // condition to wait when the queue is empty
    boost::interprocess::interprocess_condition cond_empty;

    // condition to wait when queue is full
    boost::interprocess::interprocess_condition cond_full;

    // items
    char data[LineSize]{};

    // is there any message
    bool message_in;
};

#endif //SHM_SHARED_DATA_H
