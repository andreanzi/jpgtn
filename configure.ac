# configure.in -- Process this file with autoconf to produce configure
#
# Copyright (C) 2002-2012 Jeremy Madea
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.


AC_INIT(jpgtn, 2.07, jpgtn@madea.net)
AC_CONFIG_SRCDIR(src/jpgtn.c)
# Configure the auxillary dir before init'ing automake otherwise automake can't
# find install.sh. 
AC_CONFIG_AUX_DIR(cfg)

AM_INIT_AUTOMAKE
AM_CONFIG_HEADER(src/config.h:src/config-h.in)

AC_PROG_CC

AC_HEADER_STDC
AC_CHECK_HEADERS(getopt.h errno.h strings.h unistd.h setjmp.h)

AC_C_CONST

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_STAT
AC_CHECK_FUNCS([calloc strdup strrchr rindex])
JPGTN_FIND_LIBJPEG
AC_SUBST(ac_aux_dir)

AC_OUTPUT([Makefile src/Makefile doc/Makefile test/Makefile src/replace/Makefile],
[test -z "$CONFIG_HEADERS" || echo timestamp > src/stamp-h.in])
