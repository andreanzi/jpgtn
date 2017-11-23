/*
    Copyright (C) 2002-2012 Jeremy Madea <jpgtn@madea.net>

    This file is part of jpgtn.

    Jpgtn is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    Jpgtn is based on two programs: tnpic (distributed with zgv) and gtnpic.
    The original "gtnpic" program was Copyright (C) 1997      Willie Daniel. 
    The original "tnpic"  program was Copyright (C) 1993-1996 Russell Marks.
    Both tnpic and gtnpic were distributed under the GNU Public License. 
*/
#if HAVE_CONFIG_H
#    include <config.h>
#endif 

#include "common.h"
#include "jpgtn.h"

/* write_JPEG_file -- Writes the global image "outimage" to a file. */

void write_JPEG_file(char *filename, int outwidth, int outheight, int quality)
{
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr       jerr;
    FILE     *out;
    JSAMPROW row_pointer[1];    /* pointer to JSAMPLE row[s]          */
    int      row_stride;        /* physical row width in image buffer */

    /* Step 1: Allocate and initialize JPEG compression object. */

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    /* Step 2: Specify data destination. */

        if (filename) {
            out = fopen(filename,"wb");
            if (out == NULL) {
                fprintf(stderr,"can't open %s\n",filename);
                exit(1);
            }
        } else {
            out = stdout;
        }
    jpeg_stdio_dest(&cinfo,out);

    /* Step 3: set parameters for compression */

    cinfo.image_width      = outwidth;  /* image width and height, in pix */
    cinfo.image_height     = outheight;
    cinfo.input_components = 3;         /* # of color components per pix  */
    cinfo.in_color_space   = JCS_RGB;   /* colorspace of input image      */

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo,quality,FALSE);

    /* Step 4: Start compressor */

    jpeg_start_compress(&cinfo,TRUE);

    /* Step 5: while (scan lines remain to be written) */

    row_stride = outwidth * 3;    /* JSAMPLEs per row in image_buffer */

    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = &outimage[cinfo.next_scanline*row_stride];
        jpeg_write_scanlines(&cinfo,row_pointer,1);
    }

    /* Step 6: Finish compression */

    jpeg_finish_compress(&cinfo);
    fclose(out);

    /* Step 7: release JPEG compression object */

    jpeg_destroy_compress(&cinfo);

}
