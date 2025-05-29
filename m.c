#include "_.h"
C tp[sz]={0};I ptr=0;
V ev(C*s){I l=o(strlen)(s);N(l,C10(s[i],tpr=(tpr==255)?0:tpr+1,tpr=(tpr==0)?255:tpr-1,$(ptr==sz-1,ptr=0){ptr++;},$(ptr==0,ptr=sz-1){ptr--;},{C c;sf("%c",&c);tpr=(c==-1)?0/*??*/:c;},pf("%c",tpr),$$(tpr==0,{I v=1;W(v&&++i<l){$(s[i]=='[',++v)$$(s[i]==']',--v)}}),$$(tpr!=0,{I v=1;W(v&&--i>=0){$(s[i]==']',++v)$$(s[i]=='[',--v)}}),pf("+-><,.[]\n"),{}))}
V rp(){W(1){C s[sz]={0};sf("%s",s);ev(s);pf("\n");}}
I main(){rp();R 0;}
