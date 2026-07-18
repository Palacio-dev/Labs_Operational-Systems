# Laboratório 3 - Problema dos Fumantes

## Contexto

O problema dos fumantes é um clássico exemplo de sincronização concorrente em sistemas operacionais. Ele descreve uma situação em que três fumantes precisam de três ingredientes diferentes para montar um cigarro: tabaco, papel e fósforo. Um agente externo coloca dois ingredientes em uma mesa a cada vez, e o fumante que possui o terceiro ingrediente necessário é o único capaz de concluir a ação.

Esse problema é interessante porque expõe a necessidade de coordenar múltiplas threads de forma segura, evitando condições de corrida, deadlocks e execuções inconsistentes.

## Objetivo

Implementar uma solução concorrente para o problema dos fumantes utilizando threads, semáforos e mutex, de modo que:

- o agente distribua corretamente os ingredientes;
- cada fumante espere até ter os itens necessários;
- apenas o fumante apropriado seja notificado;
- o sistema continue executando de forma coordenada e visualmente representada em uma animação no terminal.

## Solução implementada

A implementação foi estruturada em quatro partes principais:

1. Agente
   - Cria combinações de dois ingredientes diferentes.
   - Publica os ingredientes disponíveis para que os demais componentes possam reagir.

2. Helpers
   - Observam os ingredientes que chegam.
   - Identificam quando uma combinação completa é formada.
   - Liberam o semáforo correspondente ao fumante que pode finalizar a ação.

3. Fumantes
   - Cada fumante representa um tipo específico de material: tabaco, papel ou fósforo.
   - Fica bloqueado até receber a sinalização correta.
   - Quando acorda, realiza a ação de fumar por um intervalo de tempo.

4. Sincronização
   - Os semáforos controlam a ordem e a disponibilidade dos recursos.
   - O mutex é usado para proteger o estado compartilhado entre os helpers e garantir consistência nas decisões.

## Como o programa funciona

O fluxo do sistema é o seguinte:

- O agente escolhe uma combinação de dois ingredientes e os disponibiliza.
- Os helpers verificam quais materiais estão presentes.
- Quando uma combinação válida é formada, um fumante específico é despertado.
- O fumante consome a combinação e entra em um ciclo de fumaça.
- Em seguida, o agente pode produzir uma nova combinação.

Essa lógica permite simular de forma realista o problema clássico de sincronização, sem que diferentes threads tentem agir em momentos indevidos.

## Estrutura do projeto

- src/agent.c: implementação da lógica do agente.
- src/helpers.c: implementação dos helpers responsáveis por identificar combinações.
- src/smokers.c: implementação dos fumantes.
- src/main.c: inicialização das estruturas de sincronização e criação das threads.
- src/anim.c: implementação das animações visuais no terminal, utilizando a biblioteca ncurses para representar o agente, os fumantes e os estados do sistema.
- inc/: arquivos de cabeçalhos.
- Makefile: responsável por compilar o projeto.

## Animação com ncurses

A parte visual do projeto é implementada no módulo anim.c com o auxílio da biblioteca ncurses. Ela é responsável por desenhar no terminal os sprites do agente e dos fumantes, além de exibir mensagens de eventos e mudanças de estado durante a execução.

Essa camada visual ajuda a acompanhar, de forma intuitiva, o comportamento das threads e a ordem em que os ingredientes são disponibilizados e consumidos. A utilização do ncurses torna a simulação mais didática e interativa, permitindo uma representação em tempo real do problema.

## Execução

Para compilar e executar o laboratório, rode os comandos abaixo:

```bash
cd lab03
make
./build/cigarrette_smokers
```

Para encerrar a execução, pode-se usar Ctrl+C no terminal.

## Observação

Este laboratório tem um caráter didático e visual: além de resolver o problema de sincronização, ele também apresenta uma animação no terminal para facilitar a compreensão do comportamento das threads e dos semáforos ao longo da execução.
