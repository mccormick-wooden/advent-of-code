[Advent of Code](https://adventofcode.com/) solutions using Very Bad C Programming with holiday-themed flair.

### Compilation

To compile all solutions, run from the root dir:

`make`

To clean up all compiled solutions, run from the root dir:

`make clean`

### Running

Since solutions typically rely on a hardcoded input filepath, you'll want to execute them from the directory that includes their `input.txt`, which should be the same directory as the executable. Otherwise, the executable won't be able to find the input file. Making the executable "just work" with an arbitrary working directory in C was a bit too annoying.

I just do something like this from root dir and it's not too terrible:

`cd src/day_01 && ./solution_01 && cd - > /dev/null`
