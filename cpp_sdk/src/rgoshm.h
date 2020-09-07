#ifndef SHM_RGOSHM_H
#define SHM_RGOSHM_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
char *ReceiveData(char *name);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif
void SendData(const char *name, const char *data);
#ifdef __cplusplus
}
#endif
#endif //SHM_RGOSHM_H
