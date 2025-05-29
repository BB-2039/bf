typedef int I;typedef void V;typedef char C;
#define Z static
#define $(b,a...) if(b){a;}else
#define $$(b,a...) if(b){a;}
#define O(f,i) I __attribute((naked))f(long, ...){asm("mov %rcx,%r10;mov $"#i",%rax;syscall;ret");}
Z O(_w,0) Z O(w_,1) Z O(_d,3) Z O(d_,2)
#define sz 30000
