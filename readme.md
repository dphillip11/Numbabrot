# Numbabrot web app

#### Video Demo:  <https://drive.google.com/file/d/1WoXqx-RlFH0KyLxAoH1S55c8aeFoVNwn/view?usp=sharing>
#### Description:

###### How to launch the web app:

    • Navigate to the folder “Web app”, install the required components as listed in requirements.txt
    • use the command “flask run” from the terminal and follow the link provided in the terminal window.
    • The app is self explanatory I hope, use the buttons at the top, increase quality as you dive deeper into the visualization. 
    • Method 1 utilizes the pillow library mandelbrot image function and the OpenCV color map.
    • Method 2 utilizes a randomized color map and uses the numba ‘@jit’ decorator.

###### Also included:

    • The ‘html disaster’ contains an attempt to create an html engine by coloring <div> tags to be used as pixels. It is generally a bad idea but it allows for images to be generated and will run in most browsers. Try to inspect the page once the image renders.
    • The “testpy” folder includes some other incarnations of my code utilizing different computing resources, I settled on the two in the web app due to speed. There is also a tool for creating custom color maps to be used with the openCV library.
    • The ‘m-set c’ folder contains the original code along with edge detection and repositioning, suitable for automating the generation of images.

###### About:

This project is essentially an exercise to practice skills learned during the Harvard CS50x course. It captures the progression through different tools and demonstrates the value of well written code that effectively exploits computing power. Without any special decorators, python performs much more slowly than C but given some powerful libraries we can reclaim any lost performance, most notably, in this project, using the @jit decorator but also using the pool function for multi-threading and also by leaning on efficient code and adapting it to your needs. Be careful, you can get lost in those images...
