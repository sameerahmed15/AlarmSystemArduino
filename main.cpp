//HEADERS
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <seeed-kit.h>
bool flag=0;     //bool variable initialised

/**alarmOff*******************************************************
Checks if the password entered by the user is correct and deactivates
the alarm

* @params:   A --  a 4 digit combination of numbers that represent the
                   correct password

* @params:   B --  Password Combination entered by the user
          @prec length of A should be equal to length of B
                   
* @params:   a --  Counter for elements of the arrays

* @modifies  B -- Elements of B are assigned value of the elements
                  in the correct Password
* @returns   nothing

*****************************************************************/
void alarmOff(int A[],int B[],int a);

int main()
{

init();

digitalRead(4);   //reading the port D4
lcdInit();       //lcd initialisation
 


 while(true)
 {
   loop();
   delay(100);
   lcdClear();
   
 }

  return 0;
}
 

// test code for Grove - Sound Sensor

const int pinAdc = A0;

void setup()
{
    Serial.begin(115200);
    //Serial.println("Grove - Sound Sensor Test...");
}

void loop()
{
 
    long sum = 0;                  //sound sensor reading
    for(int i=0; i<32; i++)
    {
        sum += analogRead(pinAdc);
    }

    sum >>= 5;

    Serial.println(sum);
   
    delay(10);
   
   
    if(sum>500)
    {
      lcdPrint("ALARM ACTIVATED!");
      lcdBacklightColour(209,0,0);
      digitalRead(4);
      digitalWrite(4, HIGH);         //buzzer activated
      flag=1;
   }
    if(flag==1)
    {
      lcdPrint("ALARM ACTIVATED!");
    }
   
    int Pass[]={1,1,1,1};          //array initialisation
    int userPass[]={0,0,0,0};
    int c=0;                        
    alarmOff(Pass,userPass,c);
   
   
}


//function definition
void alarmOff(int A[],int B[],int a)    
{
 

  while(a<4)                   //a version of while loop used which is defined very similarly as typical for loops
 
    {
      int X=analogRead(A1);    //reading the X and Y coordinates of the joystick
      int Y=analogRead(A2);
   
      if(X>600 or Y>600)       //checking if the joystick moved
 
    {
      if(Y>600)                //checking if the joysick moved in the upward direction
      {
        B[a]=1;                //changing the element to 1
      }
      else if(X>1000)          //chekcing if the joystick is pressed
      {
        B[a]=1;
      }
      else
      B[a]=0;
     
    }
    a++;
    delay(200);
    }
    if(A[0]==B[0] && A[1]==B[1] && A[2]==B[2] && A[3]==B[3])    //comparing elements correct password array and the user inputted password
    {
        digitalWrite(4,LOW);                                    //switching off buzzer
        lcdClear();
        lcdPrint("   DEACTIVATED");
        lcdBacklightColour(0,235,0);
        flag=0;                                                //bool variable changed back to false
        delay(1000);
    }
}
