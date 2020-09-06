#include "main.h"
#include <cstdlib>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>

#define STORAGE_ID1 "/SHM_USER1"
#define STORAGE_ID2 "/SHM_USER2"

#define STORAGE_SIZE 32


// returns file descriptor to the shared memory segment
extern "C" int open_shared_segment() {

}

int main() {
    return EXIT_SUCCESS;
}