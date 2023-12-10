#define enA 10//Enable1 L298 Pin enA 
#define in1 9 //Motor1  L298 Pin in1 
#define in2 8 //Motor1  L298 Pin in1 
#define in4 7 //Motor2  L298 Pin in1 
#define in3 6 //Motor2  L298 Pin in1 
#define enB 5 //Enable2 L298 Pin enB              


#define L_S A0                     //ir sensor Left
#define R_S A1                      //ir sensor Right

const int echoPin = A5;
const int pingPin = A4;

long duration=0;

void setup(){ 

    Serial.begin(9600);     

    pinMode(R_S, INPUT); 
    pinMode(L_S, INPUT); 
  
    pinMode(echoPin, INPUT); 
    pinMode(pingPin, OUTPUT);

    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT); 
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(enB, OUTPUT); 

    analogWrite(enA, 65); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
    analogWrite(enB,65);     

}
long inches, cm; 
    
void loop(){ 
  // digitalWrite(in1, HIGH); //Left Motor backword Pin 
  // digitalWrite(in2, LOW); //Left Motor forword Pin 
  // digitalWrite(in3, HIGH); //Right Motor forword Pin 
  // digitalWrite(in4, LOW); 
  // delay(50);
 

   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   duration = pulseIn(echoPin, HIGH);

   inches = ( duration / 2) / 29.1;

  Serial.print("in, ");
  Serial.println(inches); 
   
   Serial.print(digitalRead(L_S));
     Serial.print(" ");
   Serial.println(digitalRead(R_S));
   
  
  if(inches >= 5 ){             //inches >= 3 
      followline();
  }
  else{  
     stop();
     Serial.println("obstacle detected ");  
     Serial.println(inches);  
     delay(5000);
  }

}

void followline(){
  Serial.println("follow");  
  
        if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 0))
        {
            Serial.println("forward "); 
            forward();
        }   
        else{
          if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 0))
          {  
              // Serial.print("left ");    
              Serial.println("right ");                          
              turnRight(); 
          }  

          if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 1))
          {     
              Serial.println("left ");                              
              turnLeft(); 
          } 
           
        }
        if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 1))
          {  
              // Serial.print("left ");    
              Serial.println("stop ");                          
              stop();
          } 

        
}
void forward(){  
  digitalWrite(in1, HIGH); //Left Motor backword Pin 
  digitalWrite(in2, LOW); //Left Motor forword Pin 
  digitalWrite(in3, HIGH); //Right Motor forword Pin 
  digitalWrite(in4, LOW); 
}


void turnRight(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);                //////turnRight
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW);
}
void turnLeft(){ 
  digitalWrite(in1, HIGH); //Left Motor backword Pin 
  digitalWrite(in2, LOW); //Left Motor forword Pin 
  digitalWrite(in3, LOW); //Right Motor forword Pin 
  digitalWrite(in4, HIGH);
}
void stop(){ 
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW);              /////////stop
  digitalWrite(in4, LOW);
}