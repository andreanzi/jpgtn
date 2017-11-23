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


/* Private */
static void print_version(void);
static void print_usage(char *);
static int  file_exists(const char *);
static char *output_file_name(const char *,int,const char *,int,const char *);

int main(int argc, char **argv)
{
    int f;                                 /* Current file to be indexed  */
    int xsiz = 0;                          /* Total output image xsize    */
    int ysiz = 0;                          /* Total output image ysize    */
    unsigned char *bigimage   = NULL;      /* Pointer to current image    */
    unsigned char *palrgb     = NULL;      /* Pointer to image palette    */
    int x=0;
    int  size = DEFAULTSIZE;               /* Size of thumbnail image.    */
    int  opt_size;
    int  opt_flag_quality   = 0;
    int  opt_flag_prefix    = 0;
    int  opt_flag_directory = 0;
    int  opt_flag_stdout    = 0;
    int  opt_flag_force     = 0;
    int  opt_flag_verbose   = 0;
    int  opt_quality;                      /* JPEG Quality                */
    int  opt_rsz_dim = RSZ_AUTO;           /* Dimension to resize. 0,1,2  */
    char *opt_directory = NULL;            /* Output directory            */
    char *opt_prefix    = NULL;            /* Output filename prefix      */
    char *imgfile       = NULL;            /* Output filename             */


    /* Check command args */
    if (argc < 2) {
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    while (-1 != (x = getopt(argc,argv,"Vh?SHWfvs:q:d:p:"))) {
        switch(x) {
            case 'V':
                print_version();
                exit(EXIT_FAILURE);
                break;
            case 'h':
                print_usage(argv[0]);
                exit(EXIT_FAILURE);
                break;
            case 'q':
                sscanf(optarg,"%d",&opt_quality);
                if(opt_quality < 1 || opt_quality > 100) {
                    opt_quality = 70;
                }
                opt_flag_quality = 1;
                break;
            case 's':
                sscanf(optarg,"%d",&opt_size);
                if ((opt_size < MINSIZE) || (opt_size > MAXSIZE)) {
                    opt_size = DEFAULTSIZE;
                }
                size = opt_size;
                break;
            case 'f':
                opt_flag_force = 1;
                break;
            case 'v':
                opt_flag_verbose++;
                break;
            case 'S':
                opt_flag_stdout = 1;
                break;
            case 'H':
                opt_rsz_dim = RSZ_HEIGHT;
                break;
            case 'W':
                opt_rsz_dim = RSZ_WIDTH;
                break;
            case 'd':
                opt_directory = optarg;
                opt_flag_directory = 1;
                break;
            case 'p':
                opt_prefix = optarg;
                opt_flag_prefix = 1;
                break;
            case '?':
                print_usage(argv[0]);
                exit(EXIT_FAILURE);
                break;
            default:
                fprintf(stderr,"Unknown error. Exiting.\n");
                exit(EXIT_FAILURE);
                break;
            }
        }

    if (argc - optind < 1) {
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((!opt_flag_stdout) && (!opt_flag_directory) && (!opt_flag_prefix)) {
        opt_flag_prefix = 1;
        opt_prefix = "tn_";
    }
            
    if (!opt_flag_quality) opt_quality = 70;

    if (opt_flag_verbose > 2) {
        printf("quality: %d\n",opt_quality);
    }


    /* The big loop */
    for (f = optind; f < argc; f++) {

        if (!opt_flag_stdout) { 
            imgfile = output_file_name(argv[f],
                                       opt_flag_directory, opt_directory,
                                       opt_flag_prefix, opt_prefix);
            if (imgfile != NULL) {
                if (!opt_flag_force && file_exists(imgfile)) { 
                    fprintf(stderr,"Skipping %s: File exists\n", imgfile); 
                    continue;
                } 
            } else { 
                fprintf(stderr, "Could not allocate space for filename!\n"); 
                exit(EXIT_FAILURE); 
            }
        }

        /* Get a pointer to the big image or NULL on error */
        bigimage=read_JPEG_file(argv[f], &palette);
        if (NULL == bigimage) {
            fprintf(stderr, "read_JPEG_file: Error\n");
            if(outimage) free(outimage);
            exit(EXIT_FAILURE);
        }
        palrgb=palette;

        /* Returns a pointer to the resized image or NULL on error */
        outimage = resizepic(bigimage, palrgb, palrgb+256, palrgb+512,
                             width, height, size, opt_rsz_dim);
        xsiz = out_wide;
        ysiz = out_high;

        if(outimage == NULL) {
            fprintf(stderr,"outimage = NULL ???\n");
            if(bigimage) free(bigimage);
            exit(EXIT_FAILURE);
        }

        if ((xsiz < MINSIZE) && (ysiz < MINSIZE)) {
             fprintf(stderr, "thumbnail too small...\n");
        }
    
        free(palrgb);
        free(bigimage);
        
        if (! opt_flag_stdout) { 
            if (opt_flag_verbose) { 
                printf("%s",imgfile);
                if (opt_flag_verbose > 1) printf(" %dx%d",xsiz,ysiz);
                printf("\n");
            }
            write_JPEG_file(imgfile,xsiz,ysiz,opt_quality);
            free(imgfile);
            imgfile = NULL;
            free(outimage);

        } else { 
            write_JPEG_file(NULL,xsiz,ysiz,opt_quality);
            exit(EXIT_SUCCESS);
        }
    }

    exit (EXIT_SUCCESS);
}

static int file_exists(const char *path) { 
    struct stat buf;
 
    /* Crude check. If we can stat it successfully, we assume it exists. */
    /* Otherwise we return zero, meaning that this function can't tell. */

    if (0 == stat(path, &buf)) {
        return(1);
    } else {
        return(0);
    }
}

static char *output_file_name(const char *infile, 
                              int dflag, const char *dir, 
                              int pflag, const char *pre)
{
    int   len       = 0;
    char *infiledup = NULL;
    char *ifn       = NULL;
    char *name      = NULL;

    /* Make a copy of the input file name. */
    infiledup = strdup(infile);
    if (! infiledup) { 
        return(NULL);
    }

    /* Ignore path information at the beginning of the filename. */
    ifn = strrchr(infiledup,'/');
    if (!ifn) { 
        ifn = infiledup;
    } else { 
        ifn++;
    }

    /* Estimate max length we'll need; add two for "./" and one for null. */ 
    len = strlen(ifn) + 3;               
    if (dir) len += strlen(dir);
    if (pre) len += strlen(pre);
            
    /* Reserve space for it... */
    name = (char *)malloc(len);

    if (name == NULL) { 
        return NULL; 
    } 

    *name = '\0'; 

    /* Construct the output file name. */
    if (dflag) {
       strcpy(name, dir);
       len = strlen(dir);

        /* Add "/" on dir if needed.*/
        if (dir[len - 1] != '/') {
            strcat(name,"/");
        }
    } else {
        /* strcpy(name, "./"); */
    }

    if (pflag) {
        strcat(name, pre);
        strcat(name, ifn);
    } else {
        strcat(name, ifn);
    }

    free(infiledup);
    return(name);
}

static void print_usage(char *prog)
{
    print_version();
    printf("usage: %s [switches] [inputfiles]\n",prog);
    printf("  -d directory  Set the output directory.\n");
    printf("  -f            Force overwrite of existing output files.\n");
    printf("  -h            Display this help message and exit.\n");
    printf("  -p prefix     Set the output filename prefix.\n");   
    printf("  -q quality    Set the output quality.\n");
    printf("  -s size       Set the size of the longest output dimension. ");
    printf(" (See -H and -V)\n");
    printf("  -v            Verbosity level. (May be used multiple times.)\n");
    printf("  -H            Make the -s switch refer to the output height.\n");
    printf("  -S            Process only one file and output to stdout.\n");
    printf("  -W            Make the -s switch refer to the output width.\n");
    printf("  -V            Display version and exit.\n");
    printf("\nSee jpgtn(1) for more details.\n\n");
}

static void print_version(void)
{
    printf("jpgtn : Version %s\n",VERSION);
    printf("Copyright (c) 2002-2012 Jeremy Madea <jpgtn@madea.net>\n\n");
}
