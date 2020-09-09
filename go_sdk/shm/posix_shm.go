package shm

import (
	"errors"
	"syscall"
	"unsafe"
)

type Flags int

// https://github.com/torvalds/linux/blob/master/include/uapi/linux/ipc.h
const (
	/* resource get request flags */
	IPC_CREAT  Flags = 00001000 /* create if key is nonexistent */
	IPC_EXCL   Flags = 00002000 /* fail if key exists */
	IPC_NOWAIT Flags = 00004000 /* return error on wait */
)

type SharedMemorySegment struct {
	path    *byte
	size    uint
	flags   Flags
	address uintptr
}

// key
// size
func NewSharedMemorySegment(key string, size uint, flags ...Flags) (*SharedMemorySegment, error) {
	path, err := syscall.BytePtrFromString(key)
	if err != nil {
		return nil, ErrCStringCreation
	}

	// OR flags
	var flgs Flags
	for i := 0; i < len(flags); i++ {
		flgs = flgs | flags[i]
	}

	// second arg could be uintptr(0) - auto
	// third arg - size
	// fourth - shmflg (flags)
	addr, _, errno := syscall.RawSyscall(syscall.SYS_SHMGET, uintptr(unsafe.Pointer(path)), uintptr(size), uintptr(flgs))
	if errno != 0 {
		return nil, errors.New(errno.Error())
	}

	data, err := syscall.Mmap()
	if err != nil {
		return err
	}

	return &SharedMemorySegment{
		path:    path,
		size:    size,
		flags:   flgs,
		address: addr,
	}, nil
}

func (s *SharedMemorySegment) ShmAT() error {

}
