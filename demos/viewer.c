// Test program, connects a localhost:9090
#include <stdio.h>
#include "../drawcli.h"

#define MIN(x,y) ((x) > (y) ? (y) : (x))
#define MAX(x,y) ((x) < (y) ? (y) : (x))
#define MINL(x1,y1,x2,y2) MIN(MIN(x1,y1),MIN(x2,y2))
#define MAXL(x1,y1,x2,y2) MAX(MAX(x1,y1),MAX(x2,y2))

void adjust_viewport(Window win, FILE *f) {
    float min_lower = -1.0, max_higher = 1.0;
    float x1, y1, x2, y2;
    int length;

    fscanf(f, "%d", &length);

    for (int i = 0; i < length; ++i) {
        fscanf(f, "%*d ( %f, %f) ( %f, %f)", &x1, &y1, &x2, &y2);
        
        min_lower =  MIN(MINL(x1,y1,x2,y2), min_lower);
        max_higher = MAX(MAXL(x1,y1,x2,y2), max_higher);
    }

    printf("Viewport: %f %f\n", min_lower, max_higher);

    min_lower -= 0.5; max_higher += 0.5;
    dc_set_viewport(win, min_lower, min_lower, max_higher, max_higher);
}

void read_and_draw_lines(Window win, FILE *f) {
    float x1, y1, x2, y2;
    int length;

    fscanf(f, "%d", &length);

    for (int i = 0; i < length; ++i) {
        fscanf(f, "%*d ( %f, %f) ( %f, %f)", &x1, &y1, &x2, &y2);
        dc_draw_line(win, x1, y1, x2, y2);
    }
}

int main(int argc, const char **argv) {
    Window win = dc_create_window("127.0.0.1", 9090);
    if (!win) return 1;
    
    dc_clear(win);

    dc_set_color(win, 255, 0, 0);
    
    char msg[256];
    sprintf(msg, "Fichier: %s\n", argv[1]);
    dc_set_color(win, 255, 0, 255);
    dc_write_text(win, msg, -0.96, -0.64);

    dc_update(win);

    dc_set_color(win, 0, 0, 0);
    dc_set_viewport(win, -7.0, -7.0, 7.0, 7.0);

    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;

    adjust_viewport(win, f);
    rewind(f);
    read_and_draw_lines(win, f);

    dc_update(win);

    puts("Press any key to end program..."); getchar();
    dc_destroy_window(win);

    return 0;
}
