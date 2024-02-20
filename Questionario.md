# Questionário Sistemas Embarcados I

## 1. Explique brevemente o que é compilação cruzada (***cross-compiling***) e para que ela serve.

Resposta: a primeiro momento, pode-se aformar que o "cross-compiling" é um compilador que tem a capacidade de gerar um código executável para uma plataforma diferente daquela usada para desenvolver no ambiente em questão. Ou seja, um computador ou notebook, por exemplo, através da compilação cruzada detém um ambiente de desenvolvimento em uma aquitetura totalmente diferente daquela em que o programa será rodado, como por exemplo, em um sistema embarcado, como usado em aula STM32F411CEU6 (ARM, CortexM4), assim usando GNU Arm Embedded Toolchain, por exemplo, o qual possibilita que "start files"(arquivos de inicialização) e macros que possam obter a implementação de uma inicialização ou reiniciliazação para dispostivos que possuem o processador Cortex-MX .

## 2. O que é um código de inicialização ou ***startup*** e qual sua finalidade?
Resposta: o código de inicialização (Startup Code) pode ser definido como um conjunto de instruções diversas para inicializar de forma correta um dispositivo, o que implica em garantir que algumas funções sejam executadas antes mesmo da função principal. Nesse contexto, pode-se dizer que para a família do STM32, quando algo está sendo projetado, um arquivo é gerado, contendo, por exemplo: reset handler e outras funções que obrigatoriamente acontecem antes da função "main()" ser rodada. Assim, dessa forma, inicializando registradores fundamentais, configurando a memória RAM, inicializando periféricos, copiando informações inicializadas e etc.

## 3. Sobre o utilitário **make** e o arquivo **Makefile responda**:

#### (a) Explique com suas palavras o que é e para que serve o **Makefile**.
Resposta: o Make é uma ferramenta que automatiza o processo de "program building" e o Makefile descreve as opções de comando que podem ou não serem usadas no processo de "building" (o Makefile pode ser editado da menira com que o programador em questão precisa para seu projeto). De forma geral, o Makefile é uma ferramenta que facilita a vida de muitos desenvolvedores, assim como visto em aula, já que esse evita que muitas linhas de código precisem ser reescritas várias vezes, o o que facilita o processo de compilação e evita também erros. Nesse contexto, tem-se como exemplo em sala de aula no segundo laboratório em que o código da toolchain (arm-none-eabi...) precisava ser reescrito todas as vezes para criar o arquivo main.o (objeto) a aprtir do main.c, ou seja, para fazer a "build" do programa em questão e, ao criar o Makefile, todo esse processo se tornou automático e menos cansativo. 


#### (b) Descreva brevemente o processo realizado pelo utilitário **make** para compilar um programa.
Resposta: Ainda sobre o contexto do Make, podemos esmiuçar um pouco mais do processo realizado por esse utilitário. Nesse âmbito, o Make possui 5 elementos instrutivos: regras explícitas(explicit rules), regras implícitas(implicit rules), definições de variáveis (variable definitions), diretivas (directives) e comentários (comments), sendo a regra para informar ao Make quando um target está desatualizado (se esse não existe ou se ainda é mais antigo que os prerequisites)ou se precisa ser atualizado. Agora, o processo estabelecido é: o Make fará a leitura do Makefile para compreender as regras de compilção descritas e verificar as dependências entre todos os arquivos do projeto, na sequência o Make fará uma verificação entre os arquivos do código fonte e aqueles compilados; Então é verificado se houve qualquer tipo de alteração desde a última compilação e se necessário executa o Makefile para executar as regras de compilação para compilar os arquivos fonte em arquivos objeto; E, por fim, o Make faz uma "linkagem" entre os arquivos objeto (.o) para obter um arquivo executável. Ou seja,a complição dos arquivos ".c" que então obterá a geração de arquivos objeto ".o" para criar um executável.

#### (c) Qual é a sintaxe utilizada para criar um novo **target**?
Resposta: Para que o Make não obtenha nenhum tipo de falha ao tentar criar um target que ainda não existe, para todo tipo de arquivo que tenha alguma dependência deve-se criar um novo target. Nesse sentido, para criar isso, pode-se usar a seguinte sintaxe: $(DEPS): (forma genérica para criar um target para toa a lista de arquivos objeto salvos em um diretório: DEPS = $(patsubst %, $(DEPDIR)/%.d, $(basename $(SRCS))) ).

#### (d) Como são definidas as dependências de um **target**, para que elas são utilizadas?
Resposta: As dependências de um target são definidas a partir da necessidade desses serem reconstruídos ou não, visto que quando o Make é executado é verificado se alguma das ependências de um target foram alteradas desde a última compilação, para que haja a devida atualização dessa e não ontenha erros futuros quando algo é alterado em um dos arquivos dependentes, ou seja, as regras estabelecidas no Makefile são executadas novamente para a atualização dos arquivos que sofreram algum tipo de alteração. Isso pode também ser visto em uma aplicação em laboratório, uma vez que ao criarmos um arquivo ".h" em uma dependência de ".c" e esse ter seu valor de pi alterado, nessa questão, não obtinha-se a atualização desse, pois a relação de dependência do target não havia sido ainda implementada ao Makefile e,portnato, o ".c" não tinha sido reconstruído.

#### (e) O que são as regras do **Makefile**, qual a diferença entre regras implícitas e explícitas?
Resposta: Ainda sobre o Makefile, as regras podem ser dividas em: regras explícitas (explicit rules), ou ainda em regras implícitas (implicit rules). Nesse contexto, as regras explícitas informam sempre quando e como refazer um ou mais arquivos, sendo esses chamados de alvos da regra (rules' targets), pois lista-se os arquivos que os alvos (targets) possuem dependência, o que é chamado de pré-requisites do alvo, assim fornecendo instruções ou uma fórmula para a atualização dos "targets". Agora, as regras implícitas são sobre como refazer uma classe de arquivos com base em seus nomes, já que essa regra descreve como que um alvo (target) pode depender de um arquivo com um nome semelhante ao do alvo, assim criando uma fórmula para cruar ou atualizar este alvo.

## 4. Sobre a arquitetura **ARM Cortex-M** responda:

### (a) Explique o conjunto de instruções ***Thumb*** e suas principais vantagens na arquitetura ARM. Como o conjunto de instruções ***Thumb*** opera em conjunto com o conjunto de instruções ARM?
Resposta: O conjunto de instrções Thumb é um subconunto das instruções ARM, no entanto, agora comprimidas de 32 bits para 16 bits, potanto isso reduz a quantidade de memória usada pelo código , assim também diminuindo o tamanho do Hardware e o seu custo, consequentemente. Nesse sentido, toda a instrução Thumb detém uma instrução ARM equivalente, porém o oposto não é possível, e pode-se alternar também entre os dois tipois de instrução Thumb e ARM do processador. Além disso, esse conjunto também sempre atualiza flags de condição.

### (b) Explique as diferenças entre as arquiteturas ***ARM Load/Store*** e ***Register/Register***.
Resposta: Ambas das abrodagens se referem a transferência de dados entre registradores e memória para o tipo de arquitetura ARM Cortex-M. Nesse sentido,  ARM Load/Store detém operações de carga e de armazenamento exclusivamente realizadas por meio de instruções LDR(Load Register) e STR(Store Register), portanto todos os dados precisam ser primeiramente carregados em um registrador da CPU usando uma das duas instruções e então as operações são realizadas nesse registrador e somente posteriormente que os dados são armazenados na memória (instruções aritméticas são exclusivamente realizadas em registradores). Agora Register/Register os dados são exclusivamente transferidos entre os prórpios registradores escolhidos do processador sem acessar a memória de fato, assim as instruções de movimento são o que movimenta os dados entre os registradores e portanto todas as operações artiméticas são realizadas entre registradores.


### (c) Os processadores **ARM Cortex-M** oferecem diversos recursos que podem ser explorados por sistemas baseados em **RTOS** (***Real Time Operating Systems***). Por exemplo, a separação da execução do código em níveis de acesso e diferentes modos de operação. Explique detalhadamente como funciona os níveis de acesso de execução de código e os modos de operação nos processadores **ARM Cortex-M**.

### (d) Explique como os processadores ARM tratam as exceções e as interrupções. Quais são os diferentes tipos de exceção e como elas são priorizadas? Descreva a estratégia de **group priority** e **sub-priority** presente nesse processo.

### (e) Qual a diferença entre os registradores **CPSR** (***Current Program Status Register***) e **SPSR** (***Saved Program Status Register***)?

### (f) Qual a finalidade do **LR** (***Link Register***)?

### (g) Qual o propósito do Program Status Register (PSR) nos processadores ARM?

### (h) O que é a tabela de vetores de interrupção?

### (i) Qual a finalidade do NVIC (**Nested Vectored Interrupt Controller**) nos microcontroladores ARM e como ele pode ser utilizado em aplicações de tempo real?

### (j) Em modo de execução normal, o Cortex-M pode fazer uma chamada de função usando a instrução **BL**, que muda o **PC** para o endereço de destino e salva o ponto de execução atual no registador **LR**. Ao final da função, é possível recuperar esse contexto usando uma instrução **BX LR**, por exemplo, que atualiza o **PC** para o ponto anterior. No entanto, quando acontece uma interrupção, o **LR** é preenchido com um valor completamente  diferente,  chamado  de  **EXC_RETURN**.  Explique  o  funcionamento  desse  mecanismo  e especifique como o **Cortex-M** consegue fazer o retorno da interrupção. 

### (k) Qual  a  diferença  no  salvamento  de  contexto,  durante  a  chegada  de  uma  interrupção,  entre  os processadores Cortex-M3 e Cortex M4F (com ponto flutuante)? Descreva em termos de tempo e também de uso da pilha. Explique também o que é ***lazy stack*** e como ele é configurado. 


## Referências

### Básicas

[1] [STM32F411xC Datasheet](https://www.st.com/resource/en/datasheet/stm32f411ce.pdf)

[2] [RM0383 Reference Manual](https://www.st.com/resource/en/reference_manual/rm0383-stm32f411xce-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)

[3] [Using the GNU Compiler Collection (GCC)](https://gcc.gnu.org/onlinedocs/gcc/index.html)

[4] [GNU Make](https://www.gnu.org/software/make/manual/html_node/index.html)

### Vídeos Microsoft Teams

[5] [05 - Introdução à arquitetura de computadores](https://web.microsoftstream.com/embed/channel/f6b3a0de-e6f3-4652-b2d5-f1164032498a?app=microsoftteams&sort=undefined&l=pt-br#)

[6] [06 - Arquitetura Cortex-M Parte 1/2](https://web.microsoftstream.com/embed/channel/f6b3a0de-e6f3-4652-b2d5-f1164032498a?app=microsoftteams&sort=undefined&l=pt-br#)

[7] [07 - Arquitetura Cortex-M Parte 2/2](https://web.microsoftstream.com/embed/channel/f6b3a0de-e6f3-4652-b2d5-f1164032498a?app=microsoftteams&sort=undefined&l=pt-br#)

[8] [08 - Microcontroladores STM32](https://web.microsoftstream.com/embed/channel/f6b3a0de-e6f3-4652-b2d5-f1164032498a?app=microsoftteams&sort=undefined&l=pt-br#)

[9] [10 - Introdução à arquitetura de computadores](https://web.microsoftstream.com/embed/channel/f6b3a0de-e6f3-4652-b2d5-f1164032498a?app=microsoftteams&sort=undefined&l=pt-br#)

### Material Suplementar

[5] [A General Overview of What Happens Before main()](https://embeddedartistry.com/blog/2019/04/08/a-general-overview-of-what-happens-before-main/)
 
[6] [Bare metal embedded lecture-1: Build process](https://youtu.be/qWqlkCLmZoE?si=mn5yDnJYudQ1PpZH)
 
[7] [Bare metal embedded lecture-2: Makefile and analyzing relocatable obj file](https://youtu.be/Bsq6P1B8JqI?si=yuNLPj3JQ-2IT1yo)
 
[8] [Bare metal embedded lecture-3: Writing MCU startup file from scratch](https://youtu.be/2Hm8eEHsgls?si=c27MpZ47ApiMSwHR)
 
[9] [Lecture 15: Booting Process](https://youtu.be/3brOzLJmeek?si=MsHRUEJP8zofjwJQ)
