OS := $(shell uname -s | tr A-Z a-z)
SRCS = $(shell find . -name '*.c')
PROGS = $(patsubst %.c,%,$(SRCS))
CFLAGS = -Wall -Wextra -Werror -fsanitize=leak
CC :=
ifeq ($(OS),darwin)
	CC = gcc-12
else
	CC = gcc
endif

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<
clean:
	rm -f $(PROGS)
