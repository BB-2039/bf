CC      = gcc
CFLAGS  = -O3 -fno-stack-protector -fno-builtin -ffreestanding -nostdlib
LDFLAGS = -Wl,--gc-sections -Wl,--strip-all
TARGET  = m
OBJS    = m.o

all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

clean:
	rm -f $(TARGET) $(OBJS)
