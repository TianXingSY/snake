
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <iostream>
#include <conio.h>

#define WIDTH 40
#define HEIGHT 20
char frameBuffer[HEIGHT][WIDTH + 2];

int snake_x[100];
int snake_y[100];
int food_x, food_y;
int direction = 'r'; // r, l, u, d
int score = 0;
int n = 3;


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
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = { WIDTH + 2, HEIGHT };
    SMALL_RECT windowSize = { 0, 0, WIDTH + 1, HEIGHT - 1 };

    SetConsoleScreenBufferSize(hConsole, bufferSize);
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    // 清除屏幕并设置光标位置
    COORD coord = { 0, 0 };
    DWORD written;
    FillConsoleOutputCharacterA(hConsole, ' ', WIDTH * HEIGHT, coord, &written);
    SetConsoleCursorPosition(hConsole, coord);

    // 从缓冲区打印到屏幕
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j <= WIDTH + 1; j++) {
            std::cout << frameBuffer[i][j];
        }
        std::cout << std::endl;
    }

    // 更新缓冲区
    for (int i = 0; i <= WIDTH + 1; i++)
        frameBuffer[0][i] = '#';

    for (int i = 0; i < HEIGHT; i++) {
        frameBuffer[i][0] = '#';
        for (int j = 0; j < WIDTH; j++) {
            if (i == snake_y[0] && j == snake_x[0])
                frameBuffer[i][j + 1] = 'O';
            else if (i == food_y && j == food_x)
                frameBuffer[i][j + 1] = '*';
            else {
                bool printed = false;
                for (int k = 1; k < n; k++) {
                    if (snake_y[k] == i && snake_x[k] == j) {
                        frameBuffer[i][j + 1] = 'o';
                        printed = true;
                    }
                }
                if (!printed)
                    frameBuffer[i][j + 1] = ' ';
            }
            frameBuffer[i][WIDTH + 1] = '#';
        }
    }

    for (int i = 0; i <= WIDTH + 1; i++)
        frameBuffer[HEIGHT - 1][i] = '#';

    std::cout << "得分: " << score << std::endl;
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
    // 获取控制台输出句柄
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // 设置文字颜色为红色，背景颜色为蓝色
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_GREEN|BACKGROUND_BLUE);
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
