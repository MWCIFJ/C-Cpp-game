#include"initSubjects.h"
#include"functions.h"

bool isScheduledToday(int day, int index, Map *map) {	//是否可以被放置
    for (int j = 0; j < number; j++)
        if (map->maptable[day][j] == index)
            return true;
    return false;
}

void sortSubject(Subject subjects[], Map *map) {
    for (int i = 0; i < subjectsCount; i++) {		//排主科
        if (subjects[i].major) {
            for (int j = 0; j < subjects[i].count; j++) {
                int day, period;
                do {
                    day = rand() % days;
                    period = rand() % (morning-1);	//只能排上午
                } while (isScheduledToday(day, i, map) || map->maptable[day][period] != -1);//注意while真是会循环的，所以该是||
                map->maptable[day][period] = i;
                subjects[i].isListen = true;
            }
        }
    }

    for (int i = 0; i < subjectsCount; i++) {		//排副科
        if (!subjects[i].major) {
            for (int j = 0; j < subjects[i].count; j++) {
                int day, period;
                do {
                    day = rand() % days;
                    period = rand() % (number-2);	//最后两节都是考试
                } while (isScheduledToday(day, i, map) || map->maptable[day][period] != -1);
                map->maptable[day][period] = i;
                subjects[i].isListen = true;
            }
        }
    }
}