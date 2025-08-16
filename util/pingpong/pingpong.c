#include "kernel/types.h"
#include "user/user.h"
int main(void){
int p1[2];
int p2[2];
pipe(p1);
pipe(p2);
char buf[15];
if(fork()==0){
close(p1[1]);
close(p2[0]);
//read from parent into buf
if(read(p1[0],buf,1)){
printf("%d: received ping\n",getpid());
}
close(p2[0]);
//write to parent
write(p2[1],buf,1);
close(p2[1]);
exit(0);

}else{
close(p1[0]);
close(p2[1]);
//write to child
write(p1[1],"h",1);
close(p1[1]);
wait(0);
//wait for child to write back
if(read(p2[0],buf,1)){
printf("%d: received pong\n",getpid());
}
exit(0);
}
}
