#include<kernel/types.h>
#include<user/user.h>
#include<kernel/stat.h>
#include<kernel/fs.h>
#include<kernel/fcntl.h>
char* fmtname(char* path){
static char buf[DIRSIZ+1];
char* p;
for(p=path+strlen(path);p>=path && *p!='/';p--);
p++;
memmove(buf,p,DIRSIZ);
buf[DIRSIZ]='\0';
return buf;
}

void find(char* path,char* target){
int fd;
char buf[512],*p;
struct dirent de;
struct stat st;
if((fd=open(path,O_RDONLY))<0){
fprintf(2,"cannot open %s\n",path);
return;
}
if(fstat(fd,&st)<0){
fprintf(2,"Cannot stat %s\n",path);
close(fd);
return;
}
switch(st.type){
case T_FILE: {
    char* name = fmtname(path);
    printf("DEBUG: comparing '%s' with target '%s'\n", name, target);
    if(strcmp(name, target) == 0) {
        printf("%s\n", path);
    }
close(fd);
    break;
}

//case T_FILE:
//char* name=fmtname(path);
//if(strcmp(name,target)==0){
//printf("%s\n",path);
//}
//close(fd);
//break;
case T_DIR:
 if(strlen(path)+1+DIRSIZ+1>sizeof(buf)){
 printf("path is too long\n");
 break;
}
strcpy(buf,path);
p=buf+strlen(buf);
*p++='/';
while(read(fd,&de,sizeof(de))==sizeof(de)){
if(de.inum==0) continue;
if(strcmp(de.name,".")==0 || strcmp(de.name,"..")==0) continue;
memmove(p,de.name,DIRSIZ);
p[DIRSIZ]='\0';
find(buf,target);
}
close(fd);
break;
}

}

int main(int argc,char* argv[]){
if(argc<3){
printf("Enter valid arguments");
exit(1);
}
find(argv[1],argv[2]);
exit(0);
}
