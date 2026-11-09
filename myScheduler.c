/** @file myScheduler.c
 *  @author Zachary Thirkell
 *  @date 8/11/26
 *  @brief a simple scheduling app that runs in the microsoft terminal
 *  @version 1.3.0
 *  PATH = C:\Users\zacha\dev\myScheduler
 *  datafile location: C:\Users\zacha\dev\myScheduler\schedule.txt
*/

#include <stdio.h>
#include <string.h>

#define MAJOR 1
#define MINOR 3
#define PATCH 0

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

#define MAX_LINES 100
#define MAX_LINE_LENGTH 50
#define NAME_WIDTH 30
#define VIEW_LENGTH 59

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

void view(char lines[MAX_LINES][MAX_LINE_LENGTH], int count) {
    printf("\nName                           Reference Timestamp\n");
    printf("--------------------------------------------------\n");
    size_t i;
    for (i = 0; i < count; i++) {
        char display_string[VIEW_LENGTH];
        char name[NAME_WIDTH + 1];
        snprintf(name, sizeof name, "%s", lines[i] + 20);
        name[strcspn(name, "\r\n")] = '\0';
        snprintf(display_string, sizeof(display_string), "%-*s %.8s  %.2s:%.2s %.2s/%.2s %.4s\n",
                NAME_WIDTH, name,
                lines[i] + 12,
                lines[i] + 8,
                lines[i] + 10,
                lines[i] + 6,
                lines[i] + 4,
                lines[i]);
        printf("%s", display_string);
    }
    printf("\n");
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
                FILE* datafile = fopen(DATAFILE_ADDRESS, "r");
                char lines[MAX_LINES][MAX_LINE_LENGTH];
                int count = 0;
                while (count < MAX_LINES && fgets(lines[count], MAX_LINE_LENGTH, datafile)) {
                    count++;
                }
                fclose(datafile);
                if (operation == VW) {
                    view(lines, count);
                }
            }
        }
    } while (c != QUIT);
    printf("session terminated.\n");
    return 0;
}