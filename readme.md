# Numbabrot web app

#### Video Demo:  <https://drive.google.com/file/d/1WoXqx-RlFH0KyLxAoH1S55c8aeFoVNwn/view?usp=sharing>

![screenshot4](https://user-images.githubusercontent.com/109744044/193240431-870a079a-f6cf-461e-850a-77600e0d74f8.jpg)
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
    • The zipped static website in the homepage file explains some of my work along the way
 
![screenshot5](https://user-images.githubusercontent.com/109744044/193242649-cd54b4f7-6b40-478a-aa83-9255e46ddb1b.jpg)
Screenshot of homepage

###### About:

This project is essentially an exercise to practice skills learned during the Harvard CS50x course. It captures the progression through different tools and demonstrates the value of well written code that effectively exploits computing power. Without any special decorators, python performs much more slowly than C but given some powerful libraries we can reclaim any lost performance, most notably, in this project, using the @jit decorator but also using the pool function for multi-threading and also by leaning on efficient code and adapting it to your needs. Be careful, you can get lost in those images, these screenshots are from the webapp.


![screenshot1](https://user-images.githubusercontent.com/109744044/193240348-709f8abe-3709-4a0e-a839-ed8b732fda4e.jpg)
![screenshot2](https://user-images.githubusercontent.com/109744044/193240563-abe302d4-a81c-48f4-9c20-30d5034689fe.jpg)
![screenshot3](https://user-images.githubusercontent.com/109744044/193240564-e6760a45-9fda-4559-a893-cead31b56751.jpg)
