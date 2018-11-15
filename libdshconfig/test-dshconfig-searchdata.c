/*
 *  DSH / dancer's shell or the distributed shell
 *  Copyright (C) 2002 Junichi Uekawa
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * testsuite for dshconfig_searchdata
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "libdshconfig.h"
#include "config.h"

int
main()
{
  FILE*f = fopen (getenv("READINGSOURCE"), "r");
  dshconfig * t = open_dshconfig(f, ':');

  if (strcmp (dshconfig_searchdata(t, "four"), "asdgasdkjwakmdfa"))
    {
      fprintf(stderr, "search for four failed\n");
      
      exit (1);
    }
  if (dshconfig_searchdata(t, "nonexisting"))
    {
      fprintf(stderr, "expected null return failed\n");
      exit (1);
    }
  
  if (open_dshconfig(NULL, ':'))
    {
      fprintf(stderr, "expected null return failed for NULL input\n");
      exit (1);
    }

  fprintf(stdout, "Test completes\n");

  exit (0);
}

