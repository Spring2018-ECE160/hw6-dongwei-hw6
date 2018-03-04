#include <stdio.h>


struct{
 
   
    int score;  //成绩
}class[] = {
    {-1},
    {-2},
    {-3},
    {-4},
    {-5},
    {0},
    {1},
    {2},
    {3},
    {4},
    {5}
};
int main(){
    int i;
    int y;
    int a, b, c;
    printf("Please Enter Value of a:");
    scanf("%d", &a);
    printf("Please Enter Value of b:");
    scanf("%d", &b);
    printf("Please Enter Value of c:");
    scanf("%d", &c);
    for(i=0; i<11;){
        y = a*class[i].score*class[i].score+b*class[i].score+c;
        printf("%d\t %d\t\n", class[i].score, y);
        i++;
    }
    
    return 0;
}