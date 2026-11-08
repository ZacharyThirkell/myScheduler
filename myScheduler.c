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
#define PATCH 7

#define MAX_COMMAND_LENGTH 100
#define QUIT 113

int main(int argc, char *argv[]) {

    if (argc < 2 || strcmp(argv[1], "run") != 0) {
        printf("Usage: myScheduler run\n");
        return 1;
    }
    printf("myScheduler v%d.%d.%d initialised.\n", MAJOR, MINOR, PATCH);
    char c;
    char command[MAX_COMMAND_LENGTH];
    do {
        printf("myScheduler> ");
        fflush(stdout);
        if (!fgets(command, MAX_COMMAND_LENGTH, stdin)) {
            break;
        }
        c = command[0];
    } while (c != QUIT);
    printf("Session terminated.\n");
    return 0;
}