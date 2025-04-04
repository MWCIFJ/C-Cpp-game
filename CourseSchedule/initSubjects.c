#include"initSubjects.h"
#include"functions.h"

const char *weekDays[days] = {"周一", "周二", "周三", "周四", "周五", "周六"};

Subject subjects[subjectsCount] = {     //初始化结构体数组
    {"Chinese", 0, true, false},
    {"Math", 0, true, false},
    {"English", 0, true, false},
    {"Physics", 0, false, false},
    {"Chemistry", 0, false, false},
    {"Biology", 0, false, false},
    {"Computer", 0, false, false},
    {"A", 0, false, false},
    {"B", 0, false, false},
    {"C", 0, false, false},
    {"D", 0, false, false},
    {"E", 0, false, false},
};

void initSortSubjects(Subject subjects[], Map *map) {
    for (int i = 0; i < days; i++)
        for (int j = 0; j < number; j++)
            map->maptable[i][j] = -1;	//-1代表空课
}