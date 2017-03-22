# `strcmp` Timing Attack

## Files

* `vulnerable.c` - Vulnerable program reporting number of cycles it spent
    comparing strings.
* `timestamp.c` - Program to measure the execution time of other programs. The
    resulting measured time is difference of timestamps between `fork`'ng and
    `wait`ing for child process completion. Timestamps are measured using
    `rdtcs` x86 instruction.
* `collect.pl` - Script for running a program multiple times and collecting
    timestamps provided by it in CSV format.

## Examples

Collecting the data is straightforward:

```sh
make

# See help
./vulnerable
./timestamp
./collect.pl

# Collect some statistics reported by ./vulnerable
./collect.pl ./vulnerable 100 1000 100 > internal.csv

# Collect some statistics on reported by ./timestamp
./collect.pl './timestamp ./vulnerable' 1000 100 50 > external.csv

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

# Notes

It turns out that some CPU's can automatically change their frequency. Such
uncontrolled random changes may introduce additional noise to measured delays.

To avoid that one may use tools like `cpupower` to set CPU frequency to a
constant value or, alternatively, disable frequency scaling in BIOS.

Also, measures like increasing the process priority with the `nice` program,
shutting down the `Xorg` server and putting down network interfaces have helped
me to reduce standard deviation of the measurements 1.5-2 times.
