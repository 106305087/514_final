#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <math.h> // For math functions

Adafruit_MPU6050 mpu;

// Define target angle and tolerance
const float targetAngle = 45.0; // Target angle in degrees
const float tolerance = 5.0; // Allowed deviation in degrees

void setup() {
  Serial.begin(115200);
  if (!mpu.begin()) {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    while (1);
  }
  Serial.println("MPU6050 initialization successful");
  
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Calculate pitch
  float pitch = atan2(-a.acceleration.x, sqrt(a.acceleration.y * a.acceleration.y + a.acceleration.z * a.acceleration.z)) * 180 / M_PI;

  // Check if the pitch angle is within the target range
  if (abs(pitch - targetAngle) <= tolerance) {
    Serial.println("Movement within target range.");
  } else {
    Serial.println("Movement outside target range.");
  }

  // Optionally, provide more feedback
  Serial.print("Current Angle: "); Serial.println(pitch);
  // Serial.print("Target Angle: "); Serial.println(targetAngle);
  // Serial.print("Tolerance: +/-"); Serial.println(tolerance);
  
  delay(1000); // Update every second
}