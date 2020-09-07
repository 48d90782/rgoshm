<?php
$ffi = FFI::cdef(
    "char* ReceiveData(char *name);",
    "../lib/libshm.so");

$data = $ffi->ReceiveData("data");
//var_dump($data);
