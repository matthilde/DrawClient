#include <stdlib.h>
#include <math.h>

#include "drawcli.h"

#define PI 3.14159265358979323846

#define RAD(deg) ((deg) * (PI / 180.0))

// Create a new turtle
Turtle dc_create_turtle(Window win, double x, double y) {
    Turtle turtle = (Turtle)malloc(sizeof(struct dc_turtle));

    turtle->win = win;
    turtle->x = x; turtle->y = y;
    turtle->angle = 0.0;
    turtle->pen = 0; // Pen up

    return turtle;
}

// Frees a turtle
void dc_free_turtle(Turtle tur) {
    free(tur);
}

// Calculates the next position of the turtle
// xy is a 2-sized array, the function will modify these values
static void dc_tur_get_new_position(Turtle tur, double xy[2], double step) {
    double dx = cos(RAD(tur->angle)), dy = -sin(RAD(tur->angle));

    xy[0] = tur->x + dx * step;
    xy[1] = tur->y + dy * step;
}

// Sets the pen up
void dc_tur_penup(Turtle tur) {
    tur->pen = 0;
}

// Sets the pen down
void dc_tur_pendown(Turtle tur) {
    tur->pen = 1;
}

// Move the turtle at an arbitrary position.
// It will draw a line from the old position to the new one if the pen is down.
void dc_tur_movexy(Turtle tur, double x, double y) {
    if (tur->pen)
        dc_draw_line(tur->win, tur->x, tur->y, x, y);

    tur->x = x; tur->y = y;
}

// Go forward, one can use a negative value to go backward
void dc_tur_forward(Turtle tur, double step) {
    double newpos[2];

    dc_tur_get_new_position(tur, newpos, step);
    dc_tur_movexy(tur, newpos[0], newpos[1]);
}

// Turn around. Positive value will turn right, Negative value will turn left.
// Angle is in degrees
void dc_tur_turn(Turtle tur, double angle) {
    tur->angle -= angle;
}
