#define LED 22
#define JOYX A0
#define JOYY A1


class Joystick {
  private:
    long x; 
    long y;
    int pinx;
    int piny;
    int joymaxval;
    int joyminval;
  public:
    Joystick(int xpin,int ypin,long _joyminval, long _joymaxval) {
      x = 0;
      y = 0;
      pinx = xpin;
      piny = ypin;
      joymaxval = _joymaxval;
      joyminval = _joyminval;
    }

    long signof(long val){
      return (val > 0 ? 1 : -1);
    }


    long jmap(long val,bool oneStep) {
      long mappedVal = map(val, joyminval, joymaxval, -500, 500);

      if (abs(mappedVal) > 400) {
        return 500 * signof(mappedVal); 
      } else if (abs(mappedVal) > 100 && !oneStep) {
        return 250 * signof(mappedVal); 
      } else {
        return 0;
      }
    }


    void setup(){
      pinMode(pinx,INPUT);
      pinMode(piny,INPUT);
    }

    void readPosition() {
      x = jmap(analogRead(pinx),true);
      
      y = jmap(analogRead(piny),true);
    }

    // Method to get the X position
    long getX() {
      return x;
    }

    // Method to get the Y position
    long getY() {
      return y;
    }
};

Joystick myJoystick(A0, A1,30,1020);


void setup() {
  Serial.begin(9600);
  myJoystick.setup();
  pinMode(LED,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

long lastJoyValuex = 0;
long lastJoyValuey = 0;
long joydiffx = 0;
long joydiffy = 0;

void pollEvent(){
  myJoystick.readPosition();
  joydiffx = myJoystick.getX() - lastJoyValuex;
  joydiffy = myJoystick.getY() - lastJoyValuey;

  if (myJoystick.getX() > 0){
    joyStayUp(myJoystick);
    
  }
  if (myJoystick.getX() < 0){
    joyStayDown(myJoystick);
  }

  if (myJoystick.getY() > 0){
    joyStayLeft(myJoystick);
    
  }
  if (myJoystick.getY() < 0){
    joyStayRight(myJoystick);
  }

  if (myJoystick.getX() == 0 && myJoystick.getY() == 0){
    joyStayCenter(myJoystick);
  }

  if (joydiffx != 0){
    onJoyChange(myJoystick);
    if(joydiffx < 0){
      onJoyUp(myJoystick);
    }
    if(joydiffx > 0){
      onJoyDown(myJoystick);
    }
  }

  if (joydiffy != 0){
    onJoyChange(myJoystick);
    if(joydiffy < 0){
      onJoyLeft(myJoystick);
    }
    if(joydiffy > 0){
      onJoyRight(myJoystick);
    }
  }

  lastJoyValuex = myJoystick.getX();
  lastJoyValuey = myJoystick.getY();
}

void loop() {
  pollEvent();
  delay(10);
}

void onJoyChange(Joystick joy){
  print("change !");
}

void onJoyUp(Joystick joy){
  digitalWrite(LED_BUILTIN,joy.getX());
  print("up !");
}

void onJoyDown(Joystick joy){
  digitalWrite(LED_BUILTIN,joy.getX());
  print("down !");
}

void joyStayDown(Joystick joy){
  digitalWrite(LED,LOW);

}

void joyStayUp(Joystick joy){
  digitalWrite(LED,LOW);
}

void onJoyLeft(Joystick joy){
  digitalWrite(LED_BUILTIN,joy.getY());
  print("left !");
}

void onJoyRight(Joystick joy){
  digitalWrite(LED_BUILTIN,joy.getY());
  print("right !");
}

void joyStayRight(Joystick joy){
  digitalWrite(LED,LOW);

}

void joyStayLeft(Joystick joy){
  digitalWrite(LED,LOW);
}


void joyStayCenter(Joystick joy){
  digitalWrite(LED,HIGH);
}

template <typename T>
void print(T val) {
  Serial.println(val);
  Serial.print("\n");
}

