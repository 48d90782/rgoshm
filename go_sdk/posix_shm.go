package main

const (
	IPC_CREAT  = 00001000 /* create if key is nonexistent */
	IPC_EXCL   = 00002000 /* fail if key exists */
	IPC_NOWAIT = 00004000 /* return error on wait */

	IPC_RMID = 0 /* remove resource */
	IPC_SET  = 1 /* set ipc_perm options */
	IPC_STAT = 2 /* get ipc_perm options */
	IPC_INFO = 3 /* see ipcs */

)

type SharedMemory struct {
	key string
}

func NewSharedMemory(key string) *SharedMemory {
	return &SharedMemory{}
}