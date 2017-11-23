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

unsigned char *resizepic(unsigned char *image, 
                         unsigned char *palr,
                         unsigned char *palg, 
                         unsigned char *palb,
                         int currwidth, int currheight,
                         int maxsize,
                         int resize_dim)
{
    register int   a, b, x, yp, yw;
             long  y, sw, sh, lastyp;
             int   c, pixwide, pixhigh;
    unsigned char *rline;
             int   tmp, tr, tg, tb, tn;
             int   xypos;

    if (!resize_dim) {    /* The resize dimension wasn't provided... */
        if (currwidth <= currheight) { /* Picture is square or portraity */
            resize_dim = RSZ_HEIGHT;

        } else {                       /* Picture is landscapey */
            resize_dim = RSZ_WIDTH;
        }
    }

        switch(resize_dim) {
            case RSZ_HEIGHT:
                sh = maxsize;
                sw = (int)( (maxsize * ((double)currwidth)) / 
                                       ((double)currheight) );
                break;
            case RSZ_WIDTH:
                sw = maxsize;
                sh = (int)( (maxsize * ((double)currheight)) / 
                                       ((double)currwidth) );
                break;
            default:
                /* WE SHOULD NEVER GET HERE! */
                sw = sh = 0;
                break;
        }
    
    /* This is a kludge. */
    if (sw == 0) sw += 1;
    if (sh == 0) sh += 1;

    out_wide = sw; 
    out_high = sh;
    
    /* Reserve the amount of memory we will need. */
    rline = calloc(1, sw * sh * 3);
    if (rline == NULL) {
        return NULL;
    }

    for (x=0; x < (sw*sh*3); x++) {
        rline[x] = GRAY;
    }

    if (currwidth > sw) {  /* It has been reduced. */
        lastyp  = -1;
        pixhigh = (int)( ((float)currheight) / ((float)sh) + 0.5 );
        pixwide = (int)( ((float)currwidth)  / ((float)sw) + 0.5 );
        pixhigh++;
        pixwide++;
        for(y=0; y < currheight; y++) {
            yp = (y * sh) / currheight;
            if (yp != lastyp) {
                yw = (y * currwidth);

                /* we try to resample a bit. get that pentium RSN :) */
                for (x=0; x < currwidth; x++,yw++) {
                    tr = 0;
                        tg = 0;
                        tb = 0;
                        tn = 0;
                    for (b=0; (b < pixhigh) && (y+b < currheight); b++) {
                        for (a=0; (a < pixwide) && (x+a < currwidth); a++) {
                            tmp = *(image+yw+a+b*currwidth);
                            tr  += palr[tmp];
                            tg  += palg[tmp];
                            tb  += palb[tmp];
                            tn++;
                        }
                    }

                    xypos = 3*(((x*sw)/currwidth)+yp*sw);
                    tr /= tn; 
                    tg /= tn;
                    tb /= tn;
                    rline[xypos]   = tr;
                    rline[xypos+1] = tg;
                    rline[xypos+2] = tb;
                }
                lastyp = yp;
            }
        }
    } else {     /* we just leave it the same size */

        out_wide = currwidth; 
        out_high = currheight; 
        for (y=0; y < currheight; y++) {
            for (x=0; x < currwidth; x++) {
                c = image[y*currwidth+x];
                rline[3*(y*currwidth+x)]   = palr[c];
                rline[3*(y*currwidth+x)+1] = palg[c];
                rline[3*(y*currwidth+x)+2] = palb[c];
            }
        }
    }

    return rline;
}
