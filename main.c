#include <stdio.h>
#include <stdlib.h>
#include <time.h>

# define maxSize 100
int balls[maxSize] = {};
int players,currSize,currPos,currPlayCount;
int maxPlayCount = maxSize-1;

int _start() {
    int value;
    printf("Enter a number: ");
    while (scanf("%d", &value) != 1) {//checks if given input is not a num
        printf("Please enter a valid number: ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}//removes the chars in value or else the scanf will infinitly fail
    }
    return value;
}//maybe do smth with dynamic arrays for the player bingo cards

int _getRandomNum() {//creates a random number using the seed
    currPos = rand() % currSize + 1;//= random of max amount '+' min value
    return balls[currPos];
}

void deletePos(int pos) {

    if (pos < 0 || pos >= currSize) {
        //basically stops the deletion if its not even in array
        return;
    }
    for (int i = pos; i < currSize - 1; i++) {
        //replaces the currPos witht the prev pos'
        balls[i] = balls[i + 1];
    }
    currSize--;//and srinks the array to simulate deletion


}

void _cardGenerator(int total) {//redundant 2D array but will use for smth else soon
    FILE *printCard;
    printCard = fopen("CardLists.txt","a");
    fprintf(printCard,"------------------------------------------\n");
    for (int i = 1; i <= total;i++) {
        fprintf(printCard,"player %d:\n",i);
        int card[5][5] ={};
        for (int col = 0; col < 5;col++) {
            for (int rows = 0; rows < 5;rows++) {
                card[rows][col] = _getRandomNum();
                fprintf(printCard,"%d |",card[rows][col]);
            }
            fprintf(printCard,"\n");
        }
        fprintf(printCard,"------------------------------------------\n");
    }
    fclose(printCard);
}

void _init() {//initializes the balls
    for (int i = 0; i< maxSize; i++) {
        balls[i] = i;
        //printf("%d\n",maxBalls[i]);
    }
    currSize = maxSize;
    _cardGenerator(_start());
    FILE *printHistory;
    printHistory = fopen("historyText.txt", "a");
        fprintf(printHistory, "Started BINGO game:\n");
        fprintf(printHistory, "----------------------------------------------------------\n");
        fprintf(printHistory, "Given numbers (in right order):\n");
    fclose(printHistory);
}

void _history(int givenKey) {
    FILE *printHistory;//creates a link
    printHistory = fopen("historyText.txt", "a");//opens given file and takes a mode w(write)-a(append)-r(read)
        fprintf(printHistory, "%d-",givenKey);//writes what ever is written like a printf function
    fclose(printHistory);//closes the data
}

void _historyCloser() {
    FILE *printHistory;
    printHistory = fopen("historyText.txt", "a");
        fprintf(printHistory, "\nEnd of game, history successfully updated!\n");
        fprintf(printHistory, "-------------------------------------------------------\n");
        fprintf(printHistory, "-------------------------------------------------------\n");
    fclose(printHistory);
}

void _round() {
    if (currPlayCount < maxPlayCount) {
        currPlayCount++;
        int givenNum = _getRandomNum();
        printf("%d\n", givenNum);
        _history(givenNum);
        deletePos(currPos);
    }else
        printf("you have finished all the BINGO balls!!!");
}

void _playerInput() {
        char next;
        do {
            next = '\000';
            printf("\nEnter 'c' to continue to the next round; else write 'e'...");
            scanf(" %c", &next);//there should be a space before %c so that the scanf will skip anything unwanted (10)
            if (next == 'c') {
                _round();
                next = '\000';
            }
            else if (next == 'e') {
                _historyCloser();
                printf("thx for playing!\n");
                return;
            }
            else{
                printf("\nError please enter valid command; Enter 'c' to continue to the next round; else write 'e'...");
            }
        }while (next != 'c');
}

int main(void) {
    printf("Welcome to BINGO!!!\nTo start the game please enter the amount of players!\n");
    _init();
    srand(time(NULL)); // so everytime gives a different seed
    _playerInput();
    return 0;
}