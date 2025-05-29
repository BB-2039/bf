CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = m
SRCS = m.c

$(TARGET): $(OBJS)
	$(CC) $(SRCS) $(CFLAGS) -o $@ $(OBJS)
