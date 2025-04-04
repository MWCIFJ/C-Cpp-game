#include"initSubjects.h"
#include"functions.h"
extern const char *weekDays[days];

void scanfSubjects(Subject subjects[], Map *map)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < subjectsCount; i++)
    {
        printf("输入%s每周上课节数：", subjects[i].name);
        scanf("%d", &subjects[i].count);
    }
}

void printSubjects(Subject subjects[], Map *map)
{
    printf("\n------------------课程表------------------\n");
    for (int i = 0; i < days; i++) {
        printf("%s: ", weekDays[i]);
        for (int j = 0; j < number; j++) {
            if (map->maptable[i][j] != -1)
                printf("%s ", subjects[map->maptable[i][j]].name);
            else if(j == number-1 || j == number-2)
                printf("考试 ");
            else
                printf("自习 ");
        }
        printf("\n");
    }
}