from flask import session
from PIL import Image
import cv2
import math
import numpy as np
from numba import jit, prange

def mandelbrot():
    session['alt']=0
    width = int(session['width'])
    height = int(session['height'])
    x1 = float(session['x1'])
    y1 = float(session['y1'])
    x2 = float(session['x2'])
    y2 = float(session['y2'])
    quality = int(session['quality'])
    colormap = int(session['colormap'])

    #produce mandelbrot image
    image = Image.effect_mandelbrot((width, height), (x1, y1, x2, y2), quality)
    image.save("static/bw.jpg")

    im_gray = cv2.imread("static/bw.jpg")

    if colormap == 30:
        # load lookup table
        lut = cv2.imread('static/lut.bmp')
        # colormap image
        im_color = cv2.LUT(im_gray, lut)

    else: 
        im_color = cv2.applyColorMap(im_gray, colormap)

    cv2.imwrite('static/rgb.jpg', im_color)

def runNumbabrot():
    session['alt']=1
    width = int(session['width'])
    height = int(session['height'])
    x1 = float(session['x1'])
    y1 = float(session['y1'])
    x2 = float(session['x2'])
    y2 = float(session['y2'])
    ITER = int(session['quality'])
    offset_r =  session['offset_r'] 
    offset_g = session['offset_g'] 
    offset_b = session['offset_b']
    image = numbabrot(width, height, x1, x2, y1, y2, ITER, offset_r, offset_g, offset_b)
    cv2.imwrite('static/rgb.jpg', image)

@jit(nopython=True, fastmath=True, parallel=True)
def numbabrot(width, height, x1, x2, y1, y2, ITER, offset_r, offset_g, offset_b):
    
    COLORS = 60

    red = np.zeros((COLORS))
    green = np.zeros((COLORS))
    blue = np.zeros((COLORS))

    increment = 360 / (COLORS - 1)
 

    for i in prange (COLORS):

        red[i]=(round(125 * (math.sin((increment * i) + offset_r)+1)))
        green[i]=(round(125 * (math.sin((increment * i) + offset_b) +1)))
        blue[i]=(round(125 * (math.sin((increment * i) + offset_g)+1)))

    image = np.zeros((height, width, 3 ), dtype=np.uint8)
    
    xRange = float(x2 - x1)
    yRange = float(y2 - y1)
    xStep = float(xRange/width)
    yStep = float(yRange/height)

    for i in prange(height):
        for j in prange(width):
            y = y1 + (i * yStep)
            x = x1 + (j * xStep)
            c = complex(x,y)
            z = complex(0,0)
            iter = 0

            while abs(z)<100 and iter < ITER:
                z = z**2 + c
                iter += 1
          
            mv = iter % COLORS
            r = red[mv]
            g = green[mv]
            b = blue[mv]

            image[i][j] = [r,g,b]

   
    return image
 

def initialise():
    session['x1'] = -2
    session['y1'] = -2* int(session['height'])/int(session['width'])
    session['x2'] = 2
    session['y2'] = 2* int(session['height'])/int(session['width'])
    session['quality'] = 20
    session['colormap'] = 1
    session['zoom'] = 0.25
    session['offset_r'] = np.random.randint(0, 360)
    session['offset_g'] = np.random.randint(0, 360)
    session['offset_b'] = np.random.randint(0, 360) 

def changeColor():
    session['colormap'] = (int(session['colormap']) + 1) % 22

def randomColor():
    offset_r = np.random.randint(0, 360)
    offset_g = np.random.randint(0, 360)
    offset_b = np.random.randint(0, 360)
   
    session['offset_r'] = np.random.randint(0, 360)
    session['offset_g'] = np.random.randint(0, 360)
    session['offset_b'] = np.random.randint(0, 360)

def zoom(x,y):

    #get a percentage offset value from coordinates
    x = x / int(session['width'])
    y = y / int(session['height'])
    
    # current size
    spanX = float(session['x2'] - session['x1'])
    spanY = float(session['y2'] - session['y1'])
    
    x = float(x * spanX + session['x1'])
    y = float(y * spanY + session['y1'])

    session['x1'] = x - (spanX * 0.3)
    session['y1'] = y - (spanY * 0.3)
    session['x2'] = x + (spanX * 0.3)
    session['y2'] = y + (spanY * 0.3)
    session['zoom'] = session['zoom'] * 5 / 3

    # calculate centre

    xC = (session['x1'] + session['x2'])/2
    yC = (session['y1'] + session['y2'])/2

    # calculate x range
    xRange = 1 / float(session['zoom'])
    session['x1'] = x - (xRange/2)
    session['x2'] = x + (xRange/2)
    yRange = xRange * int(session['height'])/int(session['width'])
    session['y1'] = y - (yRange/2)
    session['y2'] = y + (yRange/2)



    


