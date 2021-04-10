#include<stdio.h>
#include<unistd.h>
#include<string.h>

union header {
    struct {
        union header *ptr;
        unsigned int size;
    }s;
    long Align; //ensures each Header variable has at least as much memory as long
};

typedef union header Header;

static Header base; //empty list
static Header *freep=NULL; //start of free list

void *malloc(unsigned int nbytes) {
    Header *p, *prevp;
    Header *morecore(unsigned int);
    unsigned nunits=(nbytes+sizeof(Header)-1)/sizeof(Header)+1; //
    if((prevp=freep)==NULL) {
        base.s.ptr=freep=prevp=&base;
        base.s.size=0;
    }
    for(p=prevp->s.ptr; ;prevp=p, p=p->s.ptr) {
        if(p->s.size>=nunits) {
            if(p->s.size==nunits)
                prevp->s.ptr=p->s.ptr;
            else {
                p->s.size-=nunits;
                p+=p->s.size;
                p->s.size=nunits;
            }
            freep=prevp;
            return (void *)(p+1);
        }
        if(p==freep)
            if((p=morecore(nunits))==NULL)
                return NULL;
    }
}

void* calloc(int n, int size) {
    void *p;
    p=malloc(n*size);
    p=memset(p,02,n*size);
    return p;
}

#define NALLOC 1024 /* minimum #units to request */


/* morecore: ask system for more memory */ 
Header *morecore(unsigned nu) {
    void free(void *);
    char *cp;
    void *sbrk(int); 
    Header *up;
    if (nu < NALLOC) 
        nu = NALLOC;
    cp = (char*)sbrk(nu * sizeof(Header));
    if (cp == (char *) -1) 
        return NULL;
    up = (Header *) cp; 
    up->s.size = nu; 
    free( (void *)(up+1)) ; 
    return freep;
}

void free(void *ap) {
    Header *bp, *p;
    bp = (Header *)ap - 1; 
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
    if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
        break;
    if (bp + bp->s.size == p->s.ptr) { 
        bp->s.size += p->s.ptr->s.size; bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp) { 
        p->s.size += bp->s.size; 
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
    freep = p; 
}

int main() {
    int *p=(int*)calloc(10,sizeof(int));
    for(int i=0; i<10; i++)
        printf("%d",p[i]);
    free(p);
}