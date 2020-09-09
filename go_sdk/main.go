package main

import (
	"syscall"
	"unsafe"
)

func main() {
	key, err := syscall.BytePtrFromString("1xfffff")
	if err != nil {
		panic(err)
	}

	r1, r2, errno := syscall.RawSyscall(syscall.SYS_SHMGET, uintptr(unsafe.Pointer(key)),uintptr(101010),  uintptr(0666|IPC_CREAT|IPC_EXCL))
	if errno != 0 {
		panic(errno)
	}

	_ = r1
	_ = r2
}
