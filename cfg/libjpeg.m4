## libjpeg.m4 -- provide and handle --with-libjpeg=PATH configure option
## Copyright (C) 2000-2012 Jeremy Madea
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2, or (at your option)
## any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

AC_DEFUN([JPGTN_FIND_LIBJPEG],
[AC_ARG_WITH(libjpeg,
             AC_HELP_STRING([--with-libjpeg=PATH],
                            [Specify the location of libjpeg]),
[
if test x"${with_libjpeg}" = xno; then
  AC_MSG_ERROR([sorry, cannot build without libjpeg.])
else
  AC_MSG_NOTICE(checking for libjpeg...)
  if test x"${with_libjpeg}" = xyes; then
    AC_CHECK_LIB(jpeg, jpeg_read_header,,AC_MSG_ERROR([cannot find libjpeg.]))
  else 
    AC_EXPAND_PATH($with_libjpeg, JPG_DIR)
    test -f $JPG_DIR/jpeglib.h              && LJPEG_INC=$JPG_DIR
    test -f $JPG_DIR/include/jpeglib.h      && LJPEG_INC=$JPG_DIR/include
    test -f $JPG_DIR/include/jpeg/jpeglib.h && LJPEG_INC=$JPG_DIR/include/jpeg
    test -f $JPG_DIR/libjpeg.a              && LJPEG_LIB=$JPG_DIR
    test -f $JPG_DIR/lib/libjpeg.a          && LJPEG_LIB=$JPG_DIR/lib
    test -f $JPG_DIR/lib/jpeg/libjpeg.a     && LJPEG_LIB=$JPG_DIR/lib/jpeg
    LDFLAGS="-L$LJPEG_LIB $LDFLAGS"
    CPPFLAGS="-I$LJPEG_INC $CPPFLAGS"
    AC_CHECK_LIB(jpeg, jpeg_read_header,,AC_MSG_ERROR([cannot find libjpeg.]))
  fi
fi
],AC_CHECK_LIB(jpeg, jpeg_read_header,,AC_MSG_ERROR([cannot find libjpeg.])))
])
