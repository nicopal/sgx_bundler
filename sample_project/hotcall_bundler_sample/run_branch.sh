#!/bin/bash

source /opt/intel/sgxsdk/environment

MICRO_CODE_VERSION=$1

sudo cset shield --cpu 2,3
sudo cset shield --kthread on
for f in hotcall_branch_true hotcall_branch_true_naive hotcall_branch_false hotcall_branch_false_naive; do 
    OUTPUT_DIR="./data/${MICRO_CODE_VERSION}/${f}"
    rm -rf $OUTPUT_DIR
    mkdir -p $OUTPUT_DIR
    for cache_mode in warm cold; do
        N_ITERS=10000
        if [[ $cache_mode == "warm" ]]; then
            for i in $(seq 0 19); do
                cset shield -e ./sample -- -b "${MICRO_CODE_VERSION}/${f}" ${f} $N_ITERS -$cache_mode
            done
        else
            N_ITERS=10000
            for i in $(seq 0 19); do
                cset shield -e ./sample -- -b "${MICRO_CODE_VERSION}/${f}" ${f} $N_ITERS -$cache_mode 2
            done
        fi
    done
done
sudo cset shield --reset
