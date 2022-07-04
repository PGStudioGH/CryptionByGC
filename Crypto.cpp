#define _CRT_SECURE_NO_WARNINGS
#define MAX_KEY 64
#define LINE 2

//Глобальная инициализация
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

#include "Window.h"
#include "Characters.h"

//Запуск программы
int main(int argc, char *argv[])
{
    int i, j, a;
    char symbol = 0;

    //Создание окон
    createWindow(MAX_KEY / LINE + 2, LINE + 3);
    system("title Cryption by GC");
    std::cout << "\x1b[?25l\x1b[H";
    std::cout << "\x1b[38;2;224;224;224m\x1b[48;2;0;128;16m";
    std::cout << rtc;
    for (i = 0; i < MAX_KEY / LINE / 2 - 5; i++) std::cout << hl;
    std::cout << " Cryption ";
    for (i = 0; i < MAX_KEY / LINE / 2 - 5; i++) std::cout << hl;
    std::cout << ltc;
    for (i = 0; i < LINE; i++)
    {
        std::cout << vl << "\x1b[38;2;0;0;0m\x1b[48;2;0;64;8m";
        for (j = 0; j < MAX_KEY / LINE; j++) std::cout << SPACE;
        std::cout << "\x1b[38;2;224;224;224m\x1b[48;2;0;128;16m" << vl;
    }
    std::cout << rbc;
    for (i = 0; i < MAX_KEY / LINE; i++) std::cout << hl;
    std::cout << lbc;
    std::cout << "\x1b[38;2;192;192;192m\x1b[48;2;0;64;8m";
    for (i = 0; i < MAX_KEY / LINE - 2; i++) std::cout << SPACE;
    std::cout << "2022\x1b[H\x1b[" << LINE + 2 << "BBy GC";
    std::cout << "\x1b[H\x1b[1B\x1b[12CPlease write password\x1b[1B\x1b[14DOnly A-z & 0-9";

    if (argc - 1)
    {
        //Инициализация
        bool isVisibleCursor;
        char count = 0;
        char key[MAX_KEY];
        clock_t msec;
        for (i = 0; i < MAX_KEY; i++) key[i] = SPACE;

        //Цикл
        while (symbol != ENTER)
        {
            symbol = 0;
            isVisibleCursor = 0;
            msec = clock() + 100;
            while (!symbol)
            {
                if (clock() > msec)
                {
                    if (count < MAX_KEY)
                    {
                        isVisibleCursor = !isVisibleCursor;
                        if (isVisibleCursor) key[count] = 178;
                        else key[count] = SPACE;
                        msec = clock() + 100;

                        std::cout << "\x1b[H\x1b[" << count / (MAX_KEY / LINE) + 1;
                        std::cout << "B\x1b[" << count % (MAX_KEY / LINE) + 1 << 'C';
                        std::cout << key[count];
                    }
                }

                if (_kbhit())
                {
                    symbol = _getch();
                    if (count < MAX_KEY) key[count] = SPACE;
                }
                else if (CheckFullScreen()) return 1;
            }

            if (symbol == BACKSPACE)
            {
                if (count > 0) key[--count] = SPACE;
                else std::cout << '\a';
            }
            else if (symbol == TAB) for (i = count = 0; i < MAX_KEY; i++) key[i] = SPACE;
            else if (symbol == ESC) return 0;
            else if ((n0 <= symbol && symbol <= n9) ||
                (c_A <= symbol && symbol <= c_Z) ||
                (c_a <= symbol && symbol <= c_z))
            {
                if (count < MAX_KEY) key[count++] = symbol;
                else std::cout << '\a';
            }
            else std::cout << '\a';

            std::cout << "\x1b[H";
            for (i = 0; i < MAX_KEY; i++)
            {
                if (i % (MAX_KEY / LINE) == 0) std::cout << "\x1b[1B\x1b[2G";
                std::cout << key[i];
            }
            std::cout << "\x1b[H\x1b[1B\x1b[" << count % (MAX_KEY / LINE) + 1 << 'C';
        }

        //Инициализация перед открытием файла
        long size_file;
        if (count < MAX_KEY) key[count] = '\0';

        std::cout << "\x1b[H";
        for (i = 0; i < MAX_KEY; i++)
        {
            if (i % (MAX_KEY / LINE) == 0) std::cout << "\x1b[1B\x1b[2G";
            std::cout << SPACE;
        }
        std::cout << "\x1b[H\x1b[1B\x1b[1CLoading...\x1b[B\x1b[2GPlease wait";

        //Открытие файла
        for (a = 0; a < argc; a++)
        {
            std::fstream in(argv[a + 1], std::ios::binary | std::ios::in);
            if (in.is_open())
            {
                //Инициализация
                std::fstream get_size(argv[a + 1], std::ios::in);
                get_size.seekp(0, std::ios::end);
                size_file = (long)get_size.tellg();
                get_size.close();

                //Создание массива со размером файла
                char* text = new char[size_file];

                //Данные из файла в массив
                in.read(text, size_file);
                in.close();

                //Шифрование или расшифрование
                for (i = 0, j = strlen(key); i < size_file; i++)
                {
                    text[i] ^= key[i % j];
                }

                //Данные из массива в файл
                std::fstream out(argv[a + 1], std::ios::binary | std::ios::out);
                out.write(text, size_file);
                out.close();

                //Очистка
                delete[] text;
            }
            else std::cout << "\nНе найден файл\n";
        }
    }
    else
    {
        std::cout << "\x1b[H\x1b[1B\x1b[8CPlease upload file to the\x1b[1B\x1b[27Dapplication, as in a folder";

        //Выход
        symbol = _getch();
    }

    return 0;
}