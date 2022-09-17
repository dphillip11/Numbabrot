import numpy as np
import cv2
import math

COLORS=30
# this will save a colormap look up table that can be applied by cv2

def createCmap():

    # randomly offset some sin waves, pick a entire period, 360 degrees,
    
    colormap = np.zeros((256, 1, 3), dtype=np.uint8)
      
    offset_r = np.random.randint(0, 360)
    offset_g = np.random.randint(0, 360)
    offset_b = np.random.randint(0, 360) 

    increment = 360/(COLORS-1)
 
    # using mod means the colors repeat but creates contrast on the m-set
    for i in range (255):
        j = int(i % COLORS)
        colormap[i, 0, 0]=(round(125 * (math.sin((increment * j) + offset_r)+1)))
        colormap[i, 0, 1]=(round(125 * (math.sin((increment * j) + offset_b) +1)))
        colormap[i, 0, 2]=(round(125 * (math.sin((increment * j) + offset_g)+1)))

    # print(colormap[:, 0, 0])

    
    cv2.imwrite('lut.bmp', colormap)
   
    
    lut = cv2.imread('lut.bmp')
    img_gray = cv2.imread('fish.png')

    im_color = cv2.LUT(img_gray, lut)

    # you can save the image a this point or enable the next lines of code to view it

    # cv2.imshow('color', im_color)
 
    # cv2.waitKey(0) 
  
    # # close all open windows 
    # cv2.destroyAllWindows() 
