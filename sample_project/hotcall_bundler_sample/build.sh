#!/bin/bash

source /opt/intel/sgxsdk/environment

make -C ../../src/trusted clean
make -C ../../src/trusted SGX_MODE=HW SGX_PRERELEASE=1 SGX_DEBUG=0

make -C ../../src/untrusted clean
make -C ../../src/untrusted  

make clean
make SGX_MODE=HW SGX_PRERELEASE=1 SGX_DEBUG=0
