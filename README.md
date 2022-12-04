# Compilation

To compile all solutions, run from the root dir:
`make`

To clean up all compiled solutions, run from the root dir:
`make clean`

# Running

Since solutions typically rely on a hardcoded input filepath, you'll want to execute them in their own directory, because make the executable "just work" in C is too annoying. You can just do something like this from root dir:
`cd src/day_01 && ./solution_01 && cd - > /dev/null`