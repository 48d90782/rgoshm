package main

import (
	"github.com/ValeryPiashchynski/rgoshm/shm"
)

func main() {
	seg, err := shm.NewSharedMemorySegment("safffffsadfasdfsadfffffff", 1000, shm.IPC_CREAT, shm.IPC_EXCL)
	if err != nil {
		panic(err)
	}

	_ = seg
}
