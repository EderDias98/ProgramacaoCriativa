#include "engine.h"




int main(){

    tEngine* engine = criaEngine();

    loopGame(engine, processaDados);
    
    return 0;
}