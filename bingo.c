#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    int i = 0;
    int num;
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

int winner(int lastDraw) {
    int i = 0;   
    while (i < countPlayers) {
        int j = 0;
        while (j < 9) {
            if (listPlayers[i].numbers[j] == lastDraw) {    
                printf("Jogador: %i\nNumero: %i\nSorteio: %i\n",listPlayers[i].idPlayer, listPlayers[i].numbers[j], lastDraw);            
                ranking.classification[i][1]--; 
                printf("Numeros Restantes: %i\n\n", ranking.classification[i][1]);
                break;
            }
            j++;       
        }
        if (ranking.classification[i][1] == 0) {
            printf("Ganhador: JOGADOR %i\n\n", listPlayers[i].idPlayer);
            printf("Numeros:\n");
            int k = 0;
            while (k < 9) {
                printf("Pos %i: %i\n", k, listPlayers[i].numbers[k]);
                k++;
            }
            return 1;
        }
        i++;       
    }
    return 0;
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
    return winner(num); // 0 - sorteia; 1-fim de jogo
}

int main() {
    CARD *c;
    
    int newDraw = 0, beginPlayers = randomStartPlayer();
    while (countPlayers <= beginPlayers) {
        countPlayers++;
        c = buildCard(countPlayers);
        listPlayers[countPlayers - 1] = *c;
        ranking.classification[countPlayers - 1][0] = countPlayers; 
        ranking.classification[countPlayers - 1][1] = 9;
    }

    while (newDraw == 0) {
        newDraw = drawNumber();
        if (randomNewPlayer() == 1 && countPlayers < 30){
            countPlayers++;
            c = buildCard(countPlayers);
            listPlayers[countPlayers - 1] = *c;
            ranking.classification[countPlayers - 1][0] = countPlayers; 
            ranking.classification[countPlayers - 1][1] = 9;
        }
    }
}
