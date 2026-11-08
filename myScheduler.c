/** @file myScheduler.c
 *  @author Zachary Thirkell
 *  @date 8/11/26
 *  @brief a simple scheduling app that runs in the microsoft terminal
 *  @version 1.0.0
 *  PATH = C:\Users\zacha\dev\myScheduler
*/

#include <stdio.h>
#include <string.h>

#define MAJOR 1
#define MINOR 1
#define PATCH 1

int main(int argc, char *argv[]) {

    if (argc < 2 || strcmp(argv[1], "run") != 0) {
        printf("Usage: myScheduler run (runs the scheduler executable)");
        return 1;
    }
    printf("myScheduler v%d.%d.%d initialised.\n\n", MAJOR, MINOR, PATCH);
    return 0;
}