#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_string(char *str) {
	char **result = NULL;
	char *token;
	int count = 0;

	// First, count the number of words
	char *str_copy = strdup(str);
	token = strtok(str_copy, " ");
	while (token != NULL) {
		count++;
		token = strtok(NULL, " ");
	}
	free(str_copy);

	// Allocate memory for the array of strings
	result = malloc((count + 1) * sizeof(char *));
	if (result == NULL) {
		return NULL;
	}

	// Split the string and store each word
	token = strtok(str, " ");
	for (int i = 0; i < count; i++) {
		result[i] = strdup(token);
		token = strtok(NULL, " ");
	}
	result[count] = NULL;

	return result;
}

int main() {
	char input[] = "This is a test string";
	char **words = split_string(input);

	if (words == NULL) {
		printf("Memory allocation failed.\n");
		return 1;
	}

	printf("Original string: %s\n", input);
	printf("Split words:\n");
	for (int i = 0; words[i] != NULL; i++) {
		printf("%d: %s\n", i + 1, words[i]);
		free(words[i]);
	}
	free(words);

	return 0;
}
