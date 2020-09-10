package semaphore

import "testing"

func TestSemaphore_GetValue(t *testing.T) {
	s := NewSemaphore("", 10)
	v, err := s.GetValue("fsf6fsg", 2, IPC_CREAT)
	if err != nil {
		t.Fatal(err)
	}

	err = s.Wait(uint16(v))
	if err != nil {
		t.Fatal(err)
	}
}
