# Passa ou Repassa

## Equipe

Turma_SEG

Tema: Passa ou Repassa

Entrega final da disciplina de Sistemas Embarcados (SAA0356)

- Matheus Willian Dias Civardi - 10746918

- Jaime Fernández Antón - 14029936

- João Pedro Gerin Santana - 11372646

- Damiana Irrera - 13470819

- Eduardo Leandro Moura Santos Junior - 10746665

## Introdução

O projeto consiste no desenvolvimento de um sistema comum em jogos de palco no estilo pergunta e resposta. Resumidamente, o apresentador faz a pergunta e o participante/equipe que apertar o botão mais rapidamente tem o direito à responder. No nosso projeto, foram idealizados 4 botões:

- 2 dedicados aos participantes, para verificar quem deles terá o direito à resposta.

- 2 ao apresentador, que indicaram se a resposta está correta ou errada. 

Com o encerramento do jogo, ganha a equipe que estiver com o maior score de respostas corretas.

## Arquitetura e funcionamento

O sistema funciona exibindo os resultados diretamente no prompt de comando, o qual o apresentador teria acesso. São 4 botões:

1 - Apresenta a pergunta / Confirma que a resposta está correta

2 - Informa que o participante 1 apertou o botão

3 - Informa que o participante 2 apertou o botão

4 - Reseta o jogo / Confirma que a resposta está errada

A funcionalidade dos botões depende do estado em que se encontra o jogo. Por exemplo, os botões 1 e 2 não retornam nada enquando pergunta não for realizada.

A equipe que pressionar o botão primeiro tem o direito da resposta, errando, a outra equipe pode responder.

O score das 2 equipes é atualizado a cada pergunta, acertando, soma-se 1, errando, nenhum ponto é acrescido.


## Simulação para arduíno

![arduino](https://user-images.githubusercontent.com/55711155/208699131-eb9ca0cc-3d72-4f79-b624-c72c1397c393.jpg)

https://www.tinkercad.com/things/8iJnDNLYs39-tremendous-kasi-fyyran/editel?sharecode=HrzCFBhRZdAZV3fku4KeVITCv4ZBR2jl43VvOi-vuQI

Antes da placa da toradex ser utilizada, foram realizados alguns testes utilizando o tinkercad para simular tanto o hardware quanto o software. 
Assim, quando foi possível acessar a salinha foram necessários apenas algumas poucas mudanças relativas às portas GPIO, a compilação e a tradução do código .ino para a linguagem C.

## Exemplo de rotina

![Rotina_1](https://user-images.githubusercontent.com/55711155/208699374-acec70f8-2f22-4988-a640-5d9b4c5c91ad.jpg)

- Nesse exemplo, ao rodar o código o jogo se inicia com ambas as equipes com suas pontuações zeradas;

- O apresentador com o Botão_1 apresenta a pergunta aos grupos;

- O grupo 1 (Botão_2) aperta o botão antes do grupo 2, conquistando o direito à resposta;

- O apresentador confirma que a resposta está correta com o Botão_1, o grupo 1 ganha 1 ponto;

- Na nova pergunta o grupo 2 (Botão_3) aperta primeiro, conseguindo o direito à resposta;

- Dessa vez o apresentador pressiona o Botão_4 indicando que a resposta está errada, passando a chance de resposta para o grupo 1;

- O grupo 1 também erra, então o score é atualizado novamente, com nenhuma das equipes conseguindo ponto;

- Agora, ao invés do apresentador iniciar outra pergunta com o Botão_1, ele pressiona o Botão_4 zerando as pontuações e resetando o jogo.

## Rodando na placa da Toradex

![Toradex](https://user-images.githubusercontent.com/55711155/208714192-f3573bb0-6233-452d-993e-5e676c92870e.jpg)

Não havia botões disponíveis na salinha para realizarmos o teste completo do jogo, então, foi utilizado apenas um botão para testar no hardware da Toradex se todo o processo de compilação do código e utilização dos pinos GPIO estavam funcionando corretamente. No vídeo anexado, se mostra um teste de funcionamento.

https://user-images.githubusercontent.com/55711155/208715237-023c0279-4d66-446a-a774-dc47a585e4c1.mp4

Para passar o código de teste do botão para a placa, inicialmente abriu-se um terminal para a conexão via rede com a placa, através do comando no terminal:

<blockquote>
        <p>ssh root@ip</p>
    </blockquote>
    
Em outro terminal, responsável por ser o host, com a toolchain própria já instalada, exportam-se as variáveis para compilação cruzada pelo comando:

<blockquote>
        <p>. environmnt-setup-armv7at2hf-non-angstrom-linux-gnueabi</p>
    </blockquote>
    
Após isso, podemos compilar o código em C para a placa pelo comando:

<blockquote>
        <p> ${CC} -Wall codigo.c -o codigo</p>
    </blockquote>
    
O envio do código para a placa é feito pela instrução:

<blockquote>
        <p>scp codigo root@ip:/home/root</p>
    </blockquote>
    
Retornando ao terminal em que foi feita a conexão com a placa, basta executar o código:

<blockquote>
        <p>./codigo</p>
    </blockquote>
    
## Relação (Viola pins – Linux GPIO number)

Para manipular, por código, as ações e funções determinadas no hardware pelos pinos da Viola (conexões e seus elementos correspondentes), há a necessidade de conhecer suas respectivas identificações no Linux, o que é representado a seguir com alguns dos pinos:

<div align="center">
<img src="https://user-images.githubusercontent.com/52204674/208995104-8e02effc-52d1-49f5-9a51-fd6fc90efaf1.PNG" />
</div>

Adaptando ao projeto, com a utilização dos pinos demarcados em azul na tabela acima:

<div align="center">
<img src="https://user-images.githubusercontent.com/52204674/208992081-014584a0-94ab-4238-8a9d-31e741a74668.PNG" />
</div>

    
## Tratamento de colisão

Antes de tudo, deve ficar claro que a taxa de atualização da placa é maior que a velocidade com que a pessoa pressiona o botão. Se houver uma diferença no momento de pressionar o botão, essa diferença será detectada com certeza. Supondo que os botões foram pressionados ao mesmo tempo, pela forma como o código está estruturado, o grupo 1 tem preferência, mas isso é praticamente impossível.


## Possíveis implementações futuras

A continuação, se mostram algumas possíveis implementações futuras que poderiam ser feitas usando este projeto como um ponto de partida:

- Implementação de mais botões, para que mais equipes pudessem participar.

- Habilitar uma tela digital para mostrar os pontos obtidos por cada equipe.

- Foco no tipo de respostas que o sistema pode aceitar: abertas, de múltipla escolha, verdadeiras ou falsas. 
