#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "compress.h"

int main(int argc, char *argv[])
{
    (void)argc;
    char *type = argv[2] + strlen(argv[2]) - 4;
    if (strcmp(argv[1], "-c") == 0 && strcmp(type, ".txt") == 0)
    {
        int res = txt_to_bin(argv[2]);
        if (res == -1)
        {
            perror("txt_to_bin");
            return -1;
        }
    }
    else if (strcmp(argv[1], "-d") == 0 && strcmp(type, ".bin") == 0)
    {
        int res = bin_to_txt(argv[2]);
        if (res == -1)
        {
            perror("bin_to_txt");
            return -1;
        }
    }
    else
    {
        perror("not in the right format");
        return -1;
    }

    return 0;
}