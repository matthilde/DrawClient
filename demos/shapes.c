#include <stdio.h>
#include "../drawcli.h"

void pause() {
    puts("Press enter to leave...");
    while (getchar() != '\n');
}

int main() {
    puts("Shapes demo");

    // Cree une fenetre de dessin
    Window win = dc_create_window("127.0.0.1", 9090);
    
    // Ajuste la zone de dessin
    dc_set_viewport(win, -4.0, -3.0, 4.0, 3.0);

    // Dessine quelques rectangles
    dc_set_color(win, 130, 20, 130);
    dc_draw_rectangle(win, -2.5, -2.5, -0.7, 0.7);
    
    dc_set_color(win, 0, 128, 0);
    dc_draw_rectangle(win, -1.5, -1.3, 1.0, 1.5);

    // Dessine des cercles et des ovales
    dc_set_color(win, 0, 255, 255);
    dc_draw_oval(win, -1.0, -1.0, 1.0, 1.0);

    dc_set_color(win, 0, 0, 0);
    dc_draw_oval(win, -1.0, 2.0, 3.0, 2.5);

    // Met a jour la fenetre
    dc_update(win);

    pause();

    return 0;
}
