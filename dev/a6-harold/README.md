# C Range Work

I used the alogithmn defined in the write up: create a new mesh m, loop through the vertices to convert them into 3d points (defined a skypoint, read in the vertex data of the mesh,
called ScreenPtHitsSky to convert 2d point to 3d point then assigned it to skypoint, added it to vertices list), and then stored the results into a new sky struct).

# B and A Range Work

Here I also followed the algorithmn in the write up except I had to account for the fact that if the starting point's x value was less then that of the ending point's 
when defining the plane, the plane would need to start from the opposite direction (i.e. e-s instead of s-e). This was added because strokes beginning from the right
hand side of the screen going to the left worked to compute the hills, but the opposite failed to do so and sometimes looked to collapse.
