#ifndef ENGINE_H
#define ENGINE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct engine tEngine;


/**
 * Essa função é responsável por mudar o frame de acordo 
 * com o input recebido pelo terminal, ou seja ela é uma 
 * callback
*/
typedef void (*fptrProcessaDados)(tEngine* engine);


tEngine* criaEngine();

void imprimiFrame(tEngine* engine);


char** iniciaMapa();


void loopGame(tEngine* engine ,fptrProcessaDados fptrProcessaDados);


void processaDados(tEngine* engine);

#endif

