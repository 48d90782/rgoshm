#ifndef SHM_RGOSHM_H
#define SHM_RGOSHM_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
void *InitSegment(const char *name, size_t size);
#ifdef __cplusplus
}
#endif
#endif //SHM_RGOSHM_H
