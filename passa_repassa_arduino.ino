// C++ code
//

#define b1 4
#define b4 5
#define b2 6
#define b3 7

int flag1=0, flag2=0, flag3=0, flag4=0, score1=0, score2=0;
int botao_inic=0,botao_rst=0, botao_1, botao_2, certo, errado, grupo1=0, grupo2=0;

void printscore(int s1,int s2) {
 Serial.println("Score");
 Serial.print("grupo1: ");
 Serial.println(s1); 
 Serial.print("grupo2: ");
 Serial.println(s2); 
 Serial.println("");
}

void setup()
{
  Serial.begin(9600);
  pinMode(7, INPUT);
  pinMode(6, INPUT);
  pinMode(5, INPUT);
  pinMode(4, INPUT);
  Serial.println("Inicio do jogo...\n");
  printscore(score1,score2);           
}

void loop()
{
  //permite iniciar pergunta ou resetar score
            botao_inic = digitalRead(b1);
  			botao_rst = digitalRead(b4);
        if(botao_inic==1 && flag1==0)
            flag1++;
        if(botao_rst && flag1==0) {
          	Serial.println("resetando score\n");
			score1=0;
          	score2=0;
          	printscore(score1,score2); 
          	while(botao_rst)
              botao_rst = digitalRead(b4);
        }

        //apos iniciar
        if(flag1>0) {
            //mostra que a pergunta esta sendo feita
            if(flag2==0) {
            Serial.println("pergunta...\n");
            flag2++;
            }      

            //le os botoes
            botao_1 = digitalRead(b2);
            botao_2 = digitalRead(b3);
          	certo = digitalRead(b1);
    		errado = digitalRead(b4);      	
	
            //resposta do grupo 1
            if(botao_1==1 && flag3==0) {
                Serial.println("resposta do grupo 1\n");
                flag3++;
              	grupo1++;
            }

            //resposta do grupo 2
            if(botao_2==1 && flag3==0) {
                Serial.println("resposta do grupo 2\n");
                flag3++;
              	grupo2++;
            }
          
            if(flag3) {
              //resposta do grupo 1 correta
              if(certo&&grupo1&&flag4==0) {
                Serial.println("resposta correta\n");
                score1++;
                printscore(score1,score2);
                flag1--;
                flag2--;
                flag3--;
                grupo1--;
                while(certo)
                  certo = digitalRead(b1);
              }
              //resposta do grupo 2 correta
              if(certo&&grupo2&&flag4==0) {
                Serial.println("resposta correta\n");
                score2++;
                printscore(score1,score2);
                flag1--;
                flag2--;
                flag3--;
                grupo2--;
                while(certo)
                  certo = digitalRead(b1);
              }
              //resposta do grupo 1 incorreta
              if(errado&&grupo1&&flag4==0) {
                Serial.println("resposta incorreta\n grupo 2 tenta");
                flag4++;
                while(errado)
                  errado = digitalRead(b4);
              }
              //resposta do grupo 2 incorreta
              if(errado&&grupo2&&flag4==0) {
                Serial.println("resposta incorreta\n grupo 1 tenta");
                flag4++;
                while(errado)
                  errado = digitalRead(b4);
              }
              //resposta do grupo 1 incorreta e grupo 2 correta
              if(flag4&&grupo1&&certo) {
                Serial.println("resposta correta\n");
                score2++;
                printscore(score1,score2);
                flag1--;
                flag2--;
                flag3--;
                flag4--;
                grupo1--;
                while(certo)
                  certo = digitalRead(b1);;
              }
              //resposta do grupo 2 incorreta e grupo 1 correta
              if(flag4&&grupo2&&certo) {
                Serial.println("resposta correta\n");
                score1++;
                printscore(score1,score2);
                flag1--;
                flag2--;
                flag3--;
                flag4--;
                grupo2--;
                while(certo)
                  certo = digitalRead(b1);;
              }
              //ambas respostas incorretas
              if(flag4&&errado) {
                Serial.println("resposta incorreta\n");
                printscore(score1,score2);
                flag1--;
                flag2--;
                flag3--;
                flag4--;
                grupo1=0;
                grupo2=0;
                while(errado)
                  errado = digitalRead(b4);
              }
            }
        }
  delay(100);
}