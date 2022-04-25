#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int randomNumbers();
int printArray();

typedef struct card {
    /* Id do jogador, lista com 9 números aleatórios não repetidos */
    int idPlayer;
    int numbers[9];
} CARD;

typedef struct ranking {
    CARD classification[30];
} RANKING;

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

int randomNumbers(int array[], int player) {
    int i = 0;
    int j = 0;
    int num = 0;
    while(i < 9) {
        num = rand()%100;
        while (j < i) {
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
    printArray(array, player);
    return 0;
}

int printArray(int array[], int player) {
    int i = 0;
    printf("PLAYER %i\n\n", player);
    while (i < 9)
    {
        printf("Pos %i - %i\n", i, (int)array[i]);
        i++;
    }
    return 0;
}

RANKING *rankingHits() {
    return NULL;
}

int drawNumber() {
    return 0; // 0 - sorteia; 1-fim de jogo
}

int main() {
    /*CARD *c = NULL;*/
    int newDraw = 0, countPlayers = 0, beginPlayers = randomStartPlayer();
    while (countPlayers <= beginPlayers) {
        buildCard(countPlayers++);
    }

    while (newDraw == 0) {
        newDraw = drawNumber();
        if (randomNewPlayer() == 1 && countPlayers < 30){
            buildCard(countPlayers++);
        }
    }
}