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

#ifndef JPGTN_H
#define JPGTN_H 1

#define MAXSIZE     2048                    /* Maximum size of thumbnail   */
#define MINSIZE     1                       /* Minimum size of thumbnail   */
#define DEFAULTSIZE 128                     /* Default size of thumbnail   */

#define GRAY 128

#define RSZ_AUTO   0
#define RSZ_WIDTH  1
#define RSZ_HEIGHT 2

unsigned char *outimage;                    /* The current thumbnail image */
unsigned char *palette;                     /* Global palette pointer      */
int            width;                       /* Original image width        */
int            height;                      /* Original image height       */
int            background;                  /* Index's background color    */
long           out_wide;                    /* Width of thumbnail image    */
long           out_high;                    /* Height of thumbnail image   */


/* resizepic.c */
extern unsigned char *resizepic(unsigned char *thisimage, 
                                unsigned char *palr,
                                unsigned char *palg, 
                                unsigned char *palb,
                                int            currwidth, 
                                int            currheight,
                                int            maxsize,
                                int            which_dim);

/* readjpeg.c */
extern unsigned char *read_JPEG_file(char *filename, unsigned char **palette);

/* writejpeg.c  */
extern void write_JPEG_file(char *filename, 
                            int   outwidth,  
                            int   outheight, 
                            int   quality);

#endif /* !JPGTN_H */
