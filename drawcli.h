#ifndef __DC_DRAWCLI_H
#define __DC_DRAWCLI_H

//// Data structures

#define DC_SOCK_BUFFER_SIZE 2048
#define DC_ERR_BUFFER_SIZE 250

typedef struct dc_window {
    int sock, used_buf;
    char buffer[DC_SOCK_BUFFER_SIZE];
} *Window;

typedef struct dc_turtle {
    Window win;
    int pen; // is pen up or down?
    double x, y, angle; // Angle is in degrees
} *Turtle;

typedef struct dc_response {
    enum {
        DC_RESP_OK,
        DC_RESP_ERR,
        DC_RESP_UNKNOWN_COMMAND
    } type;
    char error[DC_ERR_BUFFER_SIZE];
} Response;

typedef struct dc_color {
    unsigned char r, g, b;
} Color;

//// Functions

// drawcli.c
Window dc_create_window(const char *addr, const int port);
void   dc_destroy_window(Window win);

void dc_clear(Window win);
void dc_set_color(Window win, int r, int g, int b);
void dc_update(Window win);
void dc_draw_rectangle(Window win, double x1, double y1, double x2, double y2);
void dc_draw_line(Window win, double x1, double y1, double x2, double y2);
void dc_set_viewport(Window win, double x1, double y1, double x2, double y2);
void dc_draw_oval(Window win, double x1, double y1, double x2, double y2);
void dc_write_text(Window win, const char *str, double x, double y);

// turtle.c
Turtle dc_create_turtle(Window win, double x, double y);
void   dc_free_turtle(Turtle tur);
void   dc_tur_penup(Turtle tur);
void   dc_tur_pendown(Turtle tur);
void   dc_tur_movexy(Turtle tur, double x, double y);
void   dc_tur_forward(Turtle tur, double step);
void   dc_tur_turn(Turtle tur, double angle);

#endif
