#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define defline 10
#define Maxline 100
#define LINES 100


void error(char *s);
int mygetline(char *, int);

int main (int argc, char *argv[])
{
	char *p;
	char *buf;
	char *bufend;
	char line[Maxline];
	char *lineptr[LINES];
	int first, i, last, len, n, nlines;

	if (argc == 1)
		n = defline;
	else if (argc == 2 && (*++argv)[0] == '-')
		n = atoi(argv[0]+1);
	else 
		error("usage: tail [-n]");
	if (n < 1 || n > LINES)
		n = Maxline;
	for (i = 0; i < LINES; i++)
		lineptr[i] = NULL;
	if ((p = buf = malloc(LINES * Maxline)) == NULL)
		error("tail: cannot allocate buf");
	bufend = buf + LINES * Maxline;
	last = 0;
	nlines = 0;

	while ((len = mygetline(line, Maxline)) > 0){
		if (p + len + 1 >= bufend)
			p = buf;
		lineptr[last] = p;
		strcpy(lineptr[last], line);
		if (++last >= Maxline)
		   last = 0;

		p += len + 1;
		nlines++;
	}

	if (n > nlines)
		n = nlines;
	first = last - n;
	if (first < 0)
		first += Maxline;
	for (i = first; n-- > 0; i = (i+1)%Maxline)
		printf("%s\n", lineptr[i]);
	return 0;
}

void error(char *s)
{
	printf("%s\n", s);
	exit(1);
}
 int mygetline(char s[], int lim)
 {
 	int c, i, j;

 	j=0;
 	for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
 		if (i < lim-2){
 			s[j] = c;
 			++j;
 		}
 		if (c == '\n'){
 			s[j]=c;
 		    ++j;
 		    ++i;
 		}
 		s[j]='\n';
 		return i;
 }


