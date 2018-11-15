/*
 *  DSH / dancer's shell or the distributed shell
 *  Copyright (C) 2001-2004 Junichi Uekawa
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
 * A library to read dsh config file style data files.
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "libdshconfig.h"
#include "config.h"

/* declaration for a local function required by autoconf */
static void * rpl_malloc (size_t n);

/* local function defining "getline" */
#ifndef HAVE_GETLINE
/* an imcomplete, and wrong implementation of getline */
static ssize_t getline (char **LINEPTR, size_t *N, FILE *STREAM)
{
  const int GETLINESIZE = 256;
  
  if (!*LINEPTR)
    *LINEPTR= malloc (GETLINESIZE);
  if (*N != GETLINESIZE)
    *LINEPTR = realloc (*LINEPTR, GETLINESIZE);
  if (!*LINEPTR)
    {
      return -1;
    }
  if (!fgets (*LINEPTR, GETLINESIZE - 1, STREAM))
    return -1;
  
  *N = strlen (*LINEPTR);
  return GETLINESIZE;
  
}
#endif

/**
   Function to search member
 */
const char * 
dshconfig_searchdata (const dshconfig * d, const char * index )
{
  dshconfig_internal * i = d->config;
  for (; i; i = i -> next )
    {
      if (! strcmp (i->title, index ))
	return i->data;
    }  
  return NULL;
}

/**
   The function used to split a line

   @return NULL on failure.
 */
dshconfig_internal *
dshconfig_splitline(const char * original, char delimiter)
{
  char * s = strdup (original);
  dshconfig_internal * d = malloc (sizeof (dshconfig_internal));
  char * pos, * i;
  
  if (!d)
    return NULL;
  if (!s)
    {
      fprintf(stderr, "Failed to malloc in dshconfig_internal");
      return NULL;
    }
  
  d->next =NULL;
  
  if ((pos = strchr(s, delimiter)) == NULL)	/* if the line has no delimiter, it is an error */
    {
      return NULL;
    }
  *(pos++) = 0; 		/* terminate the string, and pos points to start of "data" */
  
  /* removing the space at end of title */
  for (i = pos - 2; i > s; --i)
    {
      if (!isspace (*i))
	break;
      else
	*i = 0;
    }
  
  /* removing the space in the beginning in title */
  for (i = s; i < pos; ++i)
    if (!isspace (*i))
      break;
  d->title=strdup(i);
  
  /* removing the space at the end of data*/
  for (i = strlen(pos) + pos - 1; i > pos; --i)
    {
      if (!isspace (*i))
	break;
	  else
	    *i = 0;
    }
  
  /* removing space at the beginning in data */
  for (i = pos; i < pos + strlen (pos); ++i)
    {
      if (!isspace (*i))
	break;
    }
  
  d->data=strdup(i);
  
  free (s);
  return d;
}

/** 
   The ugly function to do the config file reading.
   It will read one non-commentline and return to the caller.

   Return value of NULL indicates termination and/or error.
 */
static dshconfig_internal*
read_oneline (FILE* f, int delimiter)
{
  /* read one line and return */
  dshconfig_internal * d = NULL;
  char* s = NULL;
  size_t size = 0;
  char* pos;
  
  while (getline (&s, &size, f) != -1)
    {
      if (0!=(pos = strchr(s, '#')))	/* handle comments, # and not \# */
	if ((pos == s) || (*(pos-1) != '\\'))
	  *pos = 0;
      
      if ((strchr(s, delimiter)) == NULL)	/* if the line has no delimiter, get another one */
	{
	  continue;
	}

      d = dshconfig_splitline(s, delimiter);
      if (!d)
	continue;
	
      free (s);
      return d;
    }
  
  if (s) free (s);
  return 0;
}

/** reads a dsh config file, and load it up in memory 

    @return NULL when error.
 */
dshconfig *
open_dshconfig (FILE* file, char delimiter) 
{
  dshconfig * d = malloc (sizeof (dshconfig));
  dshconfig_internal * t, * i ;
  
  if (!d)
    return NULL;
  if (!file)
    return NULL;
  
  d->config = NULL;
  
  while (0!=(t = read_oneline (file, delimiter)))
    {
      t->next = NULL;
      if (NULL != d->config)
	{
	  for (i = d->config; i -> next; i = i-> next);
	  i -> next = t;
	}
      else
	{
	  d->config = t;
	}
    }
  return d;
}

/**
   Frees up memory for dshconfig_internal.
   It is allocated by dshconfig_splitline.

   @Version soname 1 adds this feature
 */
void
free_dshconfig_internal(dshconfig_internal * i)
{
  free (i->title);
  free (i->data);
  free (i);
}

/**
   Frees up memory allocated by open_dshconfig.
 */
void
free_dshconfig(dshconfig* d)
{
  dshconfig_internal * i;

  if (!d)
    return;
  for (i=d->config; i; )
    {
      dshconfig_internal * tmp = i->next ;
      free_dshconfig_internal(i);
      i=tmp;
    }
  free (d);
}


/**
 * A GNU-compatible malloc,
 * Code to work with autoconf AC_FUNC_MALLOC
 */
#undef malloc
static void *
rpl_malloc (size_t n)
{
  if (n == 0)
    n = 1;
  return malloc (n);
}
