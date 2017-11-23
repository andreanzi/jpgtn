## Makefile.am -- Process this file with automake to produce Makefile.in
## Copyright (C) 2002-2012 Jeremy Madea
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

auxdir			= @ac_aux_dir@
AUX_DIST		= $(auxdir)/install-sh $(auxdir)/missing \
			$(auxdir)/mkinstalldirs
EXTRA_DIST		= bootstrap

AUTOMAKE_OPTIONS 	= foreign
SUBDIRS 		= src doc test
MAINTAINERCLEANFILES 	= Makefile.in aclocal.m4 configure src/config-h.in \
			src/stamp-h.in $(AUX_DIST)

ACLOCAL			= aclocal -I $(auxdir)
CPPFLAGS		= @CPPFLAGS@
