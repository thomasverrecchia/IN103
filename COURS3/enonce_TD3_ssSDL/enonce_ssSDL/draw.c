#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "body.h"
#include "draw.h"
#include "paint.h"

#define recenter_x(x) ((SCREEN_WIDTH / 2) + (x))
#define recenter_y(y) ((SCREEN_HEIGHT / 2) - (y))

/** Draw or clear all the bodies. If [clear] is false then bodies are drawn
    with their color, otherwise they are dranw black, i.e. erased from the
    screen. */
void draw_bodies (bool clear, struct body_list_t *bl,unsigned char* window)
{
  while (bl != NULL) {
    /* Pre-initialize the color with 0 in case of clearing the screen. */
    int red = 0, green = 0, blue = 0 ;
    int x, y ;
    struct body_t *b = bl->body ;

    /* If we must draw, then use the bodie's color. */
    if (! clear) {
      red = (b->color & 0xFF0000) >> 16 ;
      green = (b->color & 0xFF00) >> 8 ;
      blue = b->color & 0xFF ;
    }

    /* Recenter and clip the on-screen coordinates. If any is outside the
       screen, do not draw anything. */
    x = recenter_x (b->x) ;
    if ((x >= 0 + b->radius) && (x < SCREEN_WIDTH - b->radius)) {
      y = recenter_y (b->y) ;
      if ((y >= 0 + b->radius) && (y < SCREEN_HEIGHT - b->radius)) {
        //renderCircle (x, y, b->radius, red, green, blue) ;
        color_pixel(x,y,red,green,blue, SCREEN_WIDTH, SCREEN_HEIGHT,window);
      }
    }

    bl = bl->next ;
  }
}
