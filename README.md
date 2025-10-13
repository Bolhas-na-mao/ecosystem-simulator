# Simulador de Ecossistema

Um jogo de simulação onde você gerencia um ecossistema com grama, coelhos e raposas.

## Como Funciona

### Grama

- Cresce naturalmente em células vazias ao longo do tempo
- Serve de alimento para os coelhos

### Coelhos

- Se movem em direção à grama quando detectam dentro do alcance
- Comem grama ao ficarem adjacentes, ganhando energia
- Perdem energia a cada turno
- Morrem quando a energia chega a zero
- Se reproduzem quando atingem energia máxima (no lugar de se mover)

### Raposas

- Se movem em direção aos coelhos quando detectam dentro do alcance
- Comem coelhos ao ficarem adjacentes, ganhando energia
- Perdem energia a cada turno
- Morrem quando a energia chega a zero
- Se reproduzem quando atingem energia máxima (no lugar de se mover)

## Objetivo

Equilibrar o ecossistema posicionando e gerenciando as entidades estrategicamente para manter todas as espécies vivas pelo maior tempo possível.
