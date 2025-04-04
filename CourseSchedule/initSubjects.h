#ifndef SORTSUBJECTS_H
#define SORTSUBJECTS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
//确定一周上课天数、一天几节课、上午几节、学科总数
#define days 6
#define number 9
#define morning 5
#define subjectsCount 12

typedef struct {
    char name[10];	//学科名字
    int count;		//这科有几节
    bool major;		//是否是主科
    bool isListen;	//当日是否使用
} Subject;

typedef struct {
    int maptable[days][number];
} Map;	//课程表

#endif //SORTSUBJECTS_H
