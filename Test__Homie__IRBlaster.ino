/* config */
//const int IR_SEND_PIN = 5;

/* code */
#include <Homie.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

IRsend irsend(5);
int toSendI;
uint64_t toSend;
char toSendChar;

HomieNode IRNode("ir", "send");

void setupHandler() {
  IRNode.setProperty("unit").send("int");
}

bool infraredSenderSamsung(const HomieRange& range, const String& value) {  
  Serial.println(value); 
  toSend=0;
  for(toSendI=0;toSendI<value.length();toSendI++){
    Serial.print(toSendI);
    Serial.print(" : ");
    toSendChar = value.charAt(toSendI);
    Serial.println(toSendChar);
    if('0'<=toSendChar && toSendChar <='9'){
      toSend=toSend*10;
      toSend+=(toSendChar-'0');
    }
  }
  irsend.sendSAMSUNG(toSend,32,0);
}

void setup() {
  Serial.begin(115200);
  Homie_setBrand("TurtleIO");
  Serial << endl << endl;
  irsend.begin();

  Homie_setFirmware("ir-blaster", "1.0.0");

  IRNode.advertise("samsungint").settable(infraredSenderSamsung);

  Homie.setup();
}

void loop() {
  Homie.loop();
}
