#ifndef OAIP_LABS2_UTILS_H
#define OAIP_LABS2_UTILS_H

typedef struct {
    int len;
    char **str;
} string;

string *split(char *input, char *delimiter);

void swap_words(string *text, char *word1, char *word2);

char *multi_tok(char *input, char *delimiter);

char *file_read(char path[]);

#endif //OAIP_LABS2_UTILS_H
