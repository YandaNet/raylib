#include "raylib.h"
#include <vector>
#include <ctime>
#include <cstdlib>

class Parts {
public:
    int x, y;
};

int main()
{
    srand(time(0));

    int screen_size_width = 800;
    int screen_size_height = 800;

    InitWindow(screen_size_width, screen_size_height, "Snake");
    SetTargetFPS(10);

    int size = 20;
    int vectorX = size;
    int vectorY = 0;
    int score = 0;

    std::vector<Parts> snake = { {100, 100} };

    int itemx = rand() % (screen_size_width - size);
    int itemy = rand() % (screen_size_height - size);

    while (!WindowShouldClose())
    {
        // Керування
        if (IsKeyPressed(KEY_RIGHT) && vectorX == 0) {
            vectorX = size; vectorY = 0;
        }
        if (IsKeyPressed(KEY_LEFT) && vectorX == 0) {
            vectorX = -size; vectorY = 0;
        }
        if (IsKeyPressed(KEY_UP) && vectorY == 0) {
            vectorY = -size; vectorX = 0;
        }
        if (IsKeyPressed(KEY_DOWN) && vectorY == 0) {
            vectorY = size; vectorX = 0;
        }

        // Рух тіла (з кінця до голови)
        for (int i = snake.size() - 1; i > 0; i--) {
            snake[i] = snake[i - 1];
        }

        // Рух голови
        snake[0].x += vectorX;
        snake[0].y += vectorY;

        // Межі
        if (snake[0].x < 0) snake[0].x = 0;
        if (snake[0].y < 0) snake[0].y = 0;
        if (snake[0].x + size > screen_size_width) snake[0].x = screen_size_width - size;
        if (snake[0].y + size > screen_size_height) snake[0].y = screen_size_height - size;

        Rectangle head = { (float)snake[0].x, (float)snake[0].y, (float)size, (float)size };
        Rectangle item = { (float)itemx, (float)itemy, (float)size, (float)size };

        // Зіткнення
        if (CheckCollisionRecs(head, item))
        {
            score++;

            // ДОДАЄМО СЕГМЕНТ
            snake.push_back(snake.back());

            itemx = rand() % (screen_size_width - size);
            itemy = rand() % (screen_size_height - size);
        }

        // Малювання
        BeginDrawing();
        ClearBackground(BLACK);

        // Малюємо змійку
        for (auto& part : snake) {
            DrawRectangle(part.x, part.y, size, size, GREEN);
        }

        DrawRectangle(itemx, itemy, size, size, RED);
        DrawText(TextFormat("Score: %i", score), 10, 10, 24, GREEN);

        EndDrawing();
    }

    CloseWindow();
}