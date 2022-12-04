# Compilation

To compile all solutions, run from the root dir:

`make`

To clean up all compiled solutions, run from the root dir:

`make clean`

# Running

Since solutions typically rely on a hardcoded input filepath, you'll want to execute them in their own directory (making the executable "just work" in C was a bit too annoying). I just do something like this and it's not too terrible:

`cd src/day_01 && ./solution_01 && cd - > /dev/null`
