#include <Encoder.h>
#include <AFMotor.h>
#include <ArduinoJson.h>

AF_DCMotor motor[4](1);
#define DEFAULT_SPEED 120

int target_steps_speed = 1;
byte motor_speed[4] {DEFAULT_SPEED,DEFAULT_SPEED,DEFAULT_SPEED,DEFAULT_SPEED};

Encoder encoder[] = {Encoder(14,20),Encoder(15,20),Encoder(16,20),Encoder(17,20)};

/*
       Motor Indexes
    "View From Bottom"
               ^ (Facing Forward)
     (1)  ___________  (2)
        0 |         | 0       
          |         |        
          |         |
          |         |
        0 |         | 0
     (3)  -----------  (4)
*/

void setup() {
  Serial.begin(9600);           
  Serial.println("Started!");
  
  for(int i = 0 ; i < 4 ; i++){
    encoder[i].Setup();
    encoder[i].setDir(1);

    motor[i] = AF_DCMotor(i+1);
    motor[i].setSpeed(DEFAULT_SPEED);
    motor[i].run(RELEASE);
    motor[i].run(FORWARD);
  }  
  stop();
}

void loop() {
  if(Serial.available() > 0){
    static StaticJsonDocument<50> json_doc;
    const auto serial_data = deserializeJson(json_doc,Serial);

    String c = json_doc["direction"]; 
    target_steps_speed = json_doc["steps_permillis"];

    if( c.equals("w")) {
      forward();
    }else
    if( c.equals("s")){
      backward();
    }else
    if( c.equals("a")){
      turn_left();
    }else
    if( c.equals("d")){
      turn_right();
    }else
    if( c.equals("p")){
      stop();
    }
  }
    forward();
}

void forward(){
  for(int i = 0 ; i < 4 ; i++){
    int i = 3;
    motor[i].setSpeed(motor_speed[i]);  
    motor[i].run(FORWARD);
  }
}
void backward(){
  for(int i = 0 ; i < 4 ; i++){
    motor[i].setSpeed(motor_speed[i]);  
    motor[i].run(BACKWARD);
  }
  
}
void turn_left(){
  for(int i = 0 ; i < 4 ; i++){
    motor[i].setSpeed(motor_speed[i]);
    if(i%2 == 0)
      motor[i].run(BACKWARD);
    else
      motor[i].run(FORWARD);
  }
}
void turn_right(){
  for(int i = 0 ; i < 4 ; i++){
    motor[i].setSpeed(motor_speed[i]);
    if(i%2 == 0)
        motor[i].run(FORWARD);
      else
        motor[i].run(BACKWARD);
  }
}

void stop(){
  for(int i = 0 ; i < 4 ; i++){
    motor[i].setSpeed(0);  
  }
}
