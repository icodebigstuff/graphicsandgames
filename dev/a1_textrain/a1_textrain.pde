/*
 * CSci-4611 Assignment #1 Text Rain
 */


/* Note: if Processing's video library does not support your particular combination of webcam and
   operating system, then the Sketch may hang in the setup() routine when the list of available
   image capture devices is requestd with "Capture.list()".  If this happens, you can skip all of
   the camera initilization code and just run in movie mode by setting the following global 
   variable to true. 
 */

boolean forceMovieMode = false;

// Global vars used to access video frames from either a live camera or a prerecorded movie file
import processing.video.*;
import java.util.Random;
PImage other;
String[] cameraModes;
Capture cameraDevice;
Movie inputMovie;
boolean initialized = false;
String letters = "rain rain go away come on back another day if you dont i dont care";
int vidSpeed = 0;
boolean stop = false;

// Both modes of input (live camera and movie) will update this same variable with the lastest
// pixel data each frame.  Use this variable to access the new pixel data each frame!
PImage inputImage;
PImage mirror;

PFont f;
// Called automatically by Processing, once when the program starts up
int threshold = 128;
boolean space = false;

// Returns: thresholded color (black or white)
color thresholdPixel(color inputPixel) {
  //alternative call: float greenc = c >> 8 & 0xFF
  //source: https://py.processing.org/reference/green.html
  
  if (brightness(inputPixel) > threshold) {
    inputPixel = color(255);
  } else {
    inputPixel = color(0);
  }
  return inputPixel;

}

class Letters {
      int x = 0;
      int y = int(random(-200,-100));
      int  speed = int(random(2,8));
      int index =0 ;
      int val = 0;
      boolean findDark = false;
       void fall() {
         if (findDark == false) {
            y = y + speed;
            if (y > mirror.height) {
              y =int(random(-100, -50));} } 
      }
      
      void checkDark(){
        if (x > 0 && y > 0 && (x< mirror.width) && (y < (mirror.height - speed))){
                  if(brightness(mirror.pixels[x+(y-1)*(mirror.width)]) > threshold) {
                   y = y +5 ;}
                  else if (brightness(mirror.pixels[x+y*(mirror.width)]) <= threshold) {
                  y = y - 1;
                  } } else { findDark = false;}
      }
      
      void makeChar(int i) {
         text(letters.charAt(i),x,y); 
        
      }
      
      void checkThreshold() {
          if (x > 0 && y > 0 && (x< mirror.width) && (y < (mirror.height - speed))) {
              int index1D = x + y*(mirror.width);
              color check = thresholdPixel(mirror.pixels[index1D]);
              if(check == color(0)) {
               findDark = true; }
         }
        
      }

}
  


Letters[] s = new Letters[letters.length()];
void setup() {
  size(1280, 720);  
  inputImage = createImage(width, height, RGB);
  mirror = createImage(inputImage.width, inputImage.height, RGB);
  f = loadFont("ArialMT-28.vlw");
  textFont(f);
  fill(255,0,0);
  int spacing = 40;
  int new1 = 0;
 
  for(int i = 0; i<s.length;i++){
  s[i] = new Letters();
  //quasi-random way to drop letters while still giving reasonable chance to see a word
   if (i%10 == 0) {
    new1 = int(random(mirror.width));
  }
  s[i].x += new1;
  new1 += spacing;

  }


  
  if (!forceMovieMode) {
    println("Querying avaialble camera modes.");
    cameraModes = Capture.list();
    println("Found " + cameraModes.length + " camera modes.");
    for (int i=0; i<cameraModes.length; i++) {
      println(" " + i + ". " + cameraModes[i]); 
    }
    // if no cameras were detected, then run in offline mode
    if (cameraModes.length == 0) {
      println("Starting movie mode automatically since no cameras were detected.");
      initializeMovieMode(); 
    }
    else {
      println("Press a number key in the Processing window to select the desired camera mode.");
    }
  }

}




// Called automatically by Processing, once per frame
void draw() {
  // start each frame by clearing the screen
  background(0);
    
  if (!initialized) {
    // IF NOT INITIALIZED, DRAW THE INPUT SELECTION MENU
    drawMenuScreen();      
  }
  else {
    // IF WE REACH THIS POINT, WE'RE PAST THE MENU AND THE INPUT MODE HAS BEEN INITIALIZED


    // GET THE NEXT FRAME OF INPUT DATA FROM LIVE CAMERA OR MOVIE  
    if ((cameraDevice != null) && (cameraDevice.available())) {
      // Get image data from cameara and copy it over to the inputImage variable
      cameraDevice.read();
      inputImage.copy(cameraDevice, 0,0,cameraDevice.width,cameraDevice.height, 0,0,inputImage.width,inputImage.height);
    }
    else if ((inputMovie != null) && (inputMovie.available())) {
      // Get image data from the movie file and copy it over to the inputImage variable
      inputMovie.read();
      inputImage.copy(inputMovie, 0,0,inputMovie.width,inputMovie.height, 0,0,inputImage.width,inputImage.height);
    }


    // DRAW THE INPUTIMAGE ACROSS THE ENTIRE SCREEN
    // Note, this is like clearing the screen with an image.  It will cover up anything drawn before this point.
    // So, draw your text rain after this!
 
  

    // DRAW THE TEXT RAIN, ETC.
    // TODO: Much of your implementation code should go here.  At this point, the latest pixel data from the
    // live camera or movie file will have been copied over to the inputImage variable.  So, if you access
    // the pixel data from the inputImage variable, your code should always work, no matter which mode you run in.
    
  
  //Mirror Image
  loadPixels();

  for (int x = 0; x < inputImage.width; x++) {
     for (int y = 0; y < inputImage.height; y++ ) {
        mirror.pixels[inputImage.width - x - 1 + y*inputImage.width]  = inputImage.pixels[x + y*inputImage.width];
      }
    }
  
 
  updatePixels();
  
  set(0,0,mirror);
  filter(GRAY); //grayscale image
  text("threshold: " + threshold , 0 , mirror.height-10); //Display threshold on lower left
   if (space == true) {
    filter(THRESHOLD); //debug mode
    text("threshold: " + threshold , 0 , mirror.height-10);
  }
  
  
   for(int i = 0; i<s.length;i++){
     
      s[i].makeChar(i);
      s[i].checkDark();
      
      s[i].checkThreshold();
      s[i].fall();

  }


  
  
 
  }
}


int count = 0;
// Called automatically by Processing once per frame
void keyPressed() {
  if (!initialized) {
    // CHECK FOR A NUMBER KEY PRESS ON THE MENU SCREEN    
    if ((key >= '0') && (key <= '9')) { 
      int input = key - '0';
      if (input == 0) {
        initializeMovieMode();
      }
      else if ((input >= 1) && (input <= 9)) {
        initializeLiveCameraMode(input);
      }
    }
  }
  else {
    // CHECK FOR KEYPRESSES DURING NORMAL OPERATION
    // TODO: Fill in your code to handle keypresses here..
    if (key == CODED) {
      if (keyCode == UP) {
        threshold++;
      }
      else if (keyCode == DOWN) {
        threshold--;

      }
    }
    else if (key == ' ') {
      // spacebar pressed
      if(count %2 == 0) {
      space = true; count++; } else {
        space = false; count++;
      }
    } 
  }
}



// Loads a movie from a file to simulate camera input.
void initializeMovieMode() {
  String movieFile = "TextRainInput.mov";
  println("Simulating camera input using movie file: " + movieFile);
  inputMovie = new Movie(this, movieFile);
  inputMovie.loop();
  initialized = true;
}


// Starts up a webcam to use for input.
void initializeLiveCameraMode(int cameraMode) {
  println("Activating camera mode #" + cameraMode + ": " + cameraModes[cameraMode]);
  cameraDevice = new Capture(this, cameraModes[cameraMode-1]);
  cameraDevice.start();
  initialized = true;
}

// Draws a quick text-based menu to the screen
void drawMenuScreen() {
  int y=10;
  text("Press a number key to select an input mode", 20, y);
  y += 40;
  text("O: Offline mode, test with TextRainInput.mov movie file instead of live camera feed.", 20, y);
  y += 40; 
  for (int i = 0; i < min(9,cameraModes.length); i++) {
    text(i+1 + ": " + cameraModes[i], 20, y);
    y += 40;
  }  
}
