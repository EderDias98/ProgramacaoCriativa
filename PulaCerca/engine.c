#include "engine.h"
#define LARGURA_TELA 60
#define ALTURA_TELA 20
#define SlEEP 1000000
#define LIMITE_PULO ALTURA_TELA/2
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>




struct engine{ 
    int pulando;
    int altura;
    int distancia;
    int sleep;
    int gameOver;
    char caracterePressionado;
    char **mapa;
};

tEngine* criaEngine(){
    tEngine* engine = (tEngine*) calloc(1,sizeof(tEngine));
    engine->sleep = SlEEP;
    engine->mapa = iniciaMapa();
    engine->altura= 0;
    engine->distancia = LARGURA_TELA/2;

    return engine;
}

void imprimiFrame(tEngine* engine){
    char** mapa = engine->mapa;
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
    // inicicio
    if(engine->gameOver){
        printf("GAME OVER!\n");
        return;
    }


    printf("Precione q pra sair\n");
    printf("Altura: %d, Distancia: %d\n", engine->altura, engine->distancia);

    if(engine->altura == 0 && engine->caracterePressionado == ' ' ){
        printf("dddddddd");
        engine->pulando = 1;
    }

    int caindo =0;

    if(engine->pulando ){
        if(engine->altura < LIMITE_PULO && !caindo){
            engine->altura++;
        }else engine->altura--;
        
    }







 
    


    engine->mapa[ALTURA_TELA-1 - engine->altura ][(LARGURA_TELA -1 )/2] = 'X';
    if((engine->altura -1) >=0){
        engine->mapa[ALTURA_TELA-1 - engine->altura +1 ][(LARGURA_TELA -1 )/2] = ' ';
        printf("2");
    }
    imprimiFrame(engine);

    if(engine->altura == 0)
        engine->pulando=0;
}


void loopGame(tEngine* engine ,fptrProcessaDados fptrProcessaDados){
    
    
//configuração do terminal

struct termios old_attr ;
struct termios new_attr ;
int entradaPadrao = 0;
tcgetattr(entradaPadrao, &old_attr) ;

new_attr = old_attr ;
new_attr.c_lflag &= ~(ICANON | ECHO);

tcsetattr(entradaPadrao,TCSANOW ,&new_attr) ;

fcntl(entradaPadrao, F_SETFL, fcntl(entradaPadrao, F_GETFL) | O_NONBLOCK);

    while(1){

     

        if(engine->sleep-- == 0){

            
            printf("\033[2J\033[H");
            engine->sleep = SlEEP;

           
        
            fptrProcessaDados(engine);

            // printf("# %c #",engine->caracterePressionado);
            

            if(engine->caracterePressionado == 'q')
                break;
            
        }

        read(entradaPadrao, &engine->caracterePressionado, 1);
        

    }
    tcsetattr(entradaPadrao,TCSANOW ,&old_attr) ;
    

}

