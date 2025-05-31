#include "_.h"
V ev(C*s){C m[sz],*n[sz],*r=s,*p=m,**sp=n,d=0,c;for(;(c=*r);r++) c-']'||(d>1||(r=*p?*sp:(--sp,r)),!d||d--),c-'['||d++||(*++sp=r),d||(*p+=c=='+',*p-=c=='-',p=c=='>'?(p+1==m+sz?m:p+1):(c=='<'?(p==m?m+sz-1:p-1):p),c-'.'||w_(1,p,1),c-','||_w(0,p,1)),c-'|'||w_(1,"+- >< ., []",11);}
V rp(){w_(1,"mtx/bf 2025\n  ",14);for(;;){C s[sz]={0};I n=_w(0,s,sz-1);$$(n<=0,break)$(s[n-1]=='\n',s[--n]='\0'){s[n]='\0';}ev(s);w_(1,"\n  ",3);}}
V rd(C*s){I fd=d_((long)s,0,0);$$(fd<0,w_(2,"err\n",4);return)C bf[sz];I n=_w(fd,bf,sz-1);$$(n<=0,w_(2,"err\n",4);return)bf[n]='\0';ev(bf);w_(1,"\n",1);_d(fd);}
I main(I ac,C**av){$(ac==1,rp())$(ac==2,rd(av[1])){w_(2,"err\n",4);}}
