/*
This example shows how to take simple range measurements with the VL53L1X. The
range readings are in units of mm.
*/
#include <Servo.h>
#include <Wire.h>
#include <VL53L1X.h>

VL53L1X sensor;

Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position

void setup()
{
  Serial.begin(115200);

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }
  
  // Use long distance mode and allow up to 50000 us (50 ms) for a measurement.
  // You can change these settings to adjust the performance of the sensor, but
  // the minimum timing budget is 20 ms for short distance mode and 33 ms for
  // medium and long distance modes. See the VL53L1X datasheet for more
  // information on range and timing limits.
  sensor.setDistanceMode(VL53L1X::Long);
  sensor.setMeasurementTimingBudget(50000);

  // Start continuous readings at a rate of one measurement every 50 ms (the
  // inter-measurement period). This period should be at least as long as the
  // timing budget.
  sensor.startContinuous(50);
}

void loop()
{
  //Serial.print(sensor.read());
 // if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

 // Serial.println();
  
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
  //  Wire.setClock(100000);
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
//     Wire.setClock(400000);
    Serial.print(" Winkel: ");
    Serial.print((int)(0.5+pos*(50.0/30.0))),
    Serial.print("°  Distanz: ");
    Serial.print(sensor.read());
    Serial.print(" mm ");
    if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

    Serial.println();
    delay(300);
    
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
 //   Wire.setClock(100000);
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);  
  //   Wire.setClock(400000);// waits 15ms for the servo to reach the position
     Serial.print(" Winkel: ");
    Serial.print((int)(0.5+pos*(50.0/30.0))),
//    Serial.print(pos);
    Serial.print("°  Distanz: ");
    Serial.print(sensor.read());
      Serial.print(" mm ");
    if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

    Serial.println();
    delay(300);
    
  }
}
