#include "_.h"
C m[sz]={0},*n[sz]={0},*r,*p=m,**sp=n,d=0,c;
V rs(){N(sz,{m[i]=0;n[i]=0;})p=m;sp=n;d=0;w_(1,"reset",5);}
V ev(C*s){r=s;for(;(c=*r);r++){C3(c,{$(d>0,d++){$(*p,*++sp=r){d=1;}}},{$(d,d--){$(*p,r=*sp){sp--;}},
{$$(d==0,C7(c,(*p)++,(*p)--,$(p+1==m+sz,p=m){p++;},$(p==m,p=m+sz-1){p--;},w_(1,p,1),_w(0,p,1),w_(1,man,sizeof(man)/sizeof(C)),rs(),{}))}})}}
V rp(){w_(1,"neko/bf 2025\n  ",15);for(;;){C s[sz]={0};I n=_w(0,s,sz-1);$$(n<=0,break)$(s[n-1]=='\n',s[--n]='\0'){s[n]='\0';}ev(s);w_(1,"\n  ",3);}}
V rd(C*s){I fd=d_((long)s,0,0);$$(fd<0,w_(2,"file not found\n",15);return)C bf[sz];I n=_w(fd,bf,sz-1);$$(n<=0,w_(2,"err\n",4);return)bf[n]='\0';ev(bf);w_(1,"\n",1);_d(fd);}
I main(I ac,C**av){$(ac==1,rp())$(ac==2,rd(av[1])){w_(2,"expect file\n",12);}}
