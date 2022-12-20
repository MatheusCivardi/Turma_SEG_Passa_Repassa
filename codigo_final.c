#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

//exports

#define b1 "10"
#define b2 "10"
#define b3 "10"
#define b4 "10"

//funcao para ler valor do botao
char readb(char b[]) {
    int fd;
    char value;
    char buffer[100];

    fd = open(strcat(strcat(strcpy(buffer,"/sys/class/gpio/gpio"),b),"/value"), O_RDONLY);
    read(fd, &value, 1);
    close(fd);

    return value;
}

/*
//funcao paraa acender o LED
void lighton(char l[]) {
    char buffer[100];

    fd = open(strcat(strcat(strcpy(buffer,"/sys/class/gpio/gpio"),l),"/value"), O_WRONLY | O_SYNC);
    write(fd, "1", 1);
    close(fd);
}

//funcao para apagar o LED
void lightoff(char l[]) {
    char buffer[100];

    fd = open(strcat(strcat(strcpy(buffer,"/sys/class/gpio/gpio"),l),"/value"), O_WRONLY | O_SYNC);
    write(fd, "0", 1);
    close(fd);
}*/

//printa o score
void printscore(int s1,int s2) {
 printf("Score\n");
 printf("grupo1: ");
 printf("%d\n",s1); 
 printf("grupo2: ");
 printf("%d\n",s2); 
 printf("\n");
}

int main() {
    int fd;
    char buffer[100];
    char botao_inic, botao_rst, botao_1, botao_2, certo, errado;
    int grupo1=0, grupo2=0;
    int flag1=0, flag2=0, flag3=0, flag4=0, score1=0, score2=0;

    // export gpio
    fd = open("/sys/class/gpio/export", O_WRONLY);
    write(fd, strcat(b1,"\n"), 3);
    write(fd, strcat(b2,"\n"), 3);
    write(fd, strcat(b3,"\n"), 3);
    write(fd, strcat(b4,"\n"), 3);
    close(fd);

    // configure as input
    fd = open(strcat(strcat(strcpy(buffer,"/sys/class/gpio/gpio"),b1),"/direction"), O_WRONLY);
    write(fd, "in", 2);
    fd = open(strcat(strcat(strcpy(buffer,"/sys/class/gpio/gpio"),b2),"/direction"), O_WRONLY);
    write(fd, "in", 2);
    fd = open(strcat(strcat(strcpy(buffer,"/sys/class/gpio/gpio"),b3),"/direction"), O_WRONLY);
    write(fd, "in", 2);
    fd = open(strcat(strcat(strcpy(buffer,"/sys/class/gpio/gpio"),b4),"/direction"), O_WRONLY);
    write(fd, "in", 2);
    close(fd);

    // configure as output
    /* fd = open(strcat(strcat(strcpy(buffer,"/sys/class/gpio/gpio"),led),"/direction"), O_WRONLY);
    write(fd, "out", 3);
    close(fd); */

    //inicio do jogo
    printf("inicio do jogo\n\n");
    printscore(score1,score2);
    while(1) {
        //permite iniciar pergunta ou resetar score
            botao_inic = readb(b1);
  	    botao_rst = readb(b4);
        if(botao_inic=='1' && flag1==0)
            flag1++;
        if(botao_rst=='1' && flag1==0) {
          	printf("resetando score\n\n");
		score1=0;
          	score2=0;
          	printscore(score1,score2); 
          	while(botao_rst=='1')
             		botao_rst = readb(b4);
        }

        //apos iniciar
        if(flag1>0) {
            //mostra que a pergunta esta sendo feita
            if(flag2==0) {
            printf("pergunta...\n\n");
            flag2++;
            }      

            //le os botoes
            botao_1 = readb(b2);
            botao_2 = readb(b3);
            certo = readb(b1);
    	    errado = readb(b4);      	
	
            //resposta do grupo 1
            if(botao_1=='1' && flag3==0) {
                printf("resposta do grupo 1\n\n");
                flag3++;
              	grupo1++;
            }

            //resposta do grupo 2
            if(botao_2=='1' && flag3==0) {
                printf("resposta do grupo 2\n\n");
                flag3++;
              	grupo2++;
            }
          
            if(flag3) {
              //resposta do grupo 1 correta
              if(certo=='1'&&grupo1&&flag4==0) {
                printf("resposta correta\n\n");
                score1++;
                printscore(score1,score2);
                flag1--;
                flag2--;
                flag3--;
                grupo1--;
                while(certo=='1')
                  certo = readb(b1);
              }
              //resposta do grupo 2 correta
              if(certo=='1'&&grupo2&&flag4==0) {
                printf("resposta correta\n\n");
                score2++;
                printscore(score1,score2);
                flag1--;
                flag2--;
                flag3--;
                grupo2--;
                while(certo=='1')
                  certo = readb(b1);
              }
              //resposta do grupo 1 incorreta
              if(errado=='1'&&grupo1&&flag4==0) {
                printf("resposta incorreta\n grupo 2 tenta\n");
                flag4++;
                while(errado=='1')
                  errado = readb(b4);
              }
              //resposta do grupo 2 incorreta
              if(errado=='1'&&grupo2&&flag4==0) {
                printf("resposta incorreta\n grupo 1 tenta\n");
                flag4++;
                while(errado=='1')
                  errado = readb(b4);
              }
              //resposta do grupo 1 incorreta e grupo 2 correta
              if(flag4&&grupo1&&certo=='1') {
                printf("resposta correta\n\n");
                score2++;
                printscore(score1,score2);
                flag1--;
                flag2--;
                flag3--;
                flag4--;
                grupo1--;
                while(certo=='1')
                  certo = readb(b1);;
              }
              //resposta do grupo 2 incorreta e grupo 1 correta
              if(flag4&&grupo2&&certo=='1') {
                printf("resposta correta\n\n");
                score1++;
                printscore(score1,score2);
                flag1--;
                flag2--;
                flag3--;
                flag4--;
                grupo2--;
                while(certo=='1')
                  certo = readb(b1);;
              }
              //ambas respostas incorretas
              if(flag4&&errado=='1') {
                printf("resposta incorreta\n\n");
                printscore(score1,score2);
                flag1--;
                flag2--;
                flag3--;
                flag4--;
                grupo1=0;
                grupo2=0;
                while(errado=='1')
                  errado = readb(b4);
              }
            }
        }
        usleep(100000); //100ms de delay no loop
    }

    return 0;
}

