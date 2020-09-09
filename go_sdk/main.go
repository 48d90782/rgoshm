package main

import (
	"github.com/ValeryPiashchynski/rgoshm/shm"
)

func main() {
	seg, err := shm.NewSharedMemorySegment("safffffsadfasdfsadfff123123ffff", 1000, shm.IPC_CREAT)
	if err != nil {
		panic(err)
	}

	_ = seg
}
