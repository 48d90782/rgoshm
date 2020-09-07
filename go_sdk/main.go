package main
/*
#cgo LDFLAGS: -L../lib -lshm
#include "../lib/rgoshm.h"
 */
import (
	"C"
)

func main() {
	// "data" is the name of the mapped memory region
	a := C.ReceiveData(C.CString("data"))
	println(a)
}