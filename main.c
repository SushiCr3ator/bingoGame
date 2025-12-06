#include <stdio.h>
#include <stdlib.h>
#include <time.h>

# define maxSize 75
int balls[maxSize] = {};
int players,currSize,currPlayCount;
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
}

int _getRandomNum() {//creates a random number using the seed
    int currPos = rand() % currSize;//= random of max amount '+' min value
    return currPos;
}

void _deletePos(int arr[], int pos) {
    for (int i = pos; i < currSize-1; i++) {
        //replaces the currPos witht the prev pos'
        arr[i] = arr[i + 1];
    }
    currSize--;//and srinks the array to simulate deletion
}

int _checkPos(int forCheckNum[],int gNum) {
    int returnedNum;
    for (int z = 0; z <= sizeof(forCheckNum);z++) {
        if (forCheckNum[z] == gNum) {
            gNum = _getRandomNum();
            z = 0;
        }
    }
    returnedNum = gNum;
    return returnedNum;
}

void _cardGenerator(int total) {//redundant 2D array but will use for smth else soon
    FILE *printCard;
    printCard = fopen("CardLists.txt","a");
    fprintf(printCard,"------------------------------------------\n");
    for (int i = 1; i <= total;i++) {
        fprintf(printCard,"player %d:\n",i);
        int card[5][5] = {};
        int checkNum[25] = {};
        for (int col = 0; col < 5;col++) {
            for (int rows = 0; rows < 5;rows++) {
                int x = _getRandomNum();
                x = _checkPos(checkNum, x);
                card[rows][col] = balls[x];
                fprintf(printCard,"%d |",card[rows][col]);
                for (int v = 0; v < sizeof(checkNum);v++) {
                    if (checkNum[v] == 0) {
                        checkNum[v] = card[rows][col];
                        break;
                    }
                }
            }
            fprintf(printCard,"\n");
        }
        fprintf(printCard,"------------------------------------------\n");
    }
    fclose(printCard);
}

void _init() {//initializes the balls
    for (int i = 0; i< maxSize; i++) {
        balls[i] = i+1;
        //printf("%d\n",balls[i]);
    }
    currSize = maxSize;
    _cardGenerator(_start());//gen amount of cards depending on how much players are given
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
    if (currPlayCount <= maxPlayCount) {
        currPlayCount++;
        int givenNum = _getRandomNum();
        printf("%d\n", balls[givenNum]);
        _history(balls[givenNum]);
        _deletePos(balls,givenNum);
    }else
        printf("you have finished all the BINGO balls!!!");
}

void _playerInput() {
    char next;
    while (next != 'e') {
        printf("\nEnter 'p' to continue to the next round; 'c' to clear data; else write 'e'...");
        scanf(" %c", &next);//there should be a space before %c so that the scanf will skip anything unwanted (10)
        switch (next) {
            case 'p':
                _round();
                next = '\000';
                break;
            case 'e':
                _historyCloser();
                printf("thx for playing!\n");
                break;
            case 'c':
                FILE *f = fopen("historyText.txt", "w");
                fprintf(f, "BingoGame History:\n----------------------------------------------------------\n");
                fclose(f);
                FILE *c = fopen("CardLists.txt", "w");
                fprintf(c, "Generated Cards:\n----------------------------------------------------------\n");
                fclose(c);
                printf("history and cards successfully cleared!");
                exit(0);
        default:
            printf("\nError please enter valid command; Enter 'c' to continue to the next round; else write 'e'...");
                break;
        }
    }
}

int main(void) {
    printf("Welcome to BINGO!!!\nTo start the game please enter the amount of players!\n");
    _init();
    srand(time(NULL)); // so everytime gives a different seed
    _playerInput();
    return 0;
}