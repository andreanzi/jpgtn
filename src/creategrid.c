#if HAVE_CONFIG_H
#    include <config.h>
#endif

#include "common.h"
#include "jpgtn.h"

unsigned char *creategrid(node *head, int xsize, int ysize, int xelements, int yelements){
    unsigned char *grid = (unsigned char*) calloc(1, xsize*ysize*3);

    // memcpy(grid, head->raw_image, xsize*ysize*3);

    for (int y = 0; y < ysize; y++) {
      // For grid 1 x 2 (non funziona)
      memcpy(&grid[xsize * y], &head->raw_image[y*xsize], head->width);
      memcpy(&grid[(xsize * y + xsize/2)], &head->next->raw_image[y*xsize], head->next->width);
    }

    return grid;
}
