#if HAVE_CONFIG_H
#    include <config.h>
#endif

#include "common.h"
#include "jpgtn.h"

/**
 * @brief This cut the image according to info passed as parameters
 * 
 * @param image bytecode of original image
 * @param currwidth width of original image in pixels
 * @param currheight height of original image in pixels
 * @param which_dim integer to define which dimension has to be cut
 * @param size dimension in pixels to be cut
 * @param not_symmetric integer to define if the cut is symmetric or not
 * @return the bytecode of the cut image
 */

unsigned char *cutimage( char* image, int currwidth, int currheight, int which_dim, int size, int not_symmetric){
    unsigned char *new_image = NULL;

    if( which_dim == RSZ_HEIGHT ){
        //cutting top and bottom edges
        if( not_symmetric == 0 ) {
            // symmetric cut
            new_image = (unsigned char*) calloc(1, currwidth*(currheight - (size * 2)) * 3);
            memcpy( new_image, &image[size * currwidth * 3 ], currwidth*(currheight - (size*2)) * 3);
        } else {
            // cut 1px more from the bottom edge
            new_image = (unsigned char*) calloc(1, currwidth*(currheight - (size * 2) - 1 ) * 3);
            memcpy( new_image, &image[size * currwidth * 3 ], currwidth*(currheight - (size*2) - 1) * 3);
        }

    } else {
        if(  not_symmetric == 0 ){
            // symmetric cut
            new_image = (unsigned char*) calloc(1, currheight*(currwidth - (size*2)) * 3);
            int new_width = currwidth - size * 2;
            for( int i = 0; i < currheight; i++ ) {
                memcpy(&new_image[new_width * i * 3], &image[currwidth*i*3 + size*3], new_width * 3);
            }
        } else {
            new_image = (unsigned char*) calloc(1, currheight*(currwidth - (size*2) - 1) * 3);
            int new_width = currwidth - size * 2 - 1;
            for( int i = 0; i < currheight; i++ ) {
                memcpy(&new_image[new_width * i * 3], &image[currwidth*i*3 + size*3], new_width * 3);
            }
        }

    }

    return new_image;
}
