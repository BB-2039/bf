CC = gcc
CFLAGS = -O3
TARGET = m
SRCS = m.c

$(TARGET): $(OBJS)
	$(CC) $(SRCS) $(CFLAGS) -o $@ $(OBJS)
