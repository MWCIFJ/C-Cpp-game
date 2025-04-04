#ifndef FUNCTIONS_H
#define FUNCTIONS_H
void scanfSubjects(Subject subjects[],Map *map);
void initSortSubjects(Subject subjects[],Map *map);
bool isScheduledToday(int day,int index, Map *map);
void sortSubject(Subject subjects[], Map *map);
void printSubjects(Subject subjects[],Map *map);
#endif //FUNCTIONS_H
