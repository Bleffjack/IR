#define IRLed 12
#define uS_TO_S_FACTOR 1000000  //Conversion factor for micro seconds to seconds
#define TIME_TO_SLEEP  5        //Time ESP32 will go to sleep (in seconds)
int nzeros = 5;
RTC_DATA_ATTR int bootCount = 0; //this variable is going to be written in the RTC memory, and it will NOT be erased in deep sleep mode

String strOne = "1000100001011011111001000000000010100011000000000000000011101011"; //10001000 01011011 11100100 00000000 10100011 00000000 00000000 11101011
String strTwo = "1000100001011011111001000000000001000010000000000000100000100110"; //10001000 01011011 11100100 00000000 01000010 00000000 00001000 00100110
String strThree = "10001000010110111110010000000000000000000001110001110100000000000000010100000000000000000110000000000110000000000000000010000011000000010000000011111101"; 
//10001000 01011011 11100100 00000000 00000000 00011100 01110100 00000000 00000101 00000000 00000000 01100000 00000110 00000000 00000000 10000011 00000001 00000000 11111101

// The ESP32 is going to execute the order one time and then go to sleep, after a precise amount of time it wakes up and restart the script frome the beginning

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(IRLed, OUTPUT);
  digitalWrite(IRLed, LOW);
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));
  start();
  first_x();
  sendfirst();
  other_x();
  sendsecond();
  other_x();
  sendthird();
  delay(500);
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) + " Seconds");
  delay(100);
  esp_deep_sleep_start();
}


// The loop is empty for the reasons above
void loop() {
}



// The IRcarrier function generates a serie of pulses that work as carrier. The IR recevier, which has a filter, interprets this signal as a electrical LOW signal. In
// other words it cuts the carrier and produces a LOW signal acting as a filter.
// The logical level LOW is interpreted as a serie of a LOW electrical signal of about 380-400 us and then a HIGH electrical signal of 400-420 us.

void IRcarrier(unsigned int IRtimemicroseconds){
  int i;
  for (i = 0; i < (IRtimemicroseconds / 26); i++){
    digitalWrite(IRLed, HIGH);
    delayMicroseconds(11);
    digitalWrite(IRLed, LOW);
    delayMicroseconds(11); 
    }
  }
void zero(){
  IRcarrier(370);
  delayMicroseconds(400);
  }
  
void spamzeros(int zeros){
  for (int j = 0; j < zeros; j++){
    zero();
    }
  }

void start(){
  spamzeros(5);
  }

void first_x(){
  IRcarrier(380);
  // delayMicroseconds(25436); non funziona con questo grande numero
  delay(25);
  IRcarrier(3200);
  delayMicroseconds(1750);
  }

void one(){
  IRcarrier(380);
  delayMicroseconds(1340);
  }

void spamones(int ones){
  for (int k = 0; k < ones; k++){
    one();
    }
  }
void sendfirst(){
  int strOne_length = strOne.length();
  for (int w = 0; w < strOne_length; w++){
    if((int)strOne.charAt(w)- 48 == 1){    // il 48 serve perchè una volta fatto il cast 1 diventa 49 e zero diventa 48
      one();
      }
    else{
      zero();
      }
  }
}

void other_x(){
  IRcarrier(380);
  // delayMicroseconds(25436); non funziona con questo grande numero
  delay(35);
  IRcarrier(3200);
  delayMicroseconds(1750);
  }

void sendsecond(){
  int strTwo_length = strTwo.length();
  for (int v = 0; v < strTwo_length; v++){
    if((int)strTwo.charAt(v)- 48 == 1){    // il 48 serve perchè una volta fatto il cast 1 diventa 49 e zero diventa 48
      one();
      }
    else{
      zero();
      }
  }
}

void sendthird(){
  int strThree_length = strThree.length();
  for (int z = 0; z < strThree_length; z++){
    if((int)strThree.charAt(z)- 48 == 1){    // il 48 serve perchè una volta fatto il cast 1 diventa 49 e zero diventa 48
      one();
      }
    else{
      zero();
      }
  }
 IRcarrier(380); 
}
