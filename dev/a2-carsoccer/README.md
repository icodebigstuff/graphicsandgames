to run: first create a build directory, then run cmake .. within it, then do start a2-carsoccer.sln


# Design Decisions:

• Drawing the boundary and goals

I chose to use the QuickShapes::DrawLines() routine for drawing the boundary of the pitch
but I used the QuickShapes::DrawLineSegment routine for drawing the goals. This was because
the goals needed to be criss-crossed and while the drawLines routine was good for drawing lines
at a given position, it took less code and effort to just loop through the DrawLineSegments routine
and draw a line at each specified x position, and then draw a line at each specified y position.
I used DrawLines to draw the frame for each goal though.

• Make the Ball move through the air based on a random initial velocity and relaunch the ball when the space bar is pressed

For this part I defined "random initial velocity" as some randomly selected velocity in the x range of -20 to 40 (so the ball will launch randomly either
to its left or to its right), the y range of 0 to 10 (to limit how far up it sails), and the z range of 0 to 20. When the space bar is pressed
it calls the Reset function is Ball to return the ball to its initial position and re-make the initial velocities. I chose these
values for the velocity because it worked pretty well (I had tried several different velocities and they all make the ball go too fast, too slow, etc.)
and launched at realistic speeds.

• Update the ball’s position and velocity each time step based on the acceleration due to gravity

For this part I chose to make two functions within the ball header file: the move and the gravity functions. Every timestep
I'd pass in that value to both functions. When it's passed into the gravity function, it updates the velocity based on
the gravity vector which I put it's downwards force as 15 to limit the amount of time the ball would stay in the air.
The move function just moves the ball by updating its position based on its velocity and timestep. I chose the value of 15
for gravity because I experimented a bit and found that it kept the ball in the air for a reasonable amount of time.

• Detect a contact between the ball and the ground, ceiling, and walls and make the ball bounce in the correct direction. Detect when the car hits the walls too.

The design decision for this was based entirely on the lectures and write up we were given to detect a collision, reset the position of the ball to be just touching,
and reflect it across the normal. The normal for this I didn't define as the Unit Vector of its collision position directly (as in I didn't calculate them), instead
I just simplified this to be the Normal vector of the location of its collision (i.e. if it hits the left wall, position x would be negative and the ball would need to have its x position reset to be its collision position by altering x and then that normal would just be the normal of the x position that the velocity would need to be updated with) . I chose this method because it was straight forward and how I thought of the problem initially. I chose the same method for the car's collision
with walls.

• Decrease the speed of the ball when it bounces

I did this using the decrease_speed function in the ball header file that increments the velocity by a factor of 0.9 (decreasing it). I chose 0.9 from experimentation and I didn't think it mattered much by how big a factor to decrease the ball's velocity by.

• Contact between Car and Ball / incorporate the velocity of the car into ball's reflection velocity

I did this all in one sweep and leaned heavily on the Lecture's calculations to simulate the collision. A design decision I made outside of the Lecture's calculations was that when setting the velocity of the ball to reflect across the normal, I added the car's current velocity so that if the car comes at it fast,
the ball will have a greater velocity upon contact then it otherwise would have, and if it comes at it slow, it will mirror that pattern. I chose this method
because it seemed a simple way to incorporate the car's velocity without calling another function.

• Realistic Driving Model of car

Initially I chose to launch the car in the left pitch side (similar to how I did the ball, I used a move function). After which the car could be manipulated in speed by selecting the up arrow to speed it up and the down arrow to slow it down. I didn't get the rotation down fully, but I did get it to not move horizontally and if the left or right buttons were pressed, it would change the car's position to go that direction. I chose this method because there weren't any specifications
on how the car should be initially launched (so I chose a constant place to launch it to and a constant velocity to do so), and because I couldn't quite get the car to rotate so I had it shift positions.

• Ball hits goal and Reset

For this method I detected when the ball was passed either goal, and if it was, I just called the Reset function on both the car and the ball. I chose this
method because it was a straight forward way to do so.
