#include <iostream>
#include <iomanip>
#include <locale.h>
#include <cmath>
using namespace std;

int quilates[4]={0}, qntplayers=0;
int vencedor=0, pmax=-7000, turnos=0;
char nome[4];
char mina[6][6], interface[6][6];
bool fim=false;

void intro(){ //Texto de start do jogo
    cout << "Bem vindo à caça ao tesouro!" << endl;
    cout << "Aqui, os jogadores devem encontrar diamantes em uma mina!" << endl;
    cout << " " << endl;
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

void promptjogue(){ //Entrada de qual indice da matriz o jogador quer checar para diamantes
    cout << "Qual casa vc deseja explorar?" << endl;
}

void jogadas(int x, int dec, int uni){ //alterna os turnos entre os jogadores, checa a matriz do jogo e atualiza a matriz da interface
    int novosquilates=0;
    for(int i=0; i<qntplayers; i++){
        cout << "Vez do jogador " << nome[i] << endl;
        promptjogue();
        cin >> dec >> uni;
        interface[dec][uni]='0';
        if(mina[dec][uni]='D'){
           novosquilates=rand()%10+1;
           quilates[i]=novosquilates;
           cout << "Você achou um diamante de " << novosquilates << " quilates!" << endl;
        }else if(mina[dec][uni]='+'){
            quilates[i]+=3;
            cout << "Você está no caminho certo e achou 3 quilates!" << endl;
        }else if(mina[dec][uni]='-'){
            quilates[i+1]-=5;
            cout << "Você se escondeu e tirou 5 quilates de um oponente!" << endl;
        }else if(mina[dec][uni]='O'){
            quilates[i]-=10;
            cout << "Você caiu num tunel sem saída e perdeu 10 quilates!" << endl;
        }
        for(int i=0; i<6; i++){
            for(int j=0; j<6; j++){
                printf("%c ", interface[i][j]);
            }
        putchar('\n');
        }
        turnos++;
    }
}

void placar(){ //determina e printa o jogador com mais pontos, e escreve a pontuacao dos demais
    for(int i=0; i<qntplayers; i++){
        if(quilates[i]>pmax){
            pmax=quilates[i];
            vencedor=i;
        }
    }
    cout << "O jogador com mais pontos foi: " << nome[vencedor] << " com " << pmax << " pontos!" << endl;
    for(int j=0; j<qntplayers; j++){
        cout << "O Jogador " << j+1 << " com a inicial " << nome[j] << " teve " << quilates[j] << " pontos." << endl;
    }
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    srand((unsigned)time(NULL));
    int dec=0, x=0, uni=0;

    /*for(int i=0; i<6; i++){ // imprime a matriz do jogo para teste
        for(int j=0; j<6; j++){ 
            printf("%c ", mina[i][j]);
        }
        putchar('\n');
    
    }*/

    intro();
    qntjogadores();
    nomejogadores();
    preenchermatrizes();

    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            printf("%c ", interface[i][j]);
        }
        putchar('\n');
    }
    while(turnos<=36/qntplayers){
        jogadas(x, dec, uni);
    }
    fim=true;
    while(fim=true){
        placar();
        break;
    }
    
    
    return 0;
}
