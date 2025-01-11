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

// Receives a packet
static int dc_recv(Window win) {
    ssize_t sz = recv(win->sock, win->buffer, DC_SOCK_BUFFER_SIZE, 0);
    win->used_buf = sz;
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

// Receives response from server and decodes it in a Response struct
// Returns -1 on failure
int dc_receive_response(Window win, Response *resp) {
    if (dc_recv(win) < 0) return -1;
    
    win->buffer[win->used_buf - 2] = 0;
    char *typ = win->buffer;
    char *arg = strchr(win->buffer, ' ') + 1;
    if (arg) arg[-1] = 0;

    if (strcmp(typ, "OK") == 0)
        resp->type = DC_RESP_OK;
    else if (strcmp(typ, "ERR") == 0) {
        resp->type = DC_RESP_ERR;
        strcpy(resp->error, arg);
    } else {
        resp->type = DC_RESP_UNKNOWN_COMMAND;
    }

    return 0;
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

// Text
void dc_write_text(Window win, const char *str, double x, double y) {
    dc_sprintf(win, "TEXT %lf %lf %s\r\n", x, y, str);
}
