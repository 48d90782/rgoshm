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
	var a *C.char
	a = C.ReceiveData(C.CString("data"))
	str := C.GoString(a)
	println(str)
}