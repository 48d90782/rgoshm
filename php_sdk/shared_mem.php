<?php
$ffi = FFI::cdef(
    "void *InitSegment(const char *name, size_t size);",
    "../lib/libshm.so");

$data = $ffi->InitSegment("sample", 10000);
var_dump($data);