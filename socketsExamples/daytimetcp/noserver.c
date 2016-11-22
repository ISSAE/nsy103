/*
 *
 *      Author: Pascal Fares
 */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv) {
    char buff[80 * 100];
    time_t ticks;


        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        write(0, buff, strlen(buff));
    }

