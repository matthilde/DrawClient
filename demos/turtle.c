#include <stdio.h>

#include "../drawcli.h"

void pause() {
    puts("Press enter to continue...");
    while (getchar() != '\n');
}

void koch(Turtle tur, double length, int iter) {
    if (iter <= 0) {
        dc_tur_forward(tur, length);
    } else {
        iter -= 1;
        koch(tur, length, iter);
        dc_tur_turn(tur, -60);
        koch(tur, length, iter);
        dc_tur_turn(tur, 120);
        koch(tur, length, iter);
        dc_tur_turn(tur, -60);
        koch(tur, length, iter);
    }
}


// Creates cool fractals using the turtle module!
int main() {
    puts("Turtle program!");

    Window win = dc_create_window("127.0.0.1", 9090);
    Turtle tur = dc_create_turtle(win, -0.5, -0.32);

    dc_tur_pendown(tur);
    
    koch(tur, 0.012, 4);
    dc_tur_turn(tur, 120);
    koch(tur, 0.012, 4);
    dc_tur_turn(tur, 120);
    koch(tur, 0.012, 4);

    dc_update(win);

    pause();

    dc_free_turtle(tur);
    dc_destroy_window(win);

    return 0;
}
