<?php
$ffi = FFI::cdef(
    "void SendData(const char *name, const char *data);",
    "../lib/libshm.so");

ini_set('memory_limit','250M');

$file = file_get_contents('./citylots.json', true);
$data = $ffi->SendData("data", $file);
var_dump($data);
