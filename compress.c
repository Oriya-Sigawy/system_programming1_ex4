#include <stdio.h>
#include <stdbool.h>
#include "compress.h"
#include <string.h>
#include <stdlib.h>

int bin_to_txt(char *fileName)
{
    char *name = (char *)malloc((strlen(fileName)) * sizeof(char));         //should I allocated olace for '\0' too?
    size_t x = 0;
    while (fileName[x] != '.')
    {
        name[x] = fileName[x];
        x++;
    }
    strcat(name, ".txt");
    FILE *txt_file = fopen(name, "w");
    FILE *bin_file = fopen(fileName, "rb");
    char buff = 0;
    int end = 0;
    while ((end = fread(&buff, 1, 1, bin_file)) != 0)
    {
        buff = ~buff;
        int num1 = (buff >> 4);
        int num2 = buff & 15;
        fprintf(txt_file, "%d", num1);
        if (num2 != 0)
        {
            fprintf(txt_file, "%d", num2);
        }
    }
    fclose(txt_file);
    fclose(bin_file);
    return 0;
}

int txt_to_bin(char *fileName)
{
    int odd = 0;
    char *name = (char *)malloc((strlen(fileName)) * sizeof(char));
    size_t x = 0;
    while (fileName[x] != '.')
    {
        name[x] = fileName[x];
        x++;
    }
    strcat(name, ".bin");
    FILE *bin_file = fopen(name, "wb");
    FILE *txt_file = fopen(fileName, "r");
    char buff1 = getc(txt_file);
    char buff2 = 0;
    while ((buff2 = getc(txt_file)) != EOF && buff2 != '\n' && buff1 != EOF && buff1 != '\n')
    {
        buff1 = buff1 - '0';
        buff2 = buff2 - '0';
        buff1 = buff1 << 4;
        buff1 = buff1 | buff2;
        buff1 = ~buff1;
        fwrite(&buff1, 1, 1, bin_file);
        odd++;
        buff1 = getc(txt_file);
    }
    if (odd % 2 == 1)
    {
        buff1 = ~buff1;
        buff1 = buff1 << 4;
        fwrite(&buff1, 1, 1, bin_file);
    }
    fclose(txt_file);
    fclose(bin_file);
    return 0;
}