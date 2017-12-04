#if HAVE_CONFIG_H
#    include <config.h>
#endif

#include "common.h"
#include "jpgtn.h"

/* Private */
static unsigned char *getRawImageLine( node *, int, int, int, int);


unsigned char *creategrid(node *head, int xsize, int ysize, int rows, int columns, int TW, int TH){
    unsigned char *grid = (unsigned char*) calloc(1, xsize*ysize*3);
    //memcpy(grid, head->raw_image, head->width * head->height * 3);
    //memcpy(&grid[head->width * head->height * 3], head->next->raw_image, head->next->width * head->next->height * 3);
    int r = 0;
    for( int h = 0; h < ysize; h++){
        for( int c = 0; c < columns; c++){
            // image in position (r ; c)
            unsigned char *temp_raw = getRawImageLine(head, r * columns + c, TW, TH, h % TH);
            memcpy(&grid[ r * xsize * TH * 3 + h* xsize * 3 + c*TW * 3],temp_raw, TW * 3 );
        }
        if( h == TH - 1){
            h = 0;
            r++;
            if( r == columns ){
                break;
            }
        }
    }
    // memcpy(grid, head->raw_image, xsize*ysize*3);

    // for (int y = 0; y < ysize; y++) {
    //   // For grid 1 x 2 (non funziona)
    //   memcpy(&grid[xsize * y], &head->raw_image[y*xsize], head->width);
    //   memcpy(&grid[(xsize * y + xsize/2)], &head->next->raw_image[y*xsize], head->next->width);
    // }

    return grid;
}

static unsigned char *getRawImageLine( node *head, int n, int TW, int TH, int row){
    int c = 0;
    unsigned char *line = (unsigned char*) calloc(1, TW * 3);
    for( node *i = head; i != NULL; i = i->next) {
        if( c == n ){
            memcpy(line, &i->raw_image[row * TW * 3 ], TW*3);
            return line;
        }
        c++;
    }
    return 0;
}
