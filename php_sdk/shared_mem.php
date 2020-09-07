<?php
$ffi = FFI::cdef(
    "void SendData(const char *name, const char *data);",
    "../lib/libshm.so");

$data = $ffi->SendData("data", "10000");
var_dump($data);
