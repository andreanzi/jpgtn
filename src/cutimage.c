#if HAVE_CONFIG_H
#    include <config.h>
#endif

#include "common.h"
#include "jpgtn.h"

unsigned char *cutimage( char* image, int currwidth, int currheight, int which_dim, int size){
    unsigned char *new_image = NULL;

    if( which_dim == RSZ_HEIGHT ){
        //cutting top and bottom edges
        new_image = (unsigned char*) calloc(1, currwidth*(currheight - (size*2)));
        memcpy( new_image, &image[size * currwidth ], currwidth*(currheight - (size*2)));
    } else {
        new_image = (unsigned char*) calloc(1, currheight*(currwidth - (size*2)));
        int new_width = width - size * 2;
        for( int i = 0; i < currheight; i++ ) {
            memcpy(&new_image[new_width * i], &image[currwidth*i + size], new_width);
        }
    }

    return new_image;
}
