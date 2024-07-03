
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define WIDTH 40
#define HEIGHT 20

int snake_x[100];
int snake_y[100];
int food_x, food_y;
int direction = 'r'; // r, l, u, d
int score = 0;

void place_food();

void setup() {
    system("cls");
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        printf("#");
        for (int j = 0; j < WIDTH; j++)
            printf(" ");
        printf("#\n");
    }

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    snake_x[0] = WIDTH / 2;
    snake_y[0] = HEIGHT / 2;
    place_food();
}

void draw() {
    system("cls");
    for (int i = 0; i <= WIDTH + 1; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                printf("#");
            if (i == snake_y[0] && j == snake_x[0])
                printf("O");
            else if (i == food_y && j == food_x)
                printf("*");
            else {
                int print = 0;
                for (int k = 1; k < score; k++) {
                    if (snake_y[k] == i && snake_x[k] == j) {
                        printf("o");
                        print = 1;
                    }
                }
                if (!print)
                    printf(" ");
            }

            if (j == WIDTH - 1)
                printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i <= WIDTH + 1; i++)
        printf("#");
    printf("\n");

    printf("Score: %d\n", score);
}

void place_food() {
    food_x = rand() % WIDTH;
    food_y = rand() % HEIGHT;
    for (int i = 0; i < score; i++) {
        if (snake_y[i] == food_y && snake_x[i] == food_x)
            place_food();
    }
}

bool game_over() {
    int gameOver = 0;
    if (snake_x[0]<0 || snake_x[0]>WIDTH || snake_y[0]<0 || snake_y[0]>HEIGHT)
        gameOver = 1;
    for (int i = 1; i < score; i++) {
        if (snake_y[0] == snake_y[i] && snake_x[0] == snake_x[i])
            gameOver = 1;
    }
    return gameOver;
}

void move() {
    for (int i = score; i > 0; i--) {
        snake_y[i] = snake_y[i - 1];
        snake_x[i] = snake_x[i - 1];
    }

    if (direction == 'u')
        snake_y[0]--;
    if (direction == 'd')
        snake_y[0]++;
    if (direction == 'l')
        snake_x[0]--;
    if (direction == 'r')
        snake_x[0]++;
}

void input() {
    if (GetAsyncKeyState(VK_UP))
        direction = 'u';
    if (GetAsyncKeyState(VK_DOWN))
        direction = 'd';
    if (GetAsyncKeyState(VK_LEFT))
        direction = 'l';
    if (GetAsyncKeyState(VK_RIGHT))
        direction = 'r';
}

int main() {
    srand(time(NULL));
    setup();

    while (true) {
        if (game_over()) {
            printf("Game Over!\nFinal Score: %d\n", score);
            return 0;
        }

        input();
        move();

        if (snake_x[0] == food_x && snake_y[0] == food_y) {
            score++;
            place_food();
        }

        draw();
        Sleep(200);
    }

    return 0;
}
