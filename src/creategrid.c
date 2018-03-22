#if HAVE_CONFIG_H
#    include <config.h>
#endif

#include "common.h"
#include "jpgtn.h"



/* Private */
static unsigned char *getRawImageLine( node *, int, int, int, int);

/**
 * @brief This create the complete grid image
 * 
 * @param head head of the list of thumbnails
 * @param xsize grid width in pixels
 * @param ysize grid height in pixels
 * @param rows number of rows of the grid
 * @param columns number of columns of the grid
 * @param TW thumbnail width in pixels
 * @param TH thumbnail height in pixels
 * @return the raw bytecode of image
 */

unsigned char *creategrid(node *head, int xsize, int ysize, int rows, int columns, int TW, int TH){
    unsigned char *grid = calloc(1, xsize * ysize * 3);

    if( grid == NULL){
        printf("cannot allocate memory\n");
        return NULL;
    }


    int r = 0;
    for( int h = 0; h < ysize; h++){
        for( int c = 0; c < columns; c++){
            // image in position (r ; c)
            unsigned char *temp_raw = getRawImageLine(head, r * columns + c, TW, TH, h);
            memcpy(&grid[ r * xsize * TH * 3 + h* xsize * 3 + c*TW * 3],temp_raw, TW * 3 );
        }
        if( h == TH - 1 ){
            h = -1;
            r++;
            if( r == rows ){
                break;
            }
        }
    }

    return grid;
}

/**
 * @brief This returns the bytecode of the row-th row of the n-th image in list
 * 
 * @param head head of the list of thumbnails
 * @param n index of the thumb inside the list
 * @param TW width of thumbnails in pixels
 * @param TH height of thumbnails in pixels
 * @param row row index of which return the bytecode
 * @return bytecode of the row-th row of n-th image in list
 */

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
