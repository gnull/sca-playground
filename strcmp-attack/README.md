# `strcmp` Timing Attack

## FILES

* `vulnerable.c` - Vulnerable program reporting number of cycles it spent
    comparing strings.
* `timestamp.c` - Program reporting current value of x86-specific `rdtsc`
    cycles counter.
* `collect-internal.pl` - Script for running `vulnerable` multiple times and
    collecting timestamps provided by it in CSV format.

## EXAMPLE

```sh
make

# See help
./vulnerable
./collect-internal.pl

# Collect some statistics
./collect-internal.pl 100 1000 100 > data.csv

# Analyse the csv with any tool (e.g. R)
```
