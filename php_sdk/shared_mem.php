<?php
$ffi = FFI::cdef(
    "void SendData(const char *name, const char *data);",
    "../lib/libshm.so");

$file = file_get_contents('./generated.json', true);

for ($i = 0; $i < 100; $i++) {
    $ffi->SendData("data", $file);
}
