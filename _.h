typedef int I;typedef void V;typedef char C;
#define Z static
#define $(b,a...) if(b){a;}else
#define $$(b,a...) if(b){a;}
#define _(z) ({z;})
#define W(z) while(_(z))
#define N(n,a...) {I i=0,_n=(n);W(i<_n){a;++i;}}
#define O(f,i) I __attribute((naked))f(long, ...){asm("mov %rcx,%r10;mov $"#i",%rax;syscall;ret");}
Z O(_w,0) Z O(w_,1) Z O(_d,3) Z O(d_,2)
#define man " +   -    >     <     .    ,  [   ]   !\ninc dec rmove lmove putc read loops reset"
#define sz 30000
#define C3(z,a,b,c) switch(z){case '[':{a;break;}case ']':{b;break;}default:{c;break;}}
#define C7(z,a,b,c,d,e,f,g,h,i) switch(z){case '+':{a;break;}case '-':{b;break;}case '>':{c;break;}case '<':{d;break;}case '.':{e;break;}case ',':{f;break;}case '?':{g;break;}case '!':{h;break;}default:{i;break;}}
