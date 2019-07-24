#!/bin/bash

source /opt/intel/sgxsdk/environment



sudo cset shield --cpu 2,3
sudo cset shield --kthread on
for f in hotcall_0 vanilla_0; do #hotcall_1 hotcall_3 hotcall_5 hotcall_10 hotcall_15 vanilla_0 vanilla_1 vanilla_3 vanilla_5 vanilla_10 vanilla_15; do
    for cache_mode in warm cold; do
        N_ITERS=""
        if [[ $cache_mode == "warm" ]]; then
            N_ITERS=10000
        else
            N_ITERS=10000
        fi
        for i in $(seq 0 9); do 
            rm -rf ./untrusted/benchmark/data/hotcall/benchmark_$f/$cache_mode
            cset shield -e ./sample -- $f $N_ITERS -$cache_mode
        done
    done
done
sudo cset shield --reset
