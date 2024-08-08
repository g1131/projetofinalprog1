#include <iostream>
#include <iomanip>
#include <locale.h>
#include <cmath>
using namespace std;

int quilates[4]={0}, qntplayers=0; //variáveis universais.
int vencedor=0, pmax=-7000, turnos=0, totaldepontos=0;
char nome[4];
char mina[6][6], interface[6][6];
bool fim=false;

const string PADRAO = "\033[0m";  //cores utilizadas nas strings de saída.
const string R = "\033[31m";
const string B = "\033[34m";
const string G = "\033[32m";
const string M = "\033[35m";
const string C = "\033[36m";
const string Y = "\033[33m";
const string GBG = "\033[42m";
const string CBG = "\033[46m";
const string YBG = "\033[43m";

void intro(){ //Texto de start do jogo
    cout << Y << "Bem vindo à caça ao tesouro!" << endl;
    cout << "Aqui, os jogadores devem encontrar diamantes em uma mina!" << endl;
    cout << " " << endl << PADRAO;
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
        cout << C << "Inserir inicial do jogador " << i+1 << " : " << endl << PADRAO;
        cout << R << "AVISO! Iniciais repitidas resultarão em erro." << endl << PADRAO;
        cin >> nome[i];
    }
}

void qntjogadores(){ //Determina a quantidade de jogadores que participarao do jogo
    cout << " " << endl;
    cout << M << "Quantas pessoas vao jogar?" << endl;
    cin >> qntplayers;
    while(qntplayers<2 || qntplayers>4){
        cout << "Valor invalido, o jogo deve ser jogado com 2 a 4 jogadores." << endl;
        cout << "Quantas pessoas vão jogar?" << endl << PADRAO;
        cin >> qntplayers;
    }
}

void promptjogue(){ //Entrada de qual indice da matriz o jogador quer checar para diamantes
    cout << " " << endl;
    cout << Y << "Qual casa você deseja explorar? Por favor insira um número de 1-6 para caida eixo (X e Y)" << endl << PADRAO;
}

void jogadas(int x, int dec, int uni){ //alterna os turnos entre os jogadores, checa a matriz do jogo e atualiza a matriz da interface
    int novosquilates=0;
    int dec2, uni2;
    for(int i=0; i<qntplayers; i++){
        cout << "Vez do jogador " << nome[i] << endl;
        promptjogue();
        cin >> dec2 >> uni2;
        dec=dec2-1;
        uni=uni2-1;
        interface[dec][uni]=nome[i];
        if(mina[dec][uni]='D'){
           novosquilates=rand()%10+1;
           quilates[i]=novosquilates;
           cout << G << "Você achou um diamante de " << novosquilates << " quilates!" << endl;
           totaldepontos+=novosquilates;
        }else if(mina[dec][uni]='+'){
            quilates[i]+=3;
            cout << "Você está no caminho certo e achou 3 quilates!" << endl;
            totaldepontos+=3;
        }else if(mina[dec][uni]='-'){
            quilates[i+1]-=5;
            quilates[i]+=5;
            cout << "Você se escondeu e roubou 5 quilates de um oponente!" << endl << PADRAO;
            totaldepontos+=5;
        }else if(mina[dec][uni]='O'){
            quilates[i]-=10;
            cout << R << "Você caiu num tunel sem saída e perdeu 10 quilates!" << endl << PADRAO;
            totaldepontos-=10;
        }
        cout << GBG;
        for(int i=0; i<6; i++){
            for(int j=0; j<6; j++){
                printf("%c ", interface[i][j]);
            }
        putchar('\n');
        }
        turnos++;
        for(int j=0; j<qntplayers; j++){
        cout << " " << endl;
        cout << B << "O Jogador " << nome[j] << " está com " << quilates[j] << " pontos." << endl << PADRAO;
        cout << " " << endl;
        }
    }
}

void placar(){ //determina e printa o jogador com mais pontos, e escreve a pontuacao dos demais
    for(int i=0; i<qntplayers; i++){
        if(quilates[i]>pmax){
            pmax=quilates[i];
            vencedor=i;
        }
    }
    cout << GBG << "O jogador com mais pontos foi: " << nome[vencedor] << " com " << pmax << " pontos!" << endl << PADRAO;
    cout << " " << endl;
    for(int j=0; j<qntplayers; j++){
        cout << CBG << "O Jogador " << j+1 << " com a inicial " << nome[j] << " teve " << quilates[j] << " pontos." << endl << PADRAO;
        cout << " " << endl;
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
    while(turnos<36/qntplayers){
        jogadas(x, dec, uni);
    }
    fim=true;
    while(fim==true){
        placar();
        break;
    }
    
    
    return 0;
}
