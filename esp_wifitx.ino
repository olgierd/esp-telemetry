#include <ESP8266WiFi.h> 

#define CHANNEL 3

void setup() {
  delay(500);
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(1); 
  Serial.begin(9600);
  wifi_set_channel(CHANNEL);
}

uint16_t c = 0;
uint8_t data[] = { 0, 0, 0, 0, 0, 0 };

uint8_t packet[128] = { 0x88, 0x00, //Frame Control 
  /*0*/   0x00, 0x00, //Duration
  /*4*/   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, //Destination address 
  /*10*/  0x58, 0x44, 0x58, 0x44, 0x30, 0x31, //Source address - overwritten later
  /*16*/  0x58, 0x44, 0x58, 0x44, 0x30, 0x31, //BSSID - overwritten to the same as the source address
  /*22*/  0xc0, 0x6c, //Seq-ctl
  /*24*/  0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00, //timestamp - the number of microseconds the AP has been active
  /*32*/  0xFF, 0x00, //Beacon interval
  /*34*/  0x01, 0x04, //Capability info
  /*36*/  0x00,
  /*37*/  0x06,     // ssid length
  /*38*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, // payload
  /*44*/  0x01, 0x08, 0x82, 0x84, 0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c, //supported rate
  /*54*/  0x03, 0x01, CHANNEL /*DSSS (Current Channel)*/ 
};

void loop() {
//  Serial.print("Sending beacon frame... "); Serial.println(c);
  data[0] = (c&0xff00) >> 8;
  data[1] = c&0xff;
  sendBeacon(data);
  c++;
}

void sendBeacon(uint8_t *data) {

  // copy data to the packet
  for(uint8_t x=0; x<6; x++) {
    packet[x+38] = data[x];
  }

  wifi_send_pkt_freedom(packet, 51+6, 0);
  delay(5);
}
