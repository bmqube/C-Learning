#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

typedef struct Point {
    int x, y;
}Point;

typedef struct Scr {
    char name[100];
    int currScore;
}Scr;


int isGameOver;
Point head, fruit, tail[200];
int height, width;
int score;
int nTail;

enum direction{S = 0, LEFT, RIGHT, UP, DOWN};
enum direction dir;

void ClearScreen();
void instructions();
void load();
void initial();
void board();
void keyPress();
void logic();
void insertSorted(Scr ara[], Scr curr, int n);
void scoreBoard();
void about();
void leaderboard();
void menu();

int main() {
    menu();

    return 0;
}

void ClearScreen(){
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void instructions() {
    system("cls");
    printf("\tGame Instructions: \n");
    printf("\n=> Use W, A, S, D on your keyboard to move\n"
           "\n=> The game will end once you hit yourself\n"
           "\n=> You will be given food at random coordinates, you have to eat them in order to score higher\n"
           "\n=> The given food is like 'Complan' which will make the snake grow faster xD\n"
           "\n=> Press 'x' to terminate the game\n");
    printf("\nPress any key to continue...\n");
    getch();
}

void load() {
    system("cls");
    printf("\n\n\n\n\n\n\t\tLoading.....\n");
    printf("\t");
    for(int i=1; i<=28; i++) {
        Sleep(100);
        printf("%c", 177);
    }
    printf("\n\n\n\n\n\n\n\n\n\n");
    system("cls");
}

void initial() {
    isGameOver = 0;
    dir = S;

    height = 20;
    width = 40;

    head.x = width / 2;
    head.y = height / 2;

    srand((time(0)));
    fruit.x = rand() % width;
    srand((time(0)));
    fruit.y = rand() % height;

    score = 0;
    nTail = 0;
}

void board() {
    ClearScreen();
    for (int i = 0; i < width+2; i++) {
        printf("#");
    }
    printf("\n");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) {
                printf("#");
            }
            if (i == head.y && j == head.x) {
                printf("O");
            } else if (i == fruit.y && j == fruit.x) {
                printf("\033[1;32m");
                printf("%c", 254);
                printf("\033[0m");
            } else {
                int isPrinted = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tail[k].x == j && tail[k].y == i) {
                        printf("o");
                        isPrinted = 1;
                    }
                }
                if (!isPrinted) {
                    printf(" ");
                }
            }
            if (j == width-1) {
                printf("#");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < width+2; i++) {
        printf("#");
    }
    printf("\nScore: %d\n", score);
}

void keyPress() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w':
            case 'W':
                if (dir != DOWN) {
                    dir = UP;
                }
                break;
            case 'a':
            case 'A':
                if (dir != RIGHT) {
                    dir = LEFT;
                }
                break;
            case 's':
            case 'S':
                if (dir != UP) {
                    dir = DOWN;
                }
                break;
            case 'd':
            case 'D':
                if (dir != LEFT) {
                    dir = RIGHT;
                }
                break;
            case 'x':
            case 'X':
                isGameOver = 1;
                break;
        }
    }
}

void logic() {
    for (int i = nTail - 1; i > 0; i--) {
        tail[i].x = tail[i-1].x;
        tail[i].y = tail[i-1].y;
    }
    tail[0].x = head.x;
    tail[0].y = head.y;
    switch (dir) {
        case LEFT:
            head.x--;
            break;
        case RIGHT:
            head.x++;
            break;
        case UP:
            head.y--;
            break;
        case DOWN:
            head.y++;
            break;
    }
    if (head.x >= width) {
        head.x = 0;
    } else if (head.x < 0) {
        head.x = width - 1;
    }

    if (head.y >= height) {
        head.y = 0;
    } else if (head.y < 0) {
        head.y = height - 1;
    }

    for (int i = 0; i < nTail; i++) {
        if (head.x == tail[i].x && head.y == tail[i].y) {
            isGameOver = 1;
        }
    }

    if (head.x == fruit.x && head.y == fruit.y) {
        score += 10;
        nTail++;

        srand((time(0)));
        fruit.x = rand() % width;
        srand((time(0)));
        fruit.y = rand() % height;
    }
}

void insertSorted(Scr ara[], Scr curr, int n) {
    int ind = 0;
    while (ind < n && ara[ind].currScore >= curr.currScore) {
        ind++;
    }

    for (int i = n; i > ind; i--) {
        ara[i] = ara[i-1];
    }

    ara[ind] = curr;
}

void scoreBoard() {
    int k = 0;
    Scr *ara = (Scr*)(malloc(7*sizeof(Scr)));
    Scr curr;
    FILE *fpr = fopen("score.txt", "r");

    for (int i = 0; i < 6; i++) {
        ara[i].currScore = 0;
    }

    while (fscanf(fpr, "%[^,], %d\n", ara[k].name, &ara[k].currScore) != EOF) {
        k++;
    }

    FILE *fpw = fopen("score.txt", "w");

    if (score) {
        curr.currScore = score;
        printf("Enter your name: ");
        scanf("\n");
        gets(curr.name);
        if (k == 5 && curr.currScore <= ara[k-1].currScore) {
            printf("Sorry your score is too low to be in leaderboard\n");
        } else if (curr.currScore > ara[0].currScore) {
            printf("Congratulations for achieving highest score!\n");
            insertSorted(ara, curr, k);
            if (k < 5) {
                k++;
            }
        } else {
            printf("Score added to the leaderboard\n");
            insertSorted(ara, curr, k);
            if (k < 5) {
                k++;
            }
        }
    }

    for (int i = 0; i < k; i++) {
        fprintf(fpw, "%s, %d\n", ara[i].name, ara[i].currScore);
    }
    fclose(fpr);
    fclose(fpw);
    printf("\nPress any key to continue...\n");
    getch();
}

void about() {
    system("cls");
    printf("======================================\n");
    printf("Name:           BM Monjur Morshed\n");
    printf("Institue:       North South University\n");
    printf("Course Code:    CSE115\n");
    printf("Semester:       Spring 2020\n");
    printf("ID:             201****642\n");
    printf("======================================\n");
    printf("\nPress any key to continue...\n");
    getch();
}

void leaderboard() {
    system("cls");
    int k = 0;
    Scr *ara = (Scr*)(malloc(7*sizeof(Scr)));
    FILE *fpr = fopen("score.txt", "r");

    while (fscanf(fpr, "%[^,], %d\n", ara[k].name, &ara[k].currScore) != EOF) {
        k++;
    }

    printf("=============================\n");
    printf(" Name                  Score \n");
    printf("=============================\n");
    for (int i = 0; i < k; i++) {
        printf(" %-20s %5d  \n", ara[i].name, ara[i].currScore);
    }
    fclose(fpr);
    printf("\nPress any key to continue...\n");
    getch();
}

void menu() {
    char ch;
    do {
        system("cls");
        printf("P. Play Game\n");
        printf("L. Leader Board\n");
        printf("I. Instructions\n");
        printf("A. About\n");
        printf("Q. Quit\n");
        printf("\nChoose Option: ");
        scanf("\n%c", &ch);
        switch (ch) {
            case 'p':
            case 'P':
                load();
                initial();
                while (!isGameOver) {
                    board();
                    keyPress();
                    logic();
                }
                scoreBoard();
                break;

            case 'i':
            case 'I':
                instructions();
                break;

            case 'l':
            case 'L':
                leaderboard();
                break;

            case 'a':
            case 'A':
                about();
                break;

            case 'q':
            case 'Q':
                printf("Have a good day\n");
                exit(0);

            default:
                printf("\nInvalid Option, Try again\n");
                Sleep(1000);
        }
    } while(ch != 'q' && ch != 'Q');
}
