m:
	gcc -O3 -fno-stack-protector -fno-builtin -ffreestanding -nostdlib -Wl,--gc-sections -Wl,--strip-all -static m.c -o m
mu: m
	upx --best m
