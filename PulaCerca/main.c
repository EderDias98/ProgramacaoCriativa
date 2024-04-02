#include "engine.h"




int main(){

    tEngine* engine = criaEngine();

    loopGame(engine, processaDados);
    exit(1);
    return 0;
}