# `strcmp` Timing Attack

## Files

* `vulnerable.c` - Vulnerable program reporting number of cycles it spent
    comparing strings.
* `timestamp.c` - Program to measure the execution time of other programs. The
    resulting measured time is difference of timestamps between `fork`'ng and
    `wait`ing for child process completion. Timestamps are measured using
    `rdtcs` x86 instruction.
* `collect-internal.pl` - Script for running `vulnerable` multiple times and
    collecting timestamps provided by it in CSV format.
* `collect-external.pl` - The same as `collect-internal.pl`, but measures
    cycles using `timestamp` instead of relying of value reported by `vulnerable`.

## Examples

Collecting the data is straightforward:

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
R
```

Here is an example of simple R commands to analyse collected statistics:

```R
s = read.csv('some_file.csv')

# Plot all the samples
plot(s$cycles, s$length)

# Find the correlation between cycles count and length of matched string
cor(s$cycles, s$length)

# Find the averages
t = aggregate(s$cycles, list(s$length), mean)

# Plot the average values
plot(t$x, t$Group.1)
```
