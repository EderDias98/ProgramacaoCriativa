#include "engine.h"
#define LARGURA_TELA 60
#define ALTURA_TELA 10
#define SlEEP 100000
#define LIMITE_PULO 5
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
    int caindo;
    char **mapa;
};

tEngine* criaEngine(){
    tEngine* engine = (tEngine*) calloc(1,sizeof(tEngine));
    engine->sleep = SlEEP;
    engine->mapa = iniciaMapa();
    engine->altura= 0;
    engine->distancia = LARGURA_TELA -1;

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



    printf("Precione q pra sair\n");
    printf("Altura: %d, Distancia: %d\n", engine->altura, engine->distancia);

    if(engine->gameOver){
        printf("GAME OVER!\n");
        return;
    }
    

    if(engine->altura == 0 && engine->caracterePressionado == ' ' ){
        engine->caracterePressionado = '\0';
        engine->pulando = 1;
    }


    if(engine->pulando ){

        engine->mapa[ALTURA_TELA-1 - engine->altura ][(LARGURA_TELA -1 )/2] = ' ';



        if(engine->altura == LIMITE_PULO ){
            engine->caindo =1;
        }
        
        if(!engine->caindo){
            engine->altura++;
            
        }

        if(engine->caindo){
            engine->altura--;
            
        }

    }







 
    


    engine->mapa[ALTURA_TELA-1 - engine->altura ][(LARGURA_TELA -1 )/2] = 'X';

    engine->mapa[ALTURA_TELA-1 ][ engine->distancia] = ' ';
  
    engine->distancia--;
    engine->mapa[ALTURA_TELA-1 ][ engine->distancia] = '|';

    if(engine->distancia < 0){
        engine->distancia = LARGURA_TELA-1;
    }

    if( engine->altura ==0 && engine->distancia == (LARGURA_TELA/2) ){
        engine->gameOver =1;
        printf("\nGAME OVER\n");
        return;
    }

    imprimiFrame(engine);

    if(engine->altura == 0){
        engine->pulando=0;
        engine->caindo =0;
    }
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

            system("clear"); // Limpa a tela (no Unix/Linux/Mac)
            printf("\033[H");
            
            
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

