#include "help.h"
#include "query.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define CLR_RED "\033[1;31m"
#define CLR_YELLOW "\033[1;33m"
#define CLR_CYAN "\033[0;36m"
#define CLR_GREEN "\033[0;32m"
#define CLR_WHITE "\033[0m"
#define CLR_PURPLE "\033[0;35m"

const char *platformOpts[] = {
    "wii",
    "pc",
};

const int platformOptsSize = 2;

const char *gameOpts[] = {
    "EM1",
    "EM2",
};

const int gameOptsSize = 2;

int formatDependencies(char *dependencies, char *out) {

  int len = strlen(dependencies);
  int index = 1;
  out[0] = '\"';
  for (int i = 0; i < len; i++) {

    if (dependencies[i] == ' ') {
      out[index] = '\"';
      index++;
      out[index] = ',';
      index++;
      out[index] = '\"';
    } else {
      out[index] = dependencies[i];
    }
    index++;
  }
  out[index] = '\"';
  return 0;
}

int packMod() {
  char nameBuff[128];
  questionString("Mod Name: Mods/", nameBuff);
  char command[256];
  sprintf(command, "tar -czvf Mods/%s.tar.gz -C Mods/%s .", nameBuff, nameBuff);
  printf("Executing Tar Command...\n");
  system(command);
  printf("Packaging finished! Packaged mod saved to 'Mods/%s.tar.gz'.",
         nameBuff);
  return 0;
}

int initMod() {

  printf("Generated files will be put in the 'Mods' folder.\n");
  mkdir("Mods", 0777);

  char title[128];
  char description[1024];
  char dependencies[1024];
  char youtubeID[32];
  questionString("Mod Title: ", title);
  questionString("Mod Description (Keep it short): ", description);
  questionString("Mod Dependencies (each mod id is seperated by a space): ",
                 dependencies);
  questionString("YouTube Video ID (Not Required): ", youtubeID);
  const int platform =
      questionList("Select a platform:\n ", platformOpts, platformOptsSize);
  const int game = questionList("Select a game:\n ", gameOpts, gameOptsSize);
  printf("\nGenerating Files...\n");
  char pathBuf[128];
  sprintf(pathBuf, "Mods/%s", title);
  mkdir(pathBuf, 0777);
  sprintf(pathBuf, "Mods/%s/custom_files", title);
  mkdir(pathBuf, 0777);
  sprintf(pathBuf, "Mods/%s/custom_textures", title);
  mkdir(pathBuf, 0777);
  sprintf(pathBuf, "Mods/%s/mod.json", title);
  FILE *modMetadata = fopen(pathBuf, "w");
  char modMetadataBuff[8096];
  char formattedDependencies[4096];
  formatDependencies(dependencies, formattedDependencies);
  int size = sprintf(
      modMetadataBuff,
      "{\n    \"name\":\"%s\",\n    \"description\":\"%s\",\n    "
      "\"dependencies\":[%s],\n    \"youtube\": \"%s\",\n    \"platform\": "
      "\"%s\",\n    \"game\":\"%s\",\n    \"custom_textures_path\": "
      "\"custom_textures\",\n    \"custom_game_files_path\": "
      "\"custom_files\",\n    \"icon_path\": \"icon.png\"\n    }",
      title, description, formattedDependencies, youtubeID,
      platformOpts[platform], gameOpts[game]);
  fwrite(modMetadataBuff, size, 1, modMetadata);
  fclose(modMetadata);
  FILE *icon = fopen("icon.png", "w");
  fclose(icon);
  printf("File Generation Finished!\nIMPORTANT: Remember to change the "
         "'icon.png' to the image you want your mod to be displayed as on the "
         "Mod Market (Max resolution: 256x256)");

  return 0;
}

int main(int argc, char *argv[]) {
  // nasty af
  printf(" _______   _____ ______   ___       ________ _________  ___\n|\\  "
         "___ \\ |\\   _ \\  _   \\|\\  \\     |\\   ____\\\\___   ___\\\\  "
         "\\\n\\ \\   __/|\\ \\  \\\\\\__\\ \\  \\ \\  \\    \\ \\  "
         "\\___\\|___ \\  \\_\\ \\  \\\n \\ \\  \\_|/_\\ \\  \\\\|__| \\  \\ "
         "\\  \\    \\ \\  \\       \\ \\  \\ \\ \\  \\\n  \\ \\  \\_|\\ \\ \\ "
         " \\    \\ \\  \\ \\  \\____\\ \\  \\____   \\ \\  \\ \\ \\  \\____\n "
         "  \\ \\_______\\ \\__\\    \\ \\__\\ \\_______\\ \\_______\\  \\ "
         "\\__\\ \\ \\_______\\\n    \\|_______|\\|__|     "
         "\\|__|\\|_______|\\|_______|   \\|__|  \\|_______|\n");

  printf("\n-------------------------------------------------------------------"
         "------------------------\n");
  printf(CLR_CYAN "E-Mail: " CLR_GREEN "jonas@kalsvik.no " CLR_WHITE
                  "| " CLR_CYAN "Discord: " CLR_GREEN "@kalsvik" CLR_WHITE
                  " | " CLR_CYAN "Git Repository: " CLR_GREEN
                  "https://github.com/KjubDusJub/emlctl" CLR_WHITE);
  printf("\n-------------------------------------------------------------------"
         "------------------------\n");

  while (true) {
    char inputBuff[128];

    questionString("Input a command: ", inputBuff);

    if (strcmp(inputBuff, "init mod") == 0) {
      initMod();
    } else if (strcmp(inputBuff, "pack mod") == 0) {
      packMod();
    } else if (strcmp(inputBuff, "help") == 0) {
      displayHelp();
    } else {
      displayHelp();
      printf("Command not recognized...");
    }
  }

  return 0;
}
