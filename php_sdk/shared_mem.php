<?php
$ffi = FFI::cdef(
    "int Fib(int n);",
    "../lib/libshared.so");