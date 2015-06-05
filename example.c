#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void debug_print(char* to_print) {
	for (int i = 0; i < 12; i++) {
		printf("%c", to_print[i]);
	}
	printf("\n");
}

char* allocate_and_copy_string(char* to_copy) {
	char* str = (char *)malloc(strlen(to_copy) * sizeof(char) + 1);
	strcpy(str, to_copy);
	// free(str);

	return str;
}

int main() {
  char* hello_world = allocate_and_copy_string("hello world");
  char* garbage = allocate_and_copy_string("zjxc");

  // free(hello_world);
  // free(garbage);

  printf("%s\n", hello_world);
  printf("%s\n", garbage);
  // debug_print(garbage);

  free(hello_world);
  free(garbage);

  return 0;
}