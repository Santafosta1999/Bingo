#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

typedef struct card {
    /* Id do jogador e lista com 9 números aleatórios não repetidos */
    int idPlayer;
    int numbers[9];
} CARD;

typedef struct ranking {
    /* Matriz, onde a primeira posição é o Id do jogador e 
    a segunda a quantidade de números restantes na cartela */
    int classification[30][2];
} RANKING;

void randomNumbers();
int printArray();

int countDraw = 0; // Contador de números já sorteados
int drawNumbers[100]; // Lista com os números já sorteados para não ter repetições
int countPlayers = 0; // Contador de jogadores da partida
CARD listPlayers[30]; // Lista de cartelas dos Jogadores
RANKING ranking; // Ranking da partida

int randomNewPlayer() {
    // Verificar aleatóriamente se será adicionado um novo jogador ou não
    return rand() & 1;
}

int randomStartPlayer() {
    // Definir aleatóriamente quantos jogadores iniciarão a partida
    return rand()%30;
}

int randomNum() {
    // Retornar um número aleatório de 1 à 100
    int num = 0;
    while(num == 0) {
        num = rand()%100;
    }
    return num;
}

CARD *buildCard(int playerId) {
    /* Criação de nova cartela, definindo o idPlayer e chamando um método
    que irá preencher a lista com números aleatórios e não repetidos de 1 à 100 */
    CARD *c;
    c = malloc(sizeof(CARD));
    c->idPlayer = playerId;
    randomNumbers(c->numbers);

    return c;
}

void randomNumbers(int array[]) {
    /* Preencher a cartela com números aleatórios e não repetidos.
    O segundo "while" verifica se o número já foi existe na cartela, se sim, sorteia novamente */
    int i = 0, num;
    while(i < 9) {
        int j = 0;
        num = randomNum();
        while (j < 10) {
            if (j == 10 || (int)array[j] == num) {            
                break;
            } else {
                j++;
            }           
        }
        if (j == 10) {
            array[i] = num;
            i++;
        }
    }
}

void printCard(int idPlayer) {
    // Imprime a cartela do jogador informado
    int i = 0, j = 0;
    printf("\n\nPLAYER %i\n\n", idPlayer);
    while (i < countPlayers) {
        if(listPlayers[i].idPlayer == idPlayer) {
            while (j < 9) {
                printf("Num %i - %i\n", j + 1, (int)listPlayers[i].numbers[j]);
                j++;
            }
            break;
        }
        i++;
    }
}

RANKING *rankingHits() {
    // Ordena o ranking da partida utilizando Selection Sort
    int i, j, min, id, num;
    for (i = 0; i < (countPlayers - 1); i++) {
        min = i;
        for (j = i + 1; j < countPlayers; j++) {
            if ((int)ranking.classification[j][1] < (int)ranking.classification[min][1]) {
                min = j;
            }
        }
        if (i != min)
        {
            id = (int)ranking.classification[i][0];
            num = (int)ranking.classification[i][1];
            ranking.classification[i][0] = (int)ranking.classification[min][0];
            ranking.classification[i][1] = (int)ranking.classification[min][1];
            ranking.classification[min][0] = id;
            ranking.classification[min][1] = num;
        }
    }
    return &ranking;
}

void writeRanking(RANKING *ranking) {
    // Imprime na tela o Ranking e se houver ganhador, informa seu Id e imprime sua cartela
    int i = 0;
    printf("*-----------------------------*\n");
    printf("| POSICAO | JOGADOR | ACERTOS |\n");
    printf("|-----------------------------|\n");
    while(i < countPlayers) {
        printf("|    %2i   |    %2i   |    %i    |\n", i + 1, ranking->classification[i][0], 9 - (int)ranking->classification[i][1]);
        i++;
    }
    printf("*-----------------------------*\n\n\n");

    if((int)ranking->classification[0][1] == 0) {
        printf("Vencedor(es):\n");
        i = 0;
        while(i < countPlayers) {
            if((int)ranking->classification[i][1] == 0) {
                printf("JOGADOR %i!\n", (int)ranking->classification[i][0]);
                printCard((int)ranking->classification[i][0]);
            }
            i++;
        }
    }
    
}

int winner(int lastDraw) {
    /* Verifica quem acertou na rodada, imprime o número da rodada,
    o número sorteado e imprime o ranking, sempre verificando se há ganhador */
    int ret = 0, i = 0;   
    while (i < countPlayers) {
        int j = 0;
        while (j < 9) {
            if (listPlayers[i].numbers[j] == lastDraw) {              
                ranking.classification[i][1]--; 
                break;
            }
            j++;       
        }
        if (ranking.classification[i][1] == 0) {
            ret = 1;
        }
        i++;       
    }

    printf("Rodada %i - Numero Sorteado: %i\n", countDraw, lastDraw);
    writeRanking(rankingHits());

    return ret;
}

int drawNumber() {
    // Sorteia o número da rodada, verificando se ele já não foi sorteado antes e se não há ganhador na partida
    int i = 0;
    int num = randomNum();
    if (countDraw != 0 && countDraw < 100) {
        while (i < countDraw) {
            if ((int)drawNumbers[i] == num) {
                i = -1;            
                break;
            } else {
                i++;
            }           
        }     
    }
    if (i != -1) {
        drawNumbers[countDraw] = num;
        countDraw++;
    }
    Sleep(1000);
    return winner(num); // 0 - sorteia; 1-fim de jogo
}

void addPlayer(CARD *c) {
    // Método que adiciona novo jogador, criando sua cartela, e adicionando na lista de jogadores e no Ranking
    countPlayers++;
    c = buildCard(countPlayers);
    listPlayers[countPlayers - 1] = *c;
    ranking.classification[countPlayers - 1][0] = countPlayers; 
    ranking.classification[countPlayers - 1][1] = 9;
}

int main() {
    CARD *c;
    c = malloc(sizeof(CARD));

    srand(time(NULL)); // Utilizado para deixar o randon realmente aleatório
    
    int newDraw = 0, beginPlayers = randomStartPlayer();
    while (countPlayers <= beginPlayers) {
        addPlayer(c);
    }

    while (newDraw == 0) {
        newDraw = drawNumber();
        if (randomNewPlayer() == 1 && countPlayers < 30){
            addPlayer(c);
        }
    }
}
