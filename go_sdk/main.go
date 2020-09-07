package main
/*
#cgo CFLAGS: -I../lib
#cgo LDFLAGS: -L../lib -lshm
#include "../lib/rgoshm.h"
 */
import (
	"C"
)

func main() {
	a := C.InitSegment(C.CString("data"), 10000)
	println(a)
}