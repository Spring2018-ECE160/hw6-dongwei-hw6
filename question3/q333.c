#include<stdio.h>
#include <string.h>
#include <ctype.h>

// K&R Pg. 108-109, 119-121
#define NUME 1
#define DECR 2
#define FOLD 4
#define LINES 100
#define MAXLEN 1000
#define MAXLINES 5000
#define ALLOCSIZE 10000 // size of available space

// globals
char *lineptr[MAXLINES]; // pointers to text lines
static char allocbuf[ALLOCSIZE]; // storage for alloc
static char *allocp = allocbuf;  // next free position

// functions
int charcmp(char *, char *);
int numcmp(char *s1, char *s2);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int decr);
void qsort(void *lineptr[], int left, int right, 
           int (*comp)(void *, void *));

// sort input lines
static char option = 0;


int main(int argc, char *argv[])
{
    char *lineptr[LINES];
    int nlines;
    int c, rc = 0;

    while (--argc > 0 && (*++argv)[0] == '-')
        while (c = *++argv[0])
            switch(c){
            case 'f':
                option |= FOLD;
                break;
            case 'n':
                option |= NUME;
                break;
            case 'r':
                 option |= DECR;
                 break;
            default:
                 printf("sort: illegal option %c\n", c);
                 argc =1;
                 rc = -1;
                 break;

            }
        if (argc)
            printf("Usage: sort -nr\n");
        else
            if ((nlines = readlines(lineptr, LINES))>0){
                if (option & NUME)
                    qsort((void **) lineptr, 0, nlines-1, (int (*) (void *, void *)) numcmp);
                else if (option & FOLD)
                    qsort((void **) lineptr, 0, nlines-1, (int (*) (void *, void *)) charcmp);
                else 
                    qsort((void **) lineptr, 0, nlines-1, (int (*) (void *, void *)) strcmp);
                writelines(lineptr, nlines, option & DECR);

            } else {
                printf("input too big to sort \n");
                rc = -1;

            }
        return rc;
}

int charcmp(char *s, char *t)
{
    for ( ; tolower(*s) == tolower(*t); s++, t++)
        if (*s == '\0')
            return 0;
    return tolower(*s) - tolower(*t);
}
#define MAXLEN 1000 // max length of any input line
int mygetline(char *, int);
char *alloc(int);

// readlines: read input lines
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = mygetline(line, MAXLEN)) > 0)
    {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else
        {
            line[len-1] = '\0'; // delete newlines
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}



char *alloc(int n) // return pointer to n characters
{
    if (allocbuf + ALLOCSIZE - allocp >= n) // it fits
    {
        allocp += n;
        return allocp - n; // old p
    }
    else // not enough room
        return 0;
}

void afree(char *p) // free storage pointed to by p
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}


// mygetline: get line into s, return length
int mygetline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

// qsort:sort v[left]...v[right] into increasing order
void qsort(void *v[], int left, int right, 
           int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *v[], int, int);

    // do nothing if array contains fewer than two elements
    if (left >= right)
        return;
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if ((*comp)(v[i], v[left]) <0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1, comp);
    qsort(v, last+1, right, comp);
}

// swap:interchange v[i] and v[j]
void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}


// writelines: write output lines
void writelines(char *lineptr[], int nlines, int decr)
{
    int i;
    if (decr)
        for (i = nlines-1; i >= 0; i --)
            printf("%s\n", lineptr[i] );
    else
        for (i=0; i < nlines; i++)
            printf("%s\n", lineptr[i]);
}

// compare s1 and s2 numerically
/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}