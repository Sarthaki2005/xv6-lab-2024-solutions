#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"
int
main(int argc, char *argv[])
{
int n_page=17;
char  *mem=sbrk(n_page*PGSIZE);
mem+=(n_page-1)*PGSIZE;
write(2,mem+32,8);
exit(1);
}
