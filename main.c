#include <stdio.h>
#include <string.h>
#include <unistd.h>

const char * MIT = "Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the \"Software\"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:\n\nThe above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.\n\nTHE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.\n\nExcept as contained in this notice, the name(s) of the above copyright holders shall not be used in advertising or otherwise to promote the sale, use or other dealings in this Software without prior written authorization.\n";

const char * GPL = "This program is free software: you can redistribute it and/or modify\nit under the terms of the GNU General Public License as published by\nthe Free Software Foundation, either version 3 of the License, or\n(at your option) any later version.\n\nThis program is distributed in the hope that it will be useful,\nbut WITHOUT ANY WARRANTY; without even the implied warranty of\nMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\nGNU General Public License for more details.\n\nYou should have received a copy of the GNU General Public License\nalong with this program.  If not, see <http://www.gnu.org/licenses/>.";

const char * WTFPL = "        DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE\n                    Version 2, December 2004\n\n Everyone is permitted to copy and distribute verbatim or modified copies of this license document, and changing it is allowed as long as the name is changed.\n\n            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE\n   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION\n\n  0. You just DO WHAT THE FUCK YOU WANT TO.\n\n";

int main(int argc, char *argv[])
{
  char holders[60];
  char years[60];
  char license[60];

  int rc = 0;
  if (argc < 2){
    rc = getlogin_r(holders, sizeof(holders));
    if (rc != 0){
      return 1;
    }
  }else{
    strcpy(holders, argv[1]);
  }
  if (argc < 3){
    strcpy(years, "2016");
  }else{
    strcpy(years, argv[2]);
  }
  if (argc < 4){
    strcpy(license, "MIT");
  }else{
    strcpy(license, argv[3]);
  }

  // printf("Your %s license will be copyrighted as\n", license);
  // printf("Copyright (C) %s %s \n", years, holders);
  FILE *f = fopen(license, "w");
  if (f == NULL)
  {
      printf("Error opening file!\n");
      return 1;
  }

  /* print copyright text */
  fprintf(f, "Copyright (C) %s %s \n\n", years, holders);

  /* print the license */
  if(strcmp(license, "MIT") == 0){
    fprintf(f, "%s\n", MIT);
  }else if (strcmp(license, "GPLv3") == 0){
    fprintf(f, "%s\n", GPL);
  }else if (strcmp(license, "WTFPL") == 0){
    fprintf(f, "%s\n", WTFPL);
  }

  fclose(f);
  return 0;
}

