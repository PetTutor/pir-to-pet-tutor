# pir-to-pet-tutor
This code is used to demonstrate how the [Seeed PIR](http://wiki.seeed.cc/Grove-PIR_Motion_Sensor/) can be used to detect a person and trigger a Smart Animal Training Systems [Pet Tutor Pro with Bluetooth](https://smartanimaltraining.com/products/feeder-only) to dispense kibbles.

A demonstratrion video of the hardware and software in action is at: https://www.youtube.com/watch?v=UboJCq4RM9Y

#### pir-basic-demo.ino

A basic PIR demo, only requires the Bean+ and the PIR detector. 

The hardware required for this to function includes:

+ Seeed PIR with Grove connector
  * [http://wiki.seeed.cc/Grove-PIR_Motion_Sensor/](http://wiki.seeed.cc/Grove-PIR_Motion_Sensor/)
  * The cost to buy from Seeed is too much because of international shipping and import duties, so buy them here instead: [http://www.robotshop.com/en/seeedstudio-grove-pir-motion-sensor.html](http://www.robotshop.com/en/seeedstudio-grove-pir-motion-sensor.html) 

+ LightBlue Bean+ by PunchThrough Design
  * [https://store.punchthrough.com/collections/bean-family/products/lightblue-bean-plus](https://store.punchthrough.com/collections/bean-family/products/lightblue-bean-plus)


#### pir-to-feeder.ino

The hardware required for this to function includes everything for the PIR basic demo above plus:
+ Pet Tutor Pro with Bluetooth
  * [https://smartanimaltraining.com/products/feeder-only](https://smartanimaltraining.com/products/feeder-only)
+ One cardboard tub, like a toilet paper or paper towel tube

The code (arduino sketch) is used to allow the Bean+ to use the Seeed PIR, or passive infra red, motion detector to detect motion and request the Pet Tutor Blu app (iOS Version: 1.3 [https://itunes.apple.com/us/app/pettutor-blu/id934260904](https://itunes.apple.com/us/app/pettutor-blu/id934260904) or Andriod version 0.2.8 [https://play.google.com/store/apps/details?id=com.duffekmobile.pettutorblu](https://play.google.com/store/apps/details?id=com.duffekmobile.pettutorblu) ) to trigger the Pet Tutor Blu feeder to dispense kibbles.

#### Use cases for a PIR, Bean+, and Pet Tutor Pro with Bluetooth
How can the ability to detect a person or motion be of help in training pets? Below are some use cases. 
* Delivery person arriving and the dog always barks: The PIR could be placed to notice the delivery person and dispense a kibble as part of training to be quiet.
* A dog training setting, kennel, or shelter where there are many dogs in crates and a trainer or support person is walking down the aisle: The PIR could be set to trigger the feeder in advance of the person reaching a crate. 

Details on using this repository are on an Instrctables site: [https://www.instructables.com/id/Passive-Infrared-Motion-Detector-Pet-Tutor-Pro-Wit/](https://www.instructables.com/id/Passive-Infrared-Motion-Detector-Pet-Tutor-Pro-Wit/)
