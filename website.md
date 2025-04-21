# Implementation

The website was implemented through a python appliaction that implemented the flask libary. A HTML file templates/index.html was used to control the design of the webpage with integrated javascript functions.

# Communication 

The website recieved communicaitons from the cpp code through FastDDS publishers/subscribers. When the value of ToFSensor or MotorControls changes it is published to a FastDDS publisher and the website uses a FastDDS subscriber for each of these publishers to recieve the new data. When the data is recieved from a Python FastDDS subscriber it is then sent to the website through a socket.io port, where a javascript function updates the website with this new value. A seperate javascript function is used to plot the new values recieved through the socket.io port on x and y points of a graph, that displays how the duty_cycle and distance change over time.

# Functionality 

Having real time values of how the system is preforming on the website helps users debug and tune there system to there specific needs. The real time graph of distance and duty cycle helps the user identify how the work together and create the realationship between these values that works for them.
