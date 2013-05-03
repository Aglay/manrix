/*
 * ls for ManRix OS
 * Copyright (C) 2004, 2005	Manish Regmi (regmi dot manish at gmail dot com)
 *							Rajesh Bikram R.C   (rajee5283 at hotmail dot com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
/*
 * File: ls.c
 * 		A utility to list directories
 */

#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
  DIR *d;
  struct dirent *dirnt;
  int len;
  char *path = "/bin";
   
  d = opendir(path);
  if(d == NULL)
   {
     printf("could Not open Directory \"%s\"", path);
     return 0;
   }
  
  while ((dirnt = readdir(d)) != NULL)
  {
    if((strcmp(dirnt->d_name, ".") == 0) || ((strcmp(dirnt->d_name, "..") == 0)))
      continue;
    printf("%-20s ", dirnt->d_name);
  }
  
  return 0;
}
