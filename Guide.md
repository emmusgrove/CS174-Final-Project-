This code was able to depict the kinematic problem of if you have three points at the vertices of a triangle with a designated height and they chase each other at a designated speed, when (in milliseconds) and where will they eventually meet. This code accomplish the tasks of:
    -Using the tinygl library to create a simulation that allows the user to observe the problems results. 
    -Output the amount of milliseconds it took for the particles to meet
    -Depict the problem not only in the form of a triangle but also a square and a circle
    -Allow the users to determine the speed of the particles
    -Allow the users to determine the height and width of the square and triangle or the diameter of the circle. 
    -Store the x and y coordinates of all the particles in the code for the entirity of the runtime
    -Use those x and y coordinates to place points on a SimpleCanvas as well as a visualization of the shape the points were on that will be saved as a .png file to allow the users to view the outcome and results of the problem (as well as the movement of the particles over the entire runtime) after the code has stopped running. 

Directions to use the code:
If the user wants to draw a circle they must go to the build2 directory and type ./driver followed by the diameter (between 0 and 1) they want the circle to be, the number of points/particles which can be any integer, the velocity they want the particles to have in the x direction (between -0.2 and 0.2), the velocity they want the particles to have in the y direction (between -0.2 and 0.2), and the name they want for the resulting file (the file must be a .png file). Therefore, if I wanted a circle with a dimeter of 0.5 with 8 particles that have a velocity of 0.2 in the x direction and 0.1 in the y direction and a resulting file named "Circle.png" the terminal code will be as follows:
    ./driver circle 0.5 8 0.2 0.1 Circle.png

If the user wants to draw a triangle or square they must go to the build2 directory and type ./driver followed by the height (between 0 and 1) of the shape, the width (between 0 and 1) of the shape, the velocity they want the particles to have in the x direction (between -0.2 and 0.2), the velocity they want the particles to have in the y direction (between -0.2 and 0.2), and the name they want for the resulting file (the file must be a .png file). Therefore, if I wanted a triangle with a height of 0.5 and a width of 0.4 with the particles having a velocity in the x direction of 0.2 and 0.1 in the y direction and a resulting file named "Triangle.png" the terminal code will be as follows: 
    ./driver triangle 0.5 0.4 0.2 0.1 Triangle.png