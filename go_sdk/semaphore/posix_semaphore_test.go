package semaphore

import "testing"

func TestSemaphore_GetValue(t *testing.T) {
	s := NewSemaphore()
	v, err := s.GetValue("fsf", 1, IPC_CREAT)
	if err != nil {
		t.Fatal(err)
	}

	err = s.Wait(v)
	if err != nil {
		t.Fatal(err)
	}
}
