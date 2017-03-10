# `strcmp` Timing Attack

## FILES

* `vulnerable.c` - Vulnerable program reporting number of cycles it spent
    comparing strings.
* `timestamp.c` - Program reporting current value of x86-specific `rdtsc`
    cycles counter.
* `collect-internal.pl` - Script for running `vulnerable` multiple times and
    collecting timestamps provided by it in CSV format.
* `collect-external.pl` - The same as `collect-internal.pl`, but measures
    cycles using `timestamp` instead of relying of value reported by `vulnerable`.

## EXAMPLE

```sh
make

# See help
./vulnerable
./collect-internal.pl
./collect-external.pl

# Collect some statistics
./collect-internal.pl 100 1000 100 > internal.csv
./collect-external.pl 1000 100 50 > external.csv

# Analyse the csv with any tool (e.g. R)
```
