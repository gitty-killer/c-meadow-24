#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *word;
    int count;
} WordCount;

static void add_word(WordCount **list, int *size, int *cap, const char *word) {
    for (int i = 0; i < *size; i++) {
        if (strcmp((*list)[i].word, word) == 0) {
            (*list)[i].count++;
            return;
        }
    }
    if (*size == *cap) {
        *cap = (*cap == 0) ? 16 : *cap * 2;
        *list = realloc(*list, (*cap) * sizeof(WordCount));
    }
    (*list)[*size].word = strdup(word);
    (*list)[*size].count = 1;
    (*size)++;
}

static int cmp_counts(const void *a, const void *b) {
    const WordCount *wa = (const WordCount *)a;
    const WordCount *wb = (const WordCount *)b;
    if (wa->count == wb->count) {
        return strcmp(wa->word, wb->word);
    }
    return wb->count - wa->count;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: textstats <path> [--top N]\n");
        return 1;
    }
    int top = 10;
    const char *path = argv[1];
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--top") == 0 && i + 1 < argc) {
            top = atoi(argv[i + 1]);
        }
    }

    FILE *f = fopen(path, "rb");
    if (!f) {
        perror("fopen");
        return 1;
    }
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = malloc(len + 1);
    fread(buf, 1, len, f);
    fclose(f);
    buf[len] = '\0';

    int lines = (len == 0) ? 0 : 1;
    for (long i = 0; i < len; i++) {
        if (buf[i] == '\n') lines++;
    }

    WordCount *list = NULL;
    int size = 0, cap = 0;
    char word[256];
    int wlen = 0;
    int word_count = 0;
    for (long i = 0; i <= len; i++) {
        char ch = buf[i];
        if (isalnum((unsigned char)ch)) {
            if (wlen < 255) word[wlen++] = (char)tolower((unsigned char)ch);
        } else if (wlen > 0) {
            word[wlen] = '\0';
            add_word(&list, &size, &cap, word);
            word_count++;
            wlen = 0;
        }
    }

    qsort(list, size, sizeof(WordCount), cmp_counts);

    printf("lines: %d\n", lines);
    printf("words: %d\n", word_count);
    printf("chars: %ld\n", len);
    printf("top words:\n");
    int limit = top < size ? top : size;
    for (int i = 0; i < limit; i++) {
        printf("  %s: %d\n", list[i].word, list[i].count);
    }

    for (int i = 0; i < size; i++) {
        free(list[i].word);
    }
    free(list);
    free(buf);
    return 0;
}
