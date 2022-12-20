### Turma_SEG_Passa_Repassa
Entrega final da disciplina de Sistemas Embarcados

Damiana

Eduardo Leandro Moura Santos Junior - 10746665

Jaime Fernández Antón - 14029936

João

Matheus Willian Dias Civardi - 10746918

# Passa ou Repassa

## Introdução
O projeto consiste no desenvolvimento de um sistema comum em jogos de palco no estilo pergunta e resposta. Resumidamente, o apresentador faz a pergunta e o participante/equipe que apertar o botão mais rapidamente tem o direito à resposta. No nosso projeto foram idealizados 4 botões, 2 dedicados aos participantes, para verificar quem deles terá o direito à resposta, e outros 2 ao apresentador, que indicaram se a resposta está correta ou errada.

## Arquitetura e funcionamento
O sistema funciona exibindo os resultados diretamente no prompt de comando, o qual o apresentador teria acesso. São 4 botões:
1 - Informa que o participante 1 apertou o botão
2 - Informa que o participante 2 apertou o botão
3 - Comfirma que a resposta está correta
4 - Comfirma que a resposta está errada

Pressionando o Botão_1 o presentador apresenta a pergunta aos participantes, o grupo que apertar o seu botão primeiro tem o direito à resposta (Botão_2 para o grupo 1 e Botão_3 para o grupo 2).

Ao receber a resposta, o apresentador confirma se está correta com o Botão_1 e a equipe que respondeu pontua


### Simulação para arduíno

https://www.tinkercad.com/things/8iJnDNLYs39-tremendous-kasi-fyyran/editel?sharecode=HrzCFBhRZdAZV3fku4KeVITCv4ZBR2jl43VvOi-vuQI

Antes da placa da toradex ser utilizada, foram realizados alguns testes utilizando o tinkercad para simular tanto o hardware quanto o software.
Assim, quando foi possível acessar a salinha foram necessários apenas algumas poucas mudanças relativas às portas GPIO, a compilação e a tradução do código .ino para a linguagem C.

## Exemplos de rotina
### Primeiro exemplo de rotina 
