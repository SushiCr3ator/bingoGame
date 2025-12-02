#include <stdio.h>
#include <stdlib.h>
#include <time.h>

# define maxSize 10
int balls[maxSize] = {};
int players,currSize,currPos;

int _start() {
    while (scanf("%d", &players) != 1) {
        printf("Please enter a valid number: ");
        // clear invalid characters from input
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        if (scanf("%d", &players) == 1) {
            return 0;
        }
        _start();
    }
}

void _ballInit() {//initializes the balls
    for (int i = 0; i< maxSize; i++) {
        balls[i] = i;
        //printf("%d\n",maxBalls[i]);
    }
    currSize = maxSize;
}

int _getRandomNum() {//creates a random number using the seed
    currPos = rand() % currSize + 1;//= random of max amount '+' min value
    return balls[currPos];
}

void deletePos(int pos) {
    if (pos < 0 || pos >= currSize)//basically stops the deletion if its not even in array
        return;
    for (int i = pos; i < currSize - 1; i++)//replaces the currPos witht the prev pos'
        balls[i] = balls[i + 1];
    currSize--;//and srinks the array to simulate deletion
}

void _newRound() {
    printf("%d\n", _getRandomNum()); //line 29
    deletePos(currPos);
    char next;
    printf("\nEnter 'c' to continue to the next round; else write 'e'...");
    do {
        scanf("%c", &next);
        if (next == 'c')
                _newRound();
        if (next == 'e')
                exit(0);
        printf("please write a valid command...");
    }while (next != 'c');

}
int main(void) {
    printf("Welcome to BINGO!!!\nTo start the game please enter the amount of players:\n");
    _ballInit();
    //_start();
    srand(time(NULL)); // so everytime gives a different seed
    _newRound();


    return 0;
}