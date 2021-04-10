#include<stdio.h>
#include<stdlib.h>
#define MAXLENGTH 100

int getLine(char s[], int lim)
{
    int c=getchar();
    int i;
    for(i=0;(c!='\n'&&c!=EOF)&&(i<lim-1);++i)
    {
        s[i]=c;
        c=getchar();
    }
    if(c=='\n') {
        s[i]='\n';
        ++i;
    }
    s[i]='\0';
    return i;
}

//ENTAB
int main(int argc, char *argv[]) {
    int n=argc;
    int tabstops[n];
    tabstops[0]=0;
    for(int i=1; i<n; i++) {
        tabstops[i]=atoi(argv[i]);
    }
    char line[MAXLENGTH];
    int length;
    int position;
    int start, end;
    int nearest;
    while((length=getLine(line,MAXLENGTH))) {
        position=0;
        for(int i=0; i<length; i++) {
            if(line[i]!=' '&&line[i]!='\t') {
                putchar(line[i]);
                position++;
            } else {
                start=position;
                for(;line[i]==' '||line[i]=='\t';i++) {
                    if(line[i]==' ') {
                        position++;
                    } else {
                        for(int j=0; j<n-1; j++) {
                            if(position>=tabstops[j]&&position<tabstops[j+1]) {
                                position=tabstops[j+1];
                                break;
                            }
                        }
                    }
                }
                i--;
                end=position;
                for(int j=0; j<n-1; j++) {
                    if(end>=tabstops[j]&&end<tabstops[j+1]) {
                        nearest=tabstops[j];
                        break;
                    }
                }
                if(nearest<=start) {
                    for(int j=0; j<end-start; j++)
                    printf("<S>");
                } else {
                    for(int j=0; j<n-1; j++) {
                        if(end>=tabstops[j]&&start<tabstops[j]) {
                            printf("<T>");
                        }
                    }
                    for(int j=0; j<end-nearest; j++)
                    printf("<S>");
                }
            }
        }
    }
}

//DETAB
/*int main(int argc, char *argv[]) {
    int n=argc;
    int tabstops[n];
    tabstops[0]=0;
    for(int i=1; i<n; i++) {
        tabstops[i]=atoi(argv[i]);
    }
    
    char line[MAXLENGTH];
    int length;
    int position;
    int nearest;

    while((length=getLine(line,MAXLENGTH))) {
        position=0;
        for(int i=0; i<length; i++) {
            if(line[i]!='\t') {
                putchar(line[i]);
                position++;
            } else {
                nearest=position+1;
                for(int j=0; j<n-1; j++) {
                    if(position>=tabstops[j]&&position<tabstops[j+1]) {
                        nearest=tabstops[j+1];
                        break;
                    }
                }
                for(int j=0; j<nearest-position; j++)
                putchar(' ');
                position=nearest;
            }
        }
    }
}*/