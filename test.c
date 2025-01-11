// Test program, connects a localhost:9090
#include <stdio.h>
#include "drawcli.h"

int main() {
    Window win = dc_create_window("127.0.0.1", 9090);
    if (!win) return 1;
    
    dc_clear(win);
    dc_set_color(win, 255, 128, 128);
    dc_draw_rectangle(win, -1.0, -1.0, 1.0, 1.0);

    dc_set_color(win, 0, 0, 0);
    
    for (double i = -1.0; i <= 1.01; i += 0.1) {
        dc_draw_line(win, -1.0, i, -i, -1.0);
        dc_draw_line(win, 1.0, -i, i, 1.0);
    }

    dc_set_color(win, 255, 0, 255);
    dc_draw_line(win, -0.8, -0.5, 0.5, 0.1);

    dc_update(win);

    puts("Press any key to end program..."); getchar();
    dc_destroy_window(win);

    return 0;
}
