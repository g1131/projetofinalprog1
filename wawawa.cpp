#include <iostream>
#include <iomanip>
#include <locale.h>
#include <cmath>
using namespace std;

int quilates[4]={0}, qntplayers=0;
char nome[4];
char mina[6][6], interface[6][6];

void intro(){ //Texto de start do jogo
    cout << "Bem vindo à caça ao tesouro!" << endl;
    cout << "Aqui, os jogadores devem encontrar diamantes em uma mina!" << endl;
}

void preenchermatrizes(){ //inicializa as matrizes da interface e do "back end" do jogo
    srand((unsigned)time(NULL));
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            if(rand() % 100 < 5){
                mina[i][j] = '+'; // 5% de pistas
            }else if(rand() % 100 < 10){
                mina[i][j] = (rand() % 2 == 0) ? 'O' : '-'; // 10% de armadilhas
            }else{
                mina[i][j] = 'D'; // Diamante
            }
        }
    }

    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            interface[i][j]='X';
        }
    }
}

void nomejogadores(){ //Guarda as inicias dos jogadores invez dos nomes, para conveniencia
    for(int i=0; i<qntplayers; i++){
        cout << "Inserir inicial do jogador " << i+1 << " : " << endl;
        cin >> nome[i];
        for(int j=0; i<qntplayers; j++){
            if(nome[i+1]==nome[i]){
                cout << "Inicias iguais, por favor inserir uma inical diferente." << endl;
                cout << "Inserir inicial do jogador " << i+1 << " : " << endl;
                cin >> nome[i];
            }
        }
    }
}

void qntjogadores(){ //Determina a quantidade de jogadores que participarao do jogo
    cout << "Quantas pessoas vao jogar?" << endl;
    cin >> qntplayers;
    while(qntplayers<2 || qntplayers>4){
        cout << "Valor invalido, o jogo deve ser jogado com 2 a 4 jogadores." << endl;
        cout << "Quantas pessoas vao jogar?" << endl;
        cin >> qntplayers;
    }
}

void promptjogue(int x, int dec, int uni){ //Entrada de qual indice da matriz o jogador quer checar para diamantes
    cout << "Qual casa vc deseja explorar?" << endl;
    cin >> x;
    dec=x/10;
    uni=x%10;
}

void jogadas(int x, int dec, int uni){ //alterna os turnos entre os jogadores, checa a matriz do jogo e atualiza a matriz da interface
    for(int i=0; i<qntplayers; i++){
        cout << "Vez do jogador " << i+1 << endl;
        promptjogue(x, dec, uni);
        if(mina[dec][uni]='D'){
            quilates[i]=rand()%10+1;
        }else if(mina[dec][uni]='+'){
            quilates[i]+=3;
        }else if(mina[dec][uni]='-'){
            quilates[i+1]-=5;
        }else if(mina[dec][uni]='O'){
            quilates[i]-=10;
        }
        interface[dec][uni]=nome[i];
    }
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    srand((unsigned)time(NULL));
    int dec=0, x=0, uni=0;

    intro();
    preenchermatrizes();

    /*for(int i=0; i<6; i++){ // imprime a matriz do jogo para teste
        for(int j=0; j<6; j++){ 
            printf("%c ", mina[i][j]);
        }
        putchar('\n');
    }*/

    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            printf("%c ", interface[i][j]);
        }
        putchar('\n');
    }

    jogadas(x, dec, uni);
    
    return 0;
}
