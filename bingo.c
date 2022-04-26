#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct card {
    /* Id do jogador, lista com 9 números aleatórios não repetidos */
    int idPlayer;
    int numbers[9];
} CARD;

typedef struct ranking {
    int idPlayer;
    int remNumbers;
} RANKING;

void randomNumbers();
int printArray();
RANKING ranking;

int randomNewPlayer() {
    return rand() & 1;
}

int randomStartPlayer() {
    return rand()%30;
}

CARD *buildCard(int playerId) {
    CARD *c;
    c = malloc(sizeof(CARD));
    c->idPlayer = playerId;
    randomNumbers(c->numbers, playerId);

    return c;
}

void randomNumbers(int array[], int player) {
    int i = 0;
    int num;
    while(i < 9) {
        int j = 0;
        num = rand()%100;
        while (j < 10) {
            if (j == 10 || (int)array[j] == num) {            
                break;
            } else {
                j++;
            }           
        }
        if (j == 10 && num != 0) {
            array[i] = num;
            i++;
        }
    }
    /*printArray(array, player);*/
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
    int i = 0;
    int j = 0;
    
    while(i < 30) {
        while(j < 9) {
            j++;
        }
        i++;
    }
    return NULL;
}

int drawNumber() {
    //Verifica se há ganhador
    if (false) {
        return 1;
    }
    
    return 0; // 0 - sorteia; 1-fim de jogo
}

int winner() {
    for 
}

int main() {
    CARD *c;
    
    int newDraw = 0, countPlayers = 0, beginPlayers = randomStartPlayer();
    while (countPlayers <= beginPlayers) {
        countPlayers++;
        c = buildCard(countPlayers);
        ranking.classification[countPlayers - 1] = c->playerId;
    }

    while (newDraw == 0) {
        newDraw = drawNumber();
        if (randomNewPlayer() == 1 && countPlayers < 30){
            countPlayers++;
            c = buildCard(countPlayers);
            ranking.classification[countPlayers - 1] = *c;
        }
    }
}
