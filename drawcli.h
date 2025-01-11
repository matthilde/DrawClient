#ifndef __DC_DRAWCLI_H
#define __DC_DRAWCLI_H

//// Data structures

#define DC_SOCK_BUFFER_SIZE 2048

typedef struct dc_window {
    int sock, used_buf;
    char buffer[DC_SOCK_BUFFER_SIZE];
} *Window;

typedef struct dc_color {
    unsigned char r, g, b;
} Color;

//// Functions
Window dc_create_window(const char *addr, const int port);
void   dc_destroy_window(Window win);

void dc_clear(Window win);
void dc_set_color(Window win, int r, int g, int b);
void dc_update(Window win);
void dc_draw_rectangle(Window win, double x1, double y1, double x2, double y2);
void dc_draw_line(Window win, double x1, double y1, double x2, double y2);
void dc_set_viewport(Window win, double x1, double y1, double x2, double y2);
void dc_draw_oval(Window win, double x1, double y1, double x2, double y2);

#endif