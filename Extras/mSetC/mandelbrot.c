#define ITER 300
#define SIZE 5000
#define COLORS 30

#include <stdio.h>
#include <time.h>
#include "colormap.c"
#include "create_bitmap.c"
#include "mfunction.c"

typedef struct
{
	double x;
	double y;
}
coordinate;

RGBTRIPLE image[SIZE][SIZE];
//int r = 0;
#include "edges.c"


int main(void)
{
	clock_t t;
    t = clock();
	//initialise variables
	float zoom = 0.5;
	double im_offset = 0;
	double re_offset = 0;
	int images = 1;
	//set colour palette
	initialise_colormap();

	//repeat for each image
	for (int file_count = 0; file_count < images; file_count ++)
	{


		//get BMP file pointer with header
		FILE* file = create_bitmap(file_count);

		//convert each pixel index to a coordinate in the complex plane
		for (int i = 0; i < SIZE; i ++)
		{
			for (int j = 0; j < SIZE; j ++)
			{
				double y = (double)i / (double)SIZE;//gives a range from 0 to 1
				y = y - 0.5;//centres about origin
				y = y / zoom; //magnifies coordinates
				y = y + im_offset; //moves centre of magnification


				double x = (double)j / (double)SIZE;//gives a range from 0 to 1
				x = x - 0.5;//centres about origin
				x = x / zoom; //magnifies coordinates
				x = x + re_offset; //moves centre of magnification


				//asign color value based on number of mfunction iterations
				int colorvalue = mandelbrot(x, y) % COLORS;
				//assign an RGB to the color value
				RGBTRIPLE pixel = colormap(colorvalue);
				//update global array in memory
				image[i][j] = pixel;
				//write the pixel to the image file
				fwrite(&pixel, sizeof(RGBTRIPLE), 1, file);
			}
		}
		fclose(file);

		t = clock() - t;
		double time_taken = ((double)t)/CLOCKS_PER_SEC;
		printf("fun() took %f seconds to execute \n", time_taken);
    	return 0;
		// perform edge detection
		//change offset
		//coordinate p = reposition(zoom);
		//zoom in before next image
		// zoom = zoom * 100;
		//im_offset += p.x;
		//re_offset += p.y;

	}
}






