#include "query.h"
#include <stdio.h>
#include <string.h>

int questionString(const char *question, char *answer) {
  printf("\n");
  printf("%s", question);
  fgets(answer, 1024, stdin);
  int size = strlen(answer);
  for (int i = 0; i < size; i++) {
    if (answer[i] == '\n') {
      answer[i] = 0;
    }
  }
  return 0;
}

int questionList(const char *question, const char **opts, int size) {
  printf("\n");
  printf("%s", question);
  for (int i = 0; i < size; i++) {
    printf("%d - %s\n ", i + 1, opts[i]);
  }
  int index = -1;
  printf("\n");
  while (index < 0 || index > size) {
    printf("Enter a digit (1/%d): ", size);
    if (scanf("%d", &index) == 0) {
      printf("Not a digit!\n");
      scanf("%*s");
      index = -1;
    }
  }
  return index - 1;
}
