//This will open a file, write the BMP header and return the pointer to the file
FILE* create_bitmap(int file_count)
{
    // create output file & check if valid
    char filename[8];
    sprintf(filename, "%03i.bmp", file_count);
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("could not create file.\n");
    }

    //https://docs.microsoft.com/en-us/windows/win32/wmdm/-bitmapinfoheader
    //write header info

    BITMAPINFOHEADER bi;

    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = SIZE;
    bi.biHeight = SIZE;
    bi.biPlanes = 1;
    bi.biBitCount = 24;
    bi.biCompression = 0;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 2835;
    bi.biYPelsPerMeter = 2835;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    BITMAPFILEHEADER bf;

    bf.bfType[0] = 'B';
    bf.bfType[1] = 'M';
    bf.bfSize = 54 + (SIZE * SIZE * 3);
    bf.bfReserved1 = 0;
    bf.bfReserved2 = 0;
    bf.bfOffBits = 54;

    //write output file's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, file);

    // write output file's BITMADINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, file);

    return(file);
}