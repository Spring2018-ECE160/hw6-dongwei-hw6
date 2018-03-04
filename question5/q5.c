#include <stdio.h>

struct stu{
    char *name;  
 
    int tuition;  
}stus[] = {
    {"Sarah Lawrence College", 61236},
    {"New York University   ", 59837},
    {"The New School        ", 57340},
    {"Columbia University   ", 58742},
    {"Barnard College       ", 57312}
}, *ps;


void average(struct stu *ps, int len);

int main(){
    //求数组长度
    int len = sizeof(stus) / sizeof(struct stu);
    printf("\nThe Most Expensive Colleges in New York:\n");
    printf("Name\t\t\t\t\tTuition($)\t\n");
    for(ps=stus; ps<stus+len; ps++){
        printf("%s\t\t\t%d\t\n", ps->name, ps->tuition);
    }
    average(stus, len);

    return 0;
}

void average(struct stu *ps, int len){
    int i, num_6 = 0;
    float average, sum = 0;
    for(i=0; i<len; i++){
        sum += (ps + i) -> tuition;
        if((ps + i)->tuition > 60000) num_6++;
    }
    printf("\naverage=%.2f\nnumber of college that tuition above 60000/yr =%d\n\n", sum/5, num_6);
}