#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover <file>/n");
        return 1;
    }

    //create pointer to raw file
    FILE *raw_file = fopen(argv[1], "r");

#define BLOCK_SIZE 512 * sizeof(BYTE)

    //allocate buffer space for 512 bytes plus null character
    BYTE *buffer = malloc(sizeof(BYTE) * (512 + 1));

    //count image files, start at zero
    int file_count = 0;
    //create a filename pointer
    char filename[8];
    //write first filename
    sprintf(filename, "%03i.jpg", file_count);
    //create write file pointer
    FILE *img = fopen(filename, "w");


    //read block to buffer so long as block is available, find first jpeg
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        //search for jpeg header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            fwrite(buffer, BLOCK_SIZE, 1, img);
            break;
        }
    }

    //write subsequent blocks unless new file detected
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        //search for jpeg header

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //close file, change file name, reopen pointer
            fclose(img);
            file_count ++;
            sprintf(filename, "%03i.jpg", file_count);
            img = fopen(filename, "w");
        }

        fwrite(buffer, BLOCK_SIZE, 1, img);

    }
    fclose(img);
    fclose(raw_file);
    free(buffer);

}


