#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#define Y 9
#define X 21

static bool const bruh[Y][X] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0 },
    { 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0 },
    { 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0 },
    { 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

static char const *r;
static char const *g;
static char const *b;

inline static void reset()
{
    printf("\e[0m");
}

inline static void set_bg()
{
    printf("\e[48;2;%s;%s;%sm", r, g, b);
}

inline static void pixel()
{
    printf("  ");
}

inline static void clear()
{
    printf("\e[2J");
}

inline static void set_cursor(unsigned y, unsigned x)
{
    printf("\e[%u;%uH", y, x);
}

static void print(unsigned const h, unsigned const w)
{
    clear();
    set_cursor(0, 0);

    bool bg = false;

    for (unsigned y = 0; y < h; ++y)
    {
        if (bg)
            set_bg();

        for (unsigned x = 0; x < w; ++x)
        {
            if (bruh[y * Y / h][x * X / w] != bg)
            {
                bg = bruh[y * Y / h][x * X / w];

                if (bg)
                    set_bg();
                else
                    reset();
            }

            pixel();
        }

        reset();
        putchar('\n');
    }

    reset();
}

int main(int const argc, char const *const argv[const])
{
    assert(argc == 4);

    r = argv[1];
    g = argv[2];
    b = argv[3];

    struct termios save;
    tcgetattr(STDIN_FILENO, &save);

    struct termios t = save;
    t.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    set_cursor(1000, 1000);
    printf("\e[6n");

    char position[32];
    unsigned i = 0;
    while ((position[i] = getchar()) != 'R')
        ++i;
    position[i + 1] = '\0';

    fseek(stdin, 0, SEEK_END);
    tcsetattr(STDIN_FILENO, TCSANOW, &save);

    unsigned h, w;
    sscanf(position, "\e[%d;%dR", &h, &w);
    print(h, w / 2);
}
