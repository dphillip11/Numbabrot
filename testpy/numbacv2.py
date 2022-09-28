import cv2
from PIL import Image
import numpy as np
from numba import jit
import time
import math

ITER = 500
COLORS =100
size = 5000
increment = 255/ (COLORS - 1)


def colorm():
      
    index = np.indices((size, size), sparse=False)
    index = ((4 / size) * (index)) - 2

    x = index[0]
    y = np.array(index[1] * complex(0, 1), dtype=complex)

    # create complex coordinate array
    complexArr = np.array((x + y), dtype=complex)

    image = mandelbrot(complexArr)
    # print(image)
    return image
    



@jit(nopython=True, fastmath=True)
def mandelbrot(arr):
    m = np.empty((size, size), dtype=np.uint8)
    for i in range(size):
        for j in range(size):
            z = complex(0, 0)
            iter = 0
            c = arr[i][j]
            while abs(z) < 2 and iter < ITER:
                z = z**2 + c
                iter += 1
            m[i][j] = 2 * (iter) * increment
    return m


start_time = time.time()
image = colorm()
print("calculated" + "--- %s seconds ---" % (time.time() - start_time))
cv2.imwrite('numbacv2.jpg', image)
print("saved" + "--- %s seconds ---" % (time.time() - start_time))

im_gray = cv2.imread("numbacv2", cv2.IMREAD_GRAYSCALE)
im_color = cv2.applyColorMap(im_gray, 5)

print("color map completed" + "--- %s seconds ---" % (time.time() - start_time))

cv2.imwrite('numbacv2.jpg', im_color)

print("saved" + "--- %s seconds ---" % (time.time() - start_time))
