#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define b1 "88" //pino 10 da viola

char readb(char b[]) {
    int fd;
    char value;
    char buffer[100];

    fd = open(strcat(strcat(strcpy(buffer,"/sys/class/gpio/gpio"),b),"/value"), O_RDONLY);
    read(fd, &value, 1);
    close(fd);

    return value;
}

int main() {
    int fd;
    char botao;
     // export GPIO
    fd = open("/sys/class/gpio/export", O_WRONLY);
    write(fd, b1, 2);
    close(fd);
 
    // configure as input
    fd = open("/sys/class/gpio/gpio46/direction", O_WRONLY);
    write(fd, "in", 2);
    close(fd);

    while(1) {
        botao = readb(b1);
        printf("%c\n",botao);
        usleep(100000);
    }

    return 0;
}
