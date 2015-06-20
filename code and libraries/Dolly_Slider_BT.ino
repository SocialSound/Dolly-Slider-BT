#include <AccelStepper.h>

AccelStepper stepper1(1, 9, 8);

#define  LEFT_PIN  4
#define  STOP_PIN  3
#define  RIGHT_PIN 2

#define  SPEED_PIN 0

#define  MAX_SPEED 10000
#define  MIN_SPEED 0.1

void setup() {
              Serial1.begin(9600);
              stepper1.setMaxSpeed(10000.0);
              pinMode(LEFT_PIN, INPUT_PULLUP);
              pinMode(STOP_PIN, INPUT_PULLUP);
              pinMode(RIGHT_PIN, INPUT_PULLUP);
  
            }



void loop() {
              static float current_speed = 0.0;        
              static int analog_read_counter = 1000;    
              static char sign = 0;                     
              static int analog_value = 0;            
               String readdata; 
              
               char c = Serial1.read(); 
              readdata += c; 
  
             
              if (digitalRead(LEFT_PIN) == 0 || readdata== "Q") {
                sign = 1;
                Serial1.println("Izquierda");
              }
              else if (digitalRead(RIGHT_PIN) == 0 || readdata== "W") {    
                sign = -1;
                Serial1.println("Derecha");
              }
            
              else if (digitalRead(STOP_PIN) == 0 || readdata== "E") {
                sign = 0;
                Serial1.println("Alto");
              }

             
              if (analog_read_counter > 0) {
                analog_read_counter--;
              }
              else {
                analog_read_counter = 3000;
               
               analog_value = analogRead(SPEED_PIN);
               
                stepper1.runSpeed();
                
                current_speed = sign * ((analog_value/1023.0) * (MAX_SPEED - MIN_SPEED)) + MIN_SPEED;
                
                stepper1.setSpeed(current_speed);
              }
            
              
              stepper1.runSpeed();
           }
