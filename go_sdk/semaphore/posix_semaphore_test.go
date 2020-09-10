package semaphore

import "testing"

func TestSemaphore_GetValue(t *testing.T) {
	s := NewSemaphore()
	v, err := s.GetValue("fsf", 1, IPC_CREAT, IPC_EXCL)
	if err != nil {
		t.Fatal(err)
	}
	println(v)
}
