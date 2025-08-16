
#include"kernel/types.h"
#include"user/user.h"
void primes(int fd){
int p;
if(read(fd,&p,sizeof(p))!=sizeof(p)){
close(fd);
exit(0);
}
printf("prime %d\n",p);
int p1[2];
pipe(p1);
if(fork()==0){
close(p1[1]);
close(fd);
primes(p1[0]);
close(p1[0]);
exit(0);
}
else{
close(p1[0]);
int n;
while(read(fd,&n,sizeof(n))!=0){
if(n%p!=0){
write(p1[1],&n,sizeof(n));
}
}
close(p1[1]);
close(fd);
wait(0);
}
exit(0);
}

int main(void){
int p2[2];
pipe(p2);
if(fork()==0){
close(p2[1]);
primes(p2[0]);
close(p2[0]);
exit(0);
}
else{
close(p2[0]);
for(int i=2;i<=280;i++){
write(p2[1],&i,sizeof(int));
}
close(p2[1]);
wait(0);
}
exit(0);
}
