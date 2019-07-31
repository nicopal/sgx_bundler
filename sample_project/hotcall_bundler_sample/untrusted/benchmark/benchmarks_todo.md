### VANILLA

Conduct an experiment which shows the difference between HOTCALLS and ECALLS enclave transition.
Conduct this experiment with different micro-code versions to show that ECALLS have become much more expensive but hotcalls have stayed the same.

Conduct an experiment which shows the impact of passing arguments.

### MEMOIZE

Conduct an experiment to show performance cache hit vs cache hit with and without cold cache. Also show differences between LRU and FIFO caches.

### BUNDLE

Conduct an experiment to demonstrate the performance gains when bundling several hotcalls

### FUNCTIONAL

FOR_EACH - Bundle VS for each

MAP - Bundle VS for each

FILTER  

### IMPERATIVE

FOR - Conduct experiment to show the performance of for statement

WHILE - Conduct experiment to show the performance of while statement when condition is changed through an ecall inside of the loop body.

IF - Conduct an experiment showing the loss/gains of using an if statement vs no if statement include both when branch is executed and when its not.


IMPERATIV VS FUNCTIONAL


for(int i = 0; i < n; ++i) {
  if(xs[i]) {
    do_ecall();
  }
}


### OVS

OVS_OPTIMIZED

OVS_BUNDLE+MEMO
