void calc_pi(){int a=1e4,c=3e3,b=c,d=0,e=0,f[3000],g=1,h=0;
for(;b;!--b?printf("%04d",e+d/a),e=d%a,h=b=c-=15:f[b]=
(d=d/g*b+a*(h?f[b]:2e3))%(g=b*2-1));}