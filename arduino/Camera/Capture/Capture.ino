#include "ArduCAM.h"

ArduCAM myCam;

void setup() {
  // Initialize ArduCam with GC0328 camera module
  myCam.begin(CAMERA_MODEL_GC0328);
  
  // Set resolution
  myCam.setResolution(640, 480);
  
  // Set output format
  myCam.setFormat(RGB);
  
  // Start capture
  myCam.startCapture();
}

void loop() {
  // Check if frame is available
  if(myCam.available()) {
    // Get frame buffer
    uint8_t* imgBuf = myCam.readData();
    
    // Do something with the image buffer
    
    // Release the buffer
    myCam.releaseData(imgBuf);
  }
}
