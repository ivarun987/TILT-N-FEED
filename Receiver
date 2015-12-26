#include <SPI.h>
#include <Servo.h>
#include <Ethernet.h>
#include <SoftwareSerial.h>
#include <SoftReset.h>

unsigned int localPort = 8888; //local port to listen UDP packets
char timeServer[] = "time.nist.gov"; 
const int NTP_PACKET_SIZE = 48;
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets
EthernetUDP Udp;

//RX TX bluetooth module digital pins
SoftwareSerial  BTSerial(2, 3);

// Local Network Settings
// Must be unique on local network
byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0xD2, 0xC6};  
// you must change this
IPAddress ip(192, 168, 1, 109); 

// ThingSpeak Settings
char thingSpeakAddress[] = "api.thingspeak.com";
// you must change this
String writeAPIKey = "3CDPP6MET80GNVNZ"; 
//Delay time to next possible shake
int updateThingSpeakInterval = 2000;

// Initialize Arduino Ethernet Client
EthernetClient client;

//Initialize the servo motor
Servo motor;

void setup() {
  BTSerial.begin(9600); //begin bluetooth communication
  Serial.begin(9600); //begin serial communication
  // Start Ethernet on Arduino
  client.stop();
  Ethernet.begin(mac, ip);
  motor.attach(8);
  motor.write(92);
  Udp.begin(localPort);
}

void loop() {
  if (BTSerial.available()) {
    //reads single character at a time
    char inChar = (char) BTSerial.read();
    if(inChar == 'H') {
      motor.write(85); //Change this speed to be reasonable 
      delay(500); //Change this delay to be reasonable
      motor.write(92); //Stop motor
      // Update ThingSpeak
      int time = getTime();
      if (time < 5) {
        time = 19 +  time;
      } else {
        time = time - 5;
      }
      updateThingSpeak("field1="+String(time));
      soft_restart();
    }
  }
}

void updateThingSpeak(String tsData) {
  if (client.connect(thingSpeakAddress,80)) {  
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(tsData.length());
    client.print("\n\n");
    client.print(tsData);
    Serial.println("Updated thingspeak: " + tsData);
    delay(1000);
  }
}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(char* address) {
  Serial.println("sending packet");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}


int getTime() {
  Serial.println("getting time");
  sendNTPpacket(timeServer); // send an NTP packet to a time server

  // wait to see if a reply is available
  delay(1000);
  if (Udp.parsePacket()) {
    Serial.println("packet parsed");
    // We've received a packet, read the data from it
    Udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    // the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, extract the two words:

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    Serial.print("Seconds since Jan 1 1900 = ");
    Serial.println(secsSince1900);

    // now convert NTP time into everyday time:
    Serial.print("Unix time = ");
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears;
    // print Unix time:
    Serial.println(epoch);

    Serial.println("The UTC time is ");       // UTC is the time at Greenwich Meridian (GMT)
    int hour = (epoch  % 86400L) / 3600;
    Serial.print(hour); // print the hour (86400 equals secs per day)
    return hour;
  }
}
