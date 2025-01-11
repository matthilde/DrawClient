#include <arpa/inet.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "drawcli.h"

// Connects to server
static int dc_connect_socket(const char *addr, const int port) {
    struct sockaddr_in address;
    int sock;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1;

    address.sin_family = AF_INET;
    address.sin_port   = htons(port);

    if (inet_pton(AF_INET, addr, &address.sin_addr) <= 0)
        return -1;
    if (connect(sock, (struct sockaddr*)&address,
                sizeof(address)) == -1)
        return -1;

    return sock;
}

// Sends a packet
static int dc_send(Window win) {
    ssize_t sz = send(win->sock, win->buffer, win->used_buf, 0);
    return sz < 0 ? -1 : 0;
}

// Do some formatting then fills the buffer and send the packet
static void dc_sprintf(Window win, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    win->used_buf = vsprintf(win->buffer, fmt, args);
    va_end(args);

    dc_send(win);
}

// Creates a new window on a DrawServ server
Window dc_create_window(const char *addr, const int port) {
    Window win = (Window)malloc(sizeof(struct dc_window));
    if (!win) return NULL; // errno
    
    int s = dc_connect_socket(addr, port);
    if (s < 0) {
        free(win);
        return NULL;
    }
    win->sock = s;
    win->used_buf = 0;

    return win;
}

// Disconnects and destroys window on a DrawServ server
void dc_destroy_window(Window win) {
    close(win->sock);
    free(win);
}

// Clears screen
void dc_clear(Window win) {
    dc_sprintf(win, "CLEAR\r\n");
}

// Sets color
void dc_set_color(Window win, int r, int g, int b) {
    dc_sprintf(win, "COLOR %d %d %d\r\n", r, g, b);
}

// Updates screen
void dc_update(Window win) {
    dc_sprintf(win, "UPDATE\r\n");
}

// Rectangle
void dc_draw_rectangle(Window win, double x1, double y1, double x2, double y2) {
    dc_sprintf(win, "RECTANGLE %lf %lf %lf %lf\r\n", x1, y1, x2, y2);
}

// Line
void dc_draw_line(Window win, double x1, double y1, double x2, double y2) {
    dc_sprintf(win, "LINE %lf %lf %lf %lf\r\n", x1, y1, x2, y2);
}

// Viewport
void dc_set_viewport(Window win, double x1, double y1, double x2, double y2) {
    dc_sprintf(win, "VIEWPORT %lf %lf %lf %lf\r\n", x1, y1, x2, y2);
}

// Ellipse
void dc_draw_oval(Window win, double x1, double y1, double x2, double y2) {
    dc_sprintf(win, "ELLIPSE %lf %lf %lf %lf\r\n", x1, y1, x2, y2);
}
