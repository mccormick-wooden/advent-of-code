SRCS = $(shell find -name '*.c')
PROGS = $(patsubst %.c,%,$(SRCS))
CFLAGS = -Wall -fsanitize=leak

all: $(PROGS)

%: %.c
	gcc $(CFLAGS) -o $@ $<
clean:
	rm -f $(PROGS)