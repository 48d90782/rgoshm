#include "main.h"
#include <cstdlib>

#include <boost/interprocess/shared_memory_object.hpp>
#include <fcntl.h>

#define STORAGE_ID1 "/SHM_USER1"
#define STORAGE_ID2 "/SHM_USER2"

#define STORAGE_SIZE 32


// returns file descriptor to the shared memory segment
//extern "C" int open_shared_segment() {
//   int fd = shm_open(STORAGE_ID1, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
//}

int main() {
//    int fd = shm_open(STORAGE_ID1, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    boost::interprocess::shared_memory_object shm_obj
            (boost::interprocess::create_only                  //only create
                    ,"shared_memory"              //name
                    ,boost::interprocess::read_write                   //read-write mode
            );
    return EXIT_SUCCESS;
}