/** @file myScheduler.c
 *  @author Zachary Thirkell
 *  @date 8/11/26
 *  @brief a simple scheduling app that runs in the microsoft terminal
 *  @version 1.2.3
 *  PATH = C:\Users\zacha\dev\myScheduler
 *  datafile location: C:\Users\zacha\dev\myScheduler\schedule.txt
*/

#include <stdio.h>
#include <string.h>

#define MAJOR 1
#define MINOR 2
#define PATCH 3

#define MAX_COMMAND_LENGTH 100
#define MAX_TOKENS 5
#define QUIT 113

#define IS_VIEW_COMMAND (command[0] == 'v' && command[1] == 'w')
#define IS_SCHEDULE_COMMAND (command[0] == 's' && command[1] == 'c' && command[2] == 'h' && command[3] == ' ')
#define IS_RESCHEDULE_COMMAND (command[0] == 'r' && command[1] == 's' && command[2] == 'c' && command[3] == 'h' && command[4] == ' ')
#define IS_CANCEL_COMMAND (command[0] == 'c' && command[1] == 'n' && command[2] == 'c' && command[3] == ' ')
#define IS_CONFIGURE_COMMAND (command[0] == 'c' && command[1] == 'f' && command[2] == 'g' && command[3] == ' ')
#define IS_HELP_COMMAND (command[0] == 'h' && command[1] == 'e' && command[2] == 'l' && command[3] == 'p')

#define DATAFILE_ADDRESS "C:\\Users\\zacha\\dev\\myScheduler\\schedule.txt"

typedef enum {
    VW = 1,
    SCH,
    RSCH,
    CNC,
    CFG,
    HELP,
    ERROR
} Operation;

void help() {
    printf("\nAvailable commands             Syntax\n");
    printf("--------------------------------------------------------------------------------------------\n");
    printf("View bookings                  vw\n");
    printf("Make a new booking             sch <name> <24hr time>-<day>-<month>-<year>\n");
    printf("Move an existing booking       rsch <8-char reference code> <24hr time>-<day>-<month>-<year>\n");
    printf("Cancel an existing booking     cnc <8-char reference code> <24hr time>-<day>-<month>-<year>\n");
    printf("Blockout/unblockout time slot  cfg <24hr time>-<day>-<month>-<year>\n");
    printf("Get help                       help\n\n");
}

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
        if (c != QUIT) {
            Operation operation;
            if IS_VIEW_COMMAND {
                operation = VW;
                printf("'View' command identified.\n");
            } else if IS_SCHEDULE_COMMAND {
                operation = SCH;
                printf("'Schedule' command identified.\n");
            } else if IS_RESCHEDULE_COMMAND {
                operation = RSCH;
                printf("'Reschedule' command identified.\n");
            } else if IS_CANCEL_COMMAND {
                operation = CNC;
                printf("'Cancel' command identified.\n");
            } else if IS_CONFIGURE_COMMAND {
                operation = CFG;
                printf("'Configure' command identified.\n");
            } else if IS_HELP_COMMAND {
                operation = HELP;
            } else {
                operation = ERROR;
            }
            if (operation == HELP) {
                help();
            } if (operation == ERROR) {
                printf("ERROR: Operation not recognised\n");
            } else {
                FILE* datafile = fopen(DATAFILE_ADDRESS, "r+");
                fclose(datafile);
            }
        }
    } while (c != QUIT);
    printf("session terminated.\n");
    return 0;
}