
# Use the MinGfx::Mesh class to draw a rectangle subdivided into multiple triangles, representing a flat map of the Earth

For this portion I used Lerp() to calculate the x coordinates between the ranges of -pi and pi, and y coordinates between the ranges of
-pi/2 and pi/2 . These are the longitude and latitude coordinates and I passed them into the LatLongToSphere (if a sphere) and LatLongToPlane (if a plane)
to produce Points that could be added to the vertices vector.  I did it this way because Lerp allowed me
a seamless way to go between the x and y values. The only issue happened when trying to find the indices to use, which, after building up from a small 2x1 mesh, I was able to hone down into a consistent algorithmn.

#Apply a texture of the Earth to the rectangle so that it looks like the original image.

For this part I relied primarily on the lecture videos for guidance, and used the simple design of updating the text coordinates every iteration.

# Display on the Earth all the earthquakes that have happened within the past one year of the current visualization time.

To map the earthquakes, I used the earthquake magnitude sizes references on the richter magnitude scale found here: https://en.wikipedia.org/wiki/Richter_magnitude_scale

I simplified it for the scope of this project, so used QuickShapes::DrawSphere to draw quakes defined with the following magnitudes:
Great	8 or more  (sphere color is red)
Major	7 - 7.9    (sphere color is orange)
Strong	6 - 6.9  (sphere color is yellow)
Moderate	5 - 5.9  (sphere color is green)
Light	- less then 5 (bit different but wanted to not be too complicated, everything below moderate will be considered light) (color is blue)

To keep the spheres at a reasonable size, they're sizes were divided by 7. As the earthquake sizes are based on their magnitudes, larger earthquakes will
have larger spheres and smaller earthquakes will have smaller spheres.

# Change the vertex positions and normals to draw the Earth as a sphere instead of a rectangle and Smoothly transform the mesh between the flat map and the globe based on user input.

Besides updating LatLongToSphere to contain the proper x,y,z points and adding normals, the code is entirely the
same between the flat earth and the globe earth. To transform the mesh between the two, instead of creating accessible methods within the earth header file, I just called a method Switch() within earth.cc that did the switch by setting globe to true or false within the earth mesh. If it was true it was a sphere, if it was not the flat earth would be displayed. This was much easier as I had all the methods I needed easily accessible in the earth file without having to create methods for
them in the header file.
