#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "body.h"
#include "draw.h"
#include "simu.h"

#include "paint.h"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (600)

int main (int argc, char *argv[])
{
  struct body_list_t *bodies = NULL ;
  int go_on = true ;
  
  unsigned char* window=create_pixels(SCREEN_WIDTH,SCREEN_HEIGHT);

  /* Create the bodies. */
  bodies = new_body (bodies, 0xFF0000, 5, 10.0, 0.0, 100.0, 20.0, 20.0) ;
  bodies = new_body (bodies, 0x00FF00, 10, 1.0, 0.0, 0.0, 15.0, 15.0) ;
  bodies = new_body (bodies, 0x0000FF, 8, 5.0, 0.0, 0.0, 15.0, 15.0) ;

int i=0;
  for (i=0;i<1000;i++) {

    /* Compute one step of simulation. */
    simulate_bodies (bodies, forces_array) ;

    /* Render the bodies at their new position. */
    draw_bodies (false, bodies,window) ;

   }

  save_BMP("dessin.bmp", SCREEN_WIDTH,SCREEN_HEIGHT,window);
  
  return (0) ;
}
