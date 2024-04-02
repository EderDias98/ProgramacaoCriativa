#include "engine.h"
#define LARGURA_TELA 60
#define ALTURA_TELA 20
#define SlEEP 10000000
#include <termios.h>




struct engine{
    /* data */
    char cacterePressionado;
    int pulando;
    int altura;
    int distancia;
    int sleep;
    char **mapa;
};

tEngine* criaEngine(){
    tEngine* engine = (tEngine*) calloc(1,sizeof(tEngine));
    engine->sleep = SlEEP;
    engine->mapa = iniciaMapa();
    return engine;
}

void imprimiFrame(char **mapa){
    for( int i=0; i<ALTURA_TELA;i++){
        for(int j=0; j<LARGURA_TELA;j++){
            printf("%c", mapa[i][j]);
        }
        printf("\n");
    }
}

char** iniciaMapa(){

    char** mapa = (char**) calloc(ALTURA_TELA, sizeof(char*));

    for(int i=0; i<ALTURA_TELA;i++){
        mapa[i] = (char*) calloc(LARGURA_TELA,sizeof(char));
    }

    for( int i=0; i<ALTURA_TELA;i++){
        for(int j=0; j<LARGURA_TELA;j++){
            mapa[i][j] = ' ';
        }
    }

    return mapa;
} 

void processaDados(tEngine* engine){
    imprimiFrame(engine->mapa);
}


void loopGame(tEngine* engine ,fptrProcessaDados fptrProcessaDados){
    
    
//configuração do terminal

struct termios old_attr ;
struct termios new_attr ;
int entradaPadrao = 0;
tcgetattr(entradaPadrao, &old_attr) ;

new_attr = old_attr ;
new_attr.c_lflag &= ~ECHO ;
new_attr.c_lflag &= ~ICANON ;

tcsetattr(entradaPadrao,TCSANOW ,&new_attr) ;



    while(1){

        if(engine->sleep-- != 0){
            printf("\e[H\e[2J");
            engine->sleep = SlEEP;


            fptrProcessaDados(engine);

            printf("# %c #",engine->cacterePressionado);

            if(engine->cacterePressionado == 'q')
                break;
            
        }

        engine->cacterePressionado =  getchar();
        

    }
    tcsetattr(entradaPadrao,TCSANOW ,&old_attr) ;
    

}

