#include <stdio.h>

extern char **environ;

int main(int argc, char *argv[], char *env[]) {
	(void)argc; 
	(void)argv; 

	printf("Address of env: %p\n", (void *)env);

	printf("Address of environ: %p\n", (void *)environ);

	if (env == environ) {
		printf("env and environ point to the same location.\n");
	} else {
		printf("env and environ point to different locations.\n");
	}

	return 0;
}

