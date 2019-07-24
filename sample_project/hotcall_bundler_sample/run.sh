#!/bin/bash

source /opt/intel/sgxsdk/environment

sudo cset shield --cpu 2,3
sudo cset shield --kthread on
#cset shield -e source /opt/intel/sgxsdk/environment
cset shield -e ./sample -- $1 5>out
sudo cset shield --reset
