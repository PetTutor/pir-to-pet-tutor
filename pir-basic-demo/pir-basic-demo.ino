/*macro definitions of PIR motion sensor pin and LED pin*/
#define PIR_MOTION_SENSOR A5 
#define LED_D0 0 //D0 to drive another LED on pin D0
#define COUNT_SCRATCH 1 // the LightBlue Bean scratch counter being used
int counter =0; // counter to share how many detections

void setup()
{
    unsigned long currentMillis = millis();

    pinMode(PIR_MOTION_SENSOR, INPUT);
    pinMode(LED_D0,OUTPUT);
     Bean.setScratchNumber(COUNT_SCRATCH, 0); // initialize the scratch area to known value so initial observations can be made


}

void loop()
{

    if(isPeopleDetected()) //if it detects the moving people?
    {
        Bean.setLed(255, 0, 0); //show red
        digitalWrite(LED_D0, HIGH); // added this LED to have another indicator
        counter = counter +1;
        Bean.setScratchNumber(COUNT_SCRATCH, counter); // we will store the number of detections so the LightBlue Explorer app can see it
    }
    else
    {   //flash blue as an indicator of waiting to detect something
        Bean.setLed(0, 0, 255);
        Bean.setLed(0, 255, 255);
        Bean.setLed(0, 0, 255);
        Bean.setLed(0, 255, 255);
        
        digitalWrite(LED_D0, LOW); 

    }
}


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
