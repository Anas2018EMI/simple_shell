#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to split a string into words
char **split_string(char *str, int *word_count) {
    // Initial memory allocation for the word array
    int capacity = 10;
    char **words = malloc(capacity * sizeof(char *));
    if (words == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    int count = 0;
    char *token = strtok(str, " ");
    while (token != NULL) {
        if (count >= capacity) {
            // Doubling the capacity if the current allocation is not enough
            capacity *= 2;
            char **new_words = malloc(capacity * sizeof(char *));
            if (new_words == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                free(words);
                return NULL;
            }
            for (int i = 0; i < count; i++) {
                new_words[i] = words[i];
            }
            free(words);
            words = new_words;
        }

        // Storing the word in the array
        words[count] = token;
        count++;
        token = strtok(NULL, " ");
    }

    *word_count = count;
    return words;
}

int main(void) {
    char input[] = "This is a test string to be split";
    int word_count = 0;

    char **words = split_string(input, &word_count);
    if (words == NULL) {
        return 1;
    }

    // Print the words
    for (int i = 0; i < word_count; i++) {
        printf("Word %d: %s\n", i + 1, words[i]);
    }

    // No need to free the individual words since they are part of the original string
    free(words);

    return 0;
}

