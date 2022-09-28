import cv2
import time
import math
import numpy as np
from numba import jit, prange
ITER = 500
COLORS = 60
resolution = 5000
offset_x=0
offset_y=0
zoom=0.5

# this decorator makes a HUUUGGGE amount of difference, try with and without
@jit(nopython=True, fastmath=True, parallel=True)
def numbabrot():

    red = np.zeros((COLORS))
    green = np.zeros((COLORS))
    blue = np.zeros((COLORS))

    increment = 360 / (COLORS - 1)
  
    offset_r = np.random.randint(0, 360)
    offset_g = np.random.randint(0, 360)
    offset_b = np.random.randint(0, 360) 
 

    for i in prange (COLORS):

        red[i]=(round(125 * (math.sin((increment * i) + offset_r)+1)))
        green[i]=(round(125 * (math.sin((increment * i) + offset_b) +1)))
        blue[i]=(round(125 * (math.sin((increment * i) + offset_g)+1)))
    
    image = np.zeros((resolution, resolution, 3 ), dtype=np.uint8)
    
    
    for i in prange(resolution):
        for j in prange(resolution):
            y = (2.0 * i)/ resolution;  ##gives a range from 0 to 2
            y = y - 1.0     ##centres about origin
            y = y / zoom   ##magnifies coordinates
            y = y + offset_y   ##moves centre of magnification

            x = (2.0 * j)/ resolution       ##gives a range from 0 to 2
            x = x - 1.0     #centres about origin
            x = x / zoom        ##magnifies coordinates
            x = x + offset_x       ##moves centre of magnification
            
            c = complex(x,y)
            z = complex(0,0)
            iter = 0

            while abs(z)<2 and iter < ITER:
                z = z**2 + c
                iter += 1
          
            mv = iter % COLORS
            r = red[mv]
            g = green[mv]
            b = blue[mv]

            image[i][j] = [r,g,b]

   
    return image
            



start_time = time.time()

image = numbabrot()
cv2.imwrite('numbabrot.jpg', image)
print("saved" + "--- %s seconds ---" % (time.time() - start_time))




    