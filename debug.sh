#!/bin/bash

echo "Building debug environment"

objcopy --only-keep-debug kernel.bin kernel.sym
objcopy --strip-debug kernel.bin

