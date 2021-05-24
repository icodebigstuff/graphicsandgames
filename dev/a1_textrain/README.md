
I chose a class to hold each letter so I could instantiate functions relating to it
in order to control features such as fall, threshold checking, and rising.

The design decision I made to stop the characters from falling on a dark object was to utilize the thresholdPixel
function from the worksheet. Instead of using green(), I instead used brightness() to extract the brightness
value of the pixel for two reasons:
      1. I found it worked better at detecting shifts in threshold
      2. In order to get green() to work properly, the video needed to be blurred first which in processing, would take
        more time then just using the brightness method (not sure if this was just the GPU I was using or not).
I also used a similar algorithm to raise the letters when a dark object moved by detecting whether the pixel's current
position's brightness is still below threshold. If it was, the letter wouldn't be raised, and if not, it would. If the object moved
down, the letter would also follow, but would continue falling if the object moved away. I chose this way because it made the most
sense to me (although its a bit choppy) - instead of having to anticipate every pixel's brightness around it, a letter only worried about its 
own and moved accordingly.

Threshold checking was also important for making the falling algorithm robust enough to stop at any dark pixel. The class functions checkDark
and checkThreshold were used to set the value of findDark to true or false. True meant a dark value was found so to not move, false meant it wasn't
and could be moved.

My algorithm to qausi-randomly select letters to display from the string to make them fall was done so that if the current
iterative value (i)'s modulo 10 was equal to 0 then the letter would be placed randomly in the scope of the screen.
If not, it would be spaced out and set at a recurring value. I chose this because it gave a reasonable likelihood that a whole word would appear
but still be able to randomize the majority of the string. This decision was based on experimentation with the modulo (some values gave less words
then others such as i%2 randomized every other word).

Threshold change was calculated in a way that a count value is updated every time the space bar is pressed, if once
then its toggled to threshold/debug mode and a boolean variable is set to true, if twice, the condition on whether or not the count%2 == 0 would be broken
so count would be reset and the global boolean variable controlling the toggle would be set to false - returning it to non-debug mode.

I used the random() function to add variation to the velocity (changing the y value) as it was the easiest way to do so.

I chose to add the threshold count to the lower left of the screen so as to not clutter it.
