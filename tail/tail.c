#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define DEFAULT_LINES 10
#define ILLEGAL_TAG_CODE -51
#define ERROR_CODE -52

char buf[5120];

int getLineNumberToPrint(char* argvs[]) {
    char** argv = argvs;
    int i = 1;
    char number[100];

    if(argv[1][0] == '-') {
        for(i=1; i < strlen(argv[1]); i++) {
            if(((int)(argv[1][i])) >= 48 && ((int)(argv[1][i])) <= 57) {
                number[i-1] = argv[1][i];
            }
            else {
                return ILLEGAL_TAG_CODE;
            }
        }
        int lines = atoi(number);
        return lines;
    }
    else {
        return ERROR_CODE;
    }
}

void tailFile(int fd, int linesToPrint) {
    int i, n;
    int fileLines = 0;
    int tempLinesRead = 0;
    int tempFile = open("temp", O_CREATE | O_RDWR);

    while((n = read(fd, buf, sizeof(buf))) > 0) {
        write(tempFile, buf, n);
        for(i = 0; i < n; i++) {
            if(buf[i] == '\n')
                fileLines++;
        }
    }
    close(tempFile);

    int startPrintIndex = fileLines - linesToPrint;
    tempFile = open("temp", O_RDONLY);
    while((n = read(tempFile, buf, sizeof(buf))) > 0) {
        for(i=0; i<n; i++) {
            if(tempLinesRead >= startPrintIndex) {
                printf(1, "%c", buf[i]);
            }
            if(buf[i] == '\n') {
                tempLinesRead++;
            }
        }
    }
    unlink("temp");
}

int main(int argc, char *argv[]) {
    int fd, lines;
    
    if(argc <= 1) {
        tailFile(0, DEFAULT_LINES);
        exit();
    }
    else if(argc == 2) {
        lines = getLineNumberToPrint(argv);
        fd = open(argv[1], O_RDONLY);

        if(fd >= 0) {
            tailFile(fd, DEFAULT_LINES);
            close(fd);
            exit();
        }
        else if((fd < 0) && (lines == ILLEGAL_TAG_CODE)) {
            printf(1, "Illegal tag\n");
            exit();
        }
        else if(fd < 0 && lines == ERROR_CODE) {
            printf(1, "tail: cannot open %s\n", argv[1]);
            exit();
        }
        else if((fd < 0) && ((lines % 2 == 0) || (lines % 2 == 1))) {
            tailFile(0, lines);
            exit();
        }
        else if(fd < 0) {
            printf(1, "tail: cannot open %s\n", argv[1]);
        }
    }
    else if(argc == 3) {
        lines = getLineNumberToPrint(argv);

        if((fd = open(argv[2], O_RDONLY)) < 0) {
            printf(1, "tail: cannot open %s\n", argv[2]);
            exit();
        }
        if(lines == ILLEGAL_TAG_CODE) {
            printf(1, "Illegal tag\n");
            exit();
        }
        lines = ((lines == ERROR_CODE) ? DEFAULT_LINES : lines);
        tailFile(fd, lines);
        close(fd);
        exit();
    }
    else {
        printf(1, "tail: cannot open %s\n", argv[2]);
        exit();
    }
    exit();
}
