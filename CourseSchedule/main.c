#include"initSubjects.h"
#include"functions.h"

int main() {
	Map map;
	extern Subject subjects[subjectsCount];
	scanfSubjects(subjects,&map);
	initSortSubjects(subjects, &map);
	sortSubject(subjects, &map);
	printSubjects(subjects, &map);
	return 0;
}

//cin:6 6 6 5 5 4 3 1 1 1 1 1