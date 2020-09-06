package main

import (
	"os"
	"syscall"
	"unsafe"
)

func main() {
	name := "testtt"
	name2, err := syscall.BytePtrFromString(name)
	if err != nil {
		panic(err)
	}
	perm := os.O_RDWR|os.O_CREATE|os.O_EXCL
	fd, _, errno := syscall.Syscall(syscall.SHM, uintptr(unsafe.Pointer(name2)), uintptr(0600), uintptr(perm))
	if errno != 0 {
		panic(errno)
	}

	println(fd)
}