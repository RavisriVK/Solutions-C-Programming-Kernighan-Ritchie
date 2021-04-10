#include<fcntl.h>
#include<unistd.h>
//#include<sys/uio.h>
//#include<sys/types.h>
#include<stdlib.h>

#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20

typedef struct _iobuf {
    int cnt;
    char *ptr;
    char *base;
    int flag;
    int fd;
} FILE;

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

enum _flags {
    _READ=01,
    _WRITE=02,
    _UNBUF=04,
    _EOF=010,
    _ERR=020
};

FILE _iob[OPEN_MAX]= {
    {0,NULL,NULL,_READ,0},
    {0,NULL,NULL,_WRITE,1},
    {0,NULL,NULL,_READ|_WRITE,2}
};

int _fillbuf(FILE *);

#define feof(p) ((p)->flag==_EOF)
#define ferror(p) ((p)->flag==_ERR)
#define fileno(p) ((p)->fd)

#define getc(p) ( --(p)->cnt>=0 \
            ?  *(p)->ptr++ : _fillbuf(p) ) //for read mode-used as many times as there are elements in buffer
#define putc(x,p) ( --(p)->cnt>=0 \
            ?  (*(p)->ptr++ = (x)) : _flushbuf((x),p) )

#define getchar() getc(stdin)
#define putchar(x) putc((x),stdout)

#define PERMS 0666

FILE *fopen(char *name, char *mode) {
    int fd;
    FILE *fp;

    if(*mode!='r'&&*mode!='w'&&*mode!='a')
        return NULL;
    for( fp=_iob ; (fp-_iob)<OPEN_MAX ; fp++)
        if(fp->flag!=_READ&&fp->flag!=_WRITE)
            break;
    if((fp-_iob)>=OPEN_MAX)
        return NULL;
    if(*mode=='w')
        fd=creat(name,PERMS);
    else if(*mode=='a') {
        if((fd=open(name,O_WRONLY,0))==-1)
            fd=creat(name,PERMS);
        lseek(fd,0L,2);
    } else
        fd=open(name,O_RDONLY,0);
    if(fd==-1)
        return NULL;
    
    fp->fd=fd;
    fp->base=NULL;
    fp->cnt=0;
    fp->flag=(*mode=='r')?_READ:_WRITE;
    return fp;
}

int _fillbuf(FILE *fp) {
    if(fp->flag!=_READ&&fp->flag!=_WRITE&&fp->flag!=_EOF)
        return EOF;
    //should be BUFSIZ but for safety, it is the number of bytes read into the buffer
    int bufsize=(fp->flag==_UNBUF)?1:BUFSIZ;
    if(fp->base==NULL)
        if((fp->base=(char *)malloc(BUFSIZ*sizeof(char)))==NULL)
            return EOF;
    fp->ptr=fp->base;
    fp->cnt=read(fp->fd,fp->base,bufsize); //read returns 0 if it hits end of file, or -1 if there is an error
    if(--fp->cnt<0) {
        if(fp->cnt==-1)
            fp->flag=_EOF;
        else
            fp->flag=_ERR;
        fp->cnt=0;
        return EOF;
    }
    return (unsigned char)*fp->ptr++;
} 

void fprint(FILE *p) {
    int c;
    char ch;
    while((c=getc(p))>=0) {
        ch=c;
        write(stdout->fd,&ch,sizeof(char));
    }
}

int main() {
    FILE *p;
    p=fopen("test1.txt","r");
    fprint(p);
}