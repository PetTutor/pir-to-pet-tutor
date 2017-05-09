// 2017 05 06 john blue pir-to-feeder proof of concept
// Using the PIR, passivive infrared, motion detection demo code, this sketch integrates the communication to the PetTutor feeder
// * The communication approach is the same as the Smart Clicker: PIR / Bean+ comunicates via the serial interface thru bluetooth to the iOS app.
// * The iOS app then communicates with the Pet Tutor feeder via the serial interface thru bluetooth.

#define CLICKER_DEVICE 500 // from the feeder code - identifies the device type to the App.  For SmartClicker it's CLICKER_DEVICE (eg: 500)

#define COUNT_SCRATCH 1 // the LightBlue Bean scratch register being used
#define sbDeviceType 5  // the scratch register used to store the CLICKER_DEVICE info

/*macro definitions of PIR motion sensor pin*/
#define PIR_MOTION_SENSOR A5 // A5 is the Grove port for the PIR

boolean beenHereBefore = false; // flag to help narrow trigger of feeder to once per detection window

const int warm_up = 6; //number of 10 second batches used in warm up at startup
int counter = 0; // counter to share how many detections

void setup()
{

boolean beenHereBefore = false; // ensuring narrowing the trigger time flag is set to false in setup

// start up the communication with the iOS app; borrowed from the clicker code
  Serial.begin(57600); // ; borrowed from the clicker code
  Serial.setTimeout(100); // DO NOT REMOVE ; borrowed from the clicker code

// Do NOT remove this delay.  It is required. ; borrowed from the clicker code
  delay(100); //give everything a chance to start otherwise funky stuff starts happening ; borrowed from the clicker code

  Bean.enableConfigSave(false);   // Don't save BLE config changes such as advertising rate to non-volatile storage; borrowed from the clicker code
  Bean.enableAdvertising(true); // ; borrowed from the clicker code

  Bean.setScratchNumber(sbDeviceType, CLICKER_DEVICE);  // defines the device as a clicker for the app ; borrowed from the clicker code

  Bean.enableWakeOnConnect( true ); // used so that if been is asleep, a connect will wake it up; borrowed from the clicker code

    pinMode(PIR_MOTION_SENSOR, INPUT); // Setup connection for PIR

    Bean.setScratchNumber(COUNT_SCRATCH, 0); // initialize the scratch area to known value so initial observations can be made
 // let the PIR warm up for warm_up*10000 milliseconds
 // The PIR appears to have a need to get "warmed up", so this sensor startup provides a loop to help support warm up
 // The LED settings are to help identify, with green, the warm up is still happening.
   for (int i=1; i <= warm_up; i++){

     Bean.setLed(0, 255, 0); // LED green
     Bean.sleep(5000); // first part of 10,000 millisceconds
     Bean.setLed(0, 128, 0); // LED off
     Bean.sleep(5000); // second part of 10,000 millisceconds
   } 

}

void loop()
{
   int rcode = 0;
   boolean isPeopleDetectedFlag = false; // setup flag for function assignment

   isPeopleDetectedFlag = isPeopleDetected(); // used to keep from calling the detect function multiple times through the state detection "if" statements below

   if(isPeopleDetectedFlag && !beenHereBefore) // trigger feeder
    {

     SendAppHit(); // tell app to trigger feeder
     beenHereBefore = true; // we have now been here before
     Bean.setLed(255, 0, 0); // show red
     counter = counter +1; // count detect times
     Bean.setScratchNumber(COUNT_SCRATCH, counter); // we will store the number of detections so the LightBlue Explorer iOS app can see it
}
    else if(isPeopleDetectedFlag && beenHereBefore) // do nothing
     {
     Bean.setLed(255, 0, 0); // show red
     
     }
     else if(!isPeopleDetectedFlag) // go back to waiting for detection
     {
// reset been here before state
     beenHereBefore = false; 
     Bean.setLed(0, 0, 255); // set blue as an indicator of waiting to detect something

     } // end wait for detection else
    

} // end loop


/***************************************************************/
/*Function: Detect whether anyone moves in it's detecting range*/
/*Return:-boolean, true is someone detected.*/
// This code came from http://wiki.seeed.cc/Grove-PIR_Motion_Sensor/ page
boolean isPeopleDetected()
{
    int sensorValue = digitalRead(PIR_MOTION_SENSOR);
    if(sensorValue == HIGH)//if the sensor value is HIGH?
    {
        return true;//yes,return true
    }
    else
    {
        return false;//no,return false
    }
}

/*
 *    v8.5 isBeanConnected.
 *    
 *    Getting false negatives from Bean.getConnectionState which plays heck because
 *    sketch thinks we are disconnected but the bean and app think connected.
 *    
 */
 
bool isBeanConnected(void)
{
  int nCheckCount = 0;
  
  bool nResult = Bean.getConnectionState();
  
  while ( (nResult == false) && (nCheckCount <= 3) )
  {
    delay(10);
    nResult = Bean.getConnectionState();
    nCheckCount++;
  }
  
  return nResult;
}

// fundtion to tell iOS to trigger feeder
 void SendAppHit(void)
 {
  
  Serial.write("ACC_CMD,1"); // send command to iOS app to trigger feeder
}
