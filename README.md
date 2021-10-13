## Cardinal Curve And Interpolation

Development environment: Qt 5.12
C++ | Interface Generation with programming

This program implements Cardinal spline curve generation, curve animation and interpolation algorithm, and generates programmatic interface based on Qt.



#### Final interface style

![13](http://github.com/Aliciarui/repository CurveNInterpolation/raw/main master/pic/13.png)



#### principle of the project

- ##### Hermite curve

  If you need to understand the Cardinal curve, you first need to understand the principle of the Hermite curve.

  ![1](D:\CurveNInterpolation\pic\1.png)

  (Hermite curve)

  If we need to obtain a curve, we essentially need to get a cubic function between two points.
  That is, **y = Ax^3 + Bx^2 + Cx + D**, there are still two ways to express a new parameter u between [0,1], and write both x and y as a cubic function of u, that is 

  **x = Au^3 + Bu^2 + Cu +D** 

  and 

  **y = Au^3 + Bu^2 + Cu +D**

  this is a two-dimensional parameter system equation.
  So what we have to do is to find this P(u)

  ![2](D:\CurveNInterpolation\pic\2.png)

  Four different types of curves represent different slopes. 

  Multiply it with the slope to get the expression of P(u)

  ![3](D:\CurveNInterpolation\pic\3.png)

- ##### Cardinal curve

  Cardinal curve adds slope calculations to its formula when compared to Hermite curve.

  ![4](D:\CurveNInterpolation\pic\4.png)

- ##### Interpolation

  Interpolation algorithms include linear interpolation and vector linear interpolation. Linear interpolation: perform linear interpolation on the coordinates Pi of each point on the initial and final shapes to obtain the intermediate shape of the object deformation; vector linear interpolation: calculate the corresponding length Li and angle for every two adjacent points on the initial and final shapes θ i, then linearly interpolate Li and θ i to obtain the intermediate length and angle, and sequentially connect the defined vectors after interpolation to obtain the intermediate change shape.

  ![7](D:\CurveNInterpolation\pic\7.png)

  

#### Code

- ##### Cardinal curve

  I need to code to calculate the curve. So I create cspline class and obtain grain and tension from the user input interface.

  Through GetCardinalMatrix(), combined with the value of tension, the matrix M is generated. Then through the value of Matrix() and grain, the corresponding interpolation point is generated, and the interpolation point information is stored in the Spline array.

  ![5](D:\CurveNInterpolation\pic\5.png)

  ![6](D:\CurveNInterpolation\pic\6.png)

  (For the specific code, please refer to the source file)

- ##### Interpolation

  Establish the Interpolation class and perform two interpolation calculations.

  ![8](D:\CurveNInterpolation\pic\8.png)

  Store the intermediate image information in the result container, call QTimer to obtain the interpolated image at a fixed frequency, and draw it on the screen.

  The biggest difference in the realization of these two kinds of interpolation should be linear interpolation and vector linear interpolation respectively using (x, y) coordinates and polar coordinates for operation.

  It is particularly important to note that the implementation of vector linear interpolation requires additional consideration of the ambiguity of the angle, that is, it is necessary to ensure that the difference is clockwise or counterclockwise. In the implementation process, I choose to ensure that the final angle is greater than the initial angle. 

  (For the specific code, please refer to the source file)

- ##### Animation

  The goal is to move the picture of the sphere along the direction of the spline curve and rotate the picture according to the slope.
  ![9](D:\CurveNInterpolation\pic\9.png)(sphere)
  Use getSlope() to obtain the slope of the curve, and use QTimer to obtain the characteristic point information of the curve at a fixed time frequency to change the position of the picture.

  ![10](D:\CurveNInterpolation\pic\10.png)

  ![11](D:\CurveNInterpolation\pic\11.png)

  The image size is fixed at 50*50. The translate function is called to change the center position of the image. In order to make the sphere rotate smoothly without flipping, use judgesymbol() to determine the positive and negative relationship between the two double variables to ensure that each call is compared to the previous one. The symbol does not change.



#### Interface and Button

![12](D:\CurveNInterpolation\pic\12.png)

- click to change "grain" and "tension"

- clear to clear all

- show spline and interpolation are the two parts of the project.

  click them to unlock other buttons.



#### Result

- click to create dots

  ![14](D:\CurveNInterpolation\pic\14.png)

- show spline(unlock buttons)

  ![15](D:\CurveNInterpolation\pic\15.png)

- choose to show interpolation points

  ![16](D:\CurveNInterpolation\pic\16.png)

- move and rotate the ball

  ![17](D:\CurveNInterpolation\pic\17.png)

- linear interpolation

  ![18](D:\CurveNInterpolation\pic\18.png)

- vector interpolation

  ![19](D:\CurveNInterpolation\pic\19.png)

