## utility.m4 -- provides useful utility macros configure option
## This file is part of jpgtn.
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

dnl
dnl AC_EXPAND_PATH(path, variable)
dnl
dnl expands path to an absolute path and assigns it to variable
dnl This was borrowed from mapserver-3.6.0's aclocal.m4 and modified slightly.
dnl
AC_DEFUN([AC_EXPAND_PATH],[
  if test -z "$1" || echo "$1" | grep '^/' >/dev/null ; then
    $2=$1
  else
    $2=`pwd`/$1
  fi
])

