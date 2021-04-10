#include<unistd.h>
#include<sys/uio.h>
#include<sys/types.h>
#include<fcntl.h>
#define MAXNAME 20
int fgetc(int fd);
void fprint(int fd);
int getname(char *s);
int main() {
    char fn[MAXNAME];
    int dl;
    int fd;
    while((dl=getname(fn))!=1) {
        fd=open(fn,O_RDONLY,0);
        fprint(fd);
        close(fd);
    }
    return 0;
}
int getname(char *s) {
    static int c;
    if(c=='\n')
        return 1;
    while((c=fgetc(STDIN_FILENO))==' '||c=='\t') {
        ;
    }
    if(c=='\n')
        return 1;
    *s++=c;
    while((c=fgetc(STDIN_FILENO))>=0&&c!=' '&&c!='\t'&&c!='\n') {
        *s++=c;
    }
    *s='\0';
    return 0;
}
void fprint(int fd) {
    int c;
    char ch;
    while((c=fgetc(fd))>=0) {
        ch=c;
        write(STDOUT_FILENO,&ch,sizeof(char));
    }
}
int fgetc(int fd) {
    char c;
    return read(fd,&c,sizeof(char))>0?(unsigned char)c:-1;
}