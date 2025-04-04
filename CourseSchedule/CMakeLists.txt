cmake_minimum_required(VERSION 3.30)
project(CourseSchedule C)

set(CMAKE_C_STANDARD 23)

add_executable(CourseSchedule main.c
        initSubjects.c
        initSubjects.h
        sortSubjects.c
        scanAndPrint.c
        functions.h)
