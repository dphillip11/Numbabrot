int mandelbrot(double x, double y)
{
	int iter = 0;
	double r = 0;
	double i = 0;
	double tempr = 0;

    //while our value does'nt fall outside of the bounded region(circle of radius 2)
	while (((r * r) + (i * i) <= 4) && (iter < ITER) )
	{
        //removing the temp is interesting...
        //real part
		tempr = (r * r) - (i * i) + x ;
        //imaginary part
		i = (2 * r * i) + y;
		r = tempr;
		iter++;
	}
	return iter ;
}