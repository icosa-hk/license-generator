#include <stdio.h>
#include <string.h>
#include <unistd.h>

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
    //holders = argv[1];
  }
  if (argc < 3){
    strcpy(years, "2016");
    //years = '2016';
  }else{
    strcpy(years, argv[2]);
    //years = argv[2];
  }
  if (argc < 4){
    strcpy(license, "MIT");
    //license = 'MIT';
  }else{
    strcpy(license, argv[3]);
    // license = argv[3];
  }

  printf("Your %s license will be copyrighted as\n", license);
  printf("Copyright (C) %s %s \n", years, holders);
  return 0;
}