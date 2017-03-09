# `strcmp` Timing Attack

## FILES

* `vulnerable.c` - Vulnerable program reporting number of cycles it spent
    comparing strings.
* `collect-stats.pl` - Script for running `vulnerable` multiple times and
    collecting the data in CSV format.

## EXAMPLE

```sh
make

# See help
./vulnerable
./collect-stats.pl

# Collect some statistics
./collect-stats.pl 100 1000 100 > data.csv

# Analyse the csv with any tool (e.g. R)
```
