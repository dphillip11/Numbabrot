from PIL import Image
import cv2
import time


def mandelbrot():

    start_time = time.time()

    image = Image.effect_mandelbrot((5000,5000), (-2, -2, 2, 2), 128)
    image.save("pilcv2.jpg")
    
    print("black and white completed" + "--- %s seconds ---" % (time.time() - start_time))

    im_gray = cv2.imread("pilcv2.jpg", cv2.IMREAD_GRAYSCALE)
    im_color = cv2.applyColorMap(im_gray, 5)

    print("color map completed" + "--- %s seconds ---" % (time.time() - start_time))

    cv2.imwrite('pilcv2.jpg', im_color)

    print("saved" + "--- %s seconds ---" % (time.time() - start_time))

mandelbrot()
