typedef int I;typedef void V;typedef char C;
#define o(o) __builtin_##o
#define pf o(printf)
#define sf o(scanf)
#define _(z) ({z;})
#define W(z) while(_(z))
#define N(n,a...) {I i=0,_n=(n);W(i<_n){a;++i;}}
#define $(b,a...) if(b){a;}else
#define $$(b,a...) if(b){a;}
#define R return
#define C10(z,a,b,c,d,e,f,g,h,i,j) switch(z){case '+':{a;break;}case '-':{b;break;}case '>':{c;break;}case '<':{d;break;}case ',':{e;break;}case '.':{f;break;}case '[':{g;break;}case ']':{h;break;}case '/':{i;break;}default:{j;}}
//#define C3(z,a,b,c) switch(z){case 1:{a;break}case 2:{b;break;}default:{c;}}
#define sz 30000
#define tpr tp[ptr]
