#include "help.h"
#include <stdio.h>
void displayHelp() {
  printf("-- Help --\n");
  printf(
      "init mod | Creates a skeleton project with a mod metadata creator.\n");
  printf("pack mod | Create a ready-to-publish archive of a mod within the "
         "'Mods' folder.\n");
}
