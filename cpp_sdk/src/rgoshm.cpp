#include "rgoshm.h"
#include <string>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

// return address of shared memory region
#ifdef __cplusplus
extern "C" {
#endif
void *InitSegment(const char *name, size_t size) {
    boost::interprocess::shared_memory_object shm(
            boost::interprocess::open_or_create,
            name,
            boost::interprocess::read_write
    );

    if (size == 0) {
        shm.truncate(1024);
    } else {
        shm.truncate(size);
    }

    boost::interprocess::mapped_region region(
            shm,
            boost::interprocess::read_write
    );

    return region.get_address();
}
#ifdef __cplusplus
}
#endif

extern "C" int RemoveSegment(void *address) {
    return 0;
}

extern "C" void Send() {

}

extern "C" void Receive() {

}