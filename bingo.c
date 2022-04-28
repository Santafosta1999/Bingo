#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

typedef struct card {
    /* Id do jogador, lista com 9 números aleatórios não repetidos */
    int idPlayer;
    int numbers[9];
} CARD;

typedef struct ranking {
    int classification[30][2];
} RANKING;

void randomNumbers();
int printArray();

int countDraw = 0;
int drawNumbers[100];
int countPlayers = 0;
CARD listPlayers[30];
RANKING ranking;

int randomNewPlayer() {
    return rand() & 1;
}

int randomStartPlayer() {
    return rand()%30;
}

int randomNum() {
    int num = 0;
    while(num == 0) {
        num = rand()%100;
    }
    return num;
}

CARD *buildCard(int playerId) {
    CARD *c;
    c = malloc(sizeof(CARD));
    c->idPlayer = playerId;
    randomNumbers(c->numbers, playerId);

    return c;
}

void randomNumbers(int array[], int player) {
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

int printArray(int array[], int player) {
    int i = 0;
    printf("\n\nPLAYER %i\n\n", player);
    while (i < 9)
    {
        printf("Pos %i - %i\n", i, (int)array[i]);
        i++;
    }
    return 0;
}

RANKING *rankingHits() {
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
    int i = 0;
    printf("*-----------------------------*\n");
    printf("| POSICAO | JOGADOR | ACERTOS |\n");
    printf("|-----------------------------|\n");
    while(i < countPlayers) {
        printf("|    %2i   |    %2i   |    %2i   |\n", i + 1, ranking->classification[i][0], 9 - (int)ranking->classification[i][1]);
        i++;
    }
    printf("*-----------------------------*\n\n\n");

    if((int)ranking->classification[0][1] == 0) {
        printf("Vencedor(es):\n");
        i = 0;
        while(i < countPlayers) {
            if((int)ranking->classification[i][1] == 0) {
                printf("JOGADOR %i!\n", (int)ranking->classification[i][0]);
            }
            i++;
        }
    }
    
}

int winner(int lastDraw) {
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
    //Sorteia
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
    countPlayers++;
    c = buildCard(countPlayers);
    listPlayers[countPlayers - 1] = *c;
    ranking.classification[countPlayers - 1][0] = countPlayers; 
    ranking.classification[countPlayers - 1][1] = 9;
}

int main() {
    CARD *c;
    c = malloc(sizeof(CARD));

    srand(time(NULL));
    
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
