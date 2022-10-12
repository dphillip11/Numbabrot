from multiprocessing import Pool
import numpy as np
import random
import math
import cv2
import time

ITER = 128
COLORS = 30
resolution = 5000
red =[]
green=[]
blue=[]

def main():
   
    #get resolution input that is an int
    while True:
        try:
            resolution = int(input("resolution: "))
            break
        except ValueError:
            print("enter a number")
    
    start_time = time.time()

    #create a number line over the domain of the m-set
    arr = np.linspace(-2, 2, num = resolution)


    matrix = []


    #concatenate coordinate values over the number line in the x and y direction
    for i in range (resolution):
        line=[]
        for j in range (resolution):
            line.append([arr[i],arr[j]])
        matrix.append(line)
        

    print("matrix created" + "--- %s seconds ---" % (time.time() - start_time))

    initColorMap(COLORS)


    print("colormap created" + "--- %s seconds ---" % (time.time() - start_time))

    m_values = []
    
    #calculate m-values using mandelbrot function
    with Pool(5) as p:
        m_values = p.map(mandelbrot, matrix)
    
    print("values calculated" + "--- %s seconds ---" % (time.time() - start_time))

    image_RGB = np.array(m_values)
  
    cv2.imwrite('pool.jpg', image_RGB)

    print("image saved" + "--- %s seconds ---" % (time.time() - start_time))

    




def mandelbrot(c):
    rgbv=[]
    for coordinate in c:
        
        x = coordinate[0]
        y = coordinate[1]
        iter = 0
        r = 0.0
        i = 0.0
        tempr = 0.0

        while (r * r) + (i * i) <= 4 and (iter < ITER):

            tempr = (r * r) - (i * i) + x
            i = (2 * r * i) + y
            r = tempr

            iter += 1

        rgbv.append(colormap(iter % COLORS))
    return rgbv

def colormap(m):

    r = (red[m])
    g = (green[m])
    b = (blue[m])

    rgb = [r, g, b]
    return rgb


def initColorMap(COLORS):

    increment = 360 / (COLORS - 1)

    random.seed()    
    offset_r = random.randint(0, 360)
    offset_g = random.randint(0, 360)
    offset_b = random.randint(0, 360)   

    for i in range (COLORS):

        red.append(round(125 * (math.sin((increment * i) + offset_r)+1)))
        green.append(round(125 * (math.sin((increment * i) + offset_b) +1)))
        blue.append(round(125 * (math.sin((increment * i) + offset_g)+1)))

    return[red,green,blue]




if __name__=="__main__":
    main()






