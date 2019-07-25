#!/bin/bash

source /opt/intel/sgxsdk/environment

MICRO_CODE_VERSION=$1

sudo cset shield --cpu 2,3
sudo cset shield --kthread on
for f in hotcall; do #hotcall_1 hotcall_3 hotcall_5 hotcall_10 hotcall_15 vanilla_0 vanilla_1 vanilla_3 vanilla_5 vanilla_10 vanilla_15; do
    echo $f
    OUTPUT_DIR="./data/${MICRO_CODE_VERSION}/${f}"
    rm -rf $OUTPUT_DIR
    mkdir -p $OUTPUT_DIR
    for cache_mode in warm cold; do
        N_ITERS=""
        if [[ $cache_mode == "warm" ]]; then
            echo "TRUE"
            N_ITERS=10000
            for i in $(seq 0 9); do 
                cset shield -e ./sample -- -b "${MICRO_CODE_VERSION}/${f}" ${f}_0 $N_ITERS -$cache_mode
            done
        else
            echo "FALSE $cache_mode"
            N_ITERS=10000
            for m in 1 2 4 8; do
                for i in $(seq 0 9); do 
                    cset shield -e ./sample -- -b "${MICRO_CODE_VERSION}/${f}" ${f}_0 $N_ITERS -$cache_mode $m
                done
            done
        fi
    done
done
sudo cset shield --reset
