#include <stdio.h>
#include <stdlib.h>
#include <time.h>
# define maxBallz 100
int maxBalls[] = {};
int maxSize;
void _ballInit() {
    for (int i = 0; i< maxBallz; i++) {
        maxBalls[i] = i;
    }
    maxSize = sizeof(maxBalls) / sizeof(maxBalls[0]);
}
int _getRandomNum() {
    int newNum = rand() % maxSize + 1;
    return maxBalls[newNum];
}
int main(void) {
    srand(time(NULL)); // so everytime gives a different seed
    _ballInit();
    int randGen = _getRandomNum();
    printf("%d\n", randGen);
    return 0;
}