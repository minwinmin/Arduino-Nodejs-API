//0x90, 0xA2, 0xDA, 0x10, 0xA9, 0x8B

#include <SPI.h>
#include <Ethernet2.h>
#define SERIAL SerialUSB

// シールドのMACアドレス
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED // ここをEthernet Shieldに書いてあるMacアドレスに変更
};

// Arduinoの固定IP
IPAddress ip(192, 168, 1, 177); // ここを適当なIPアドレス（ルーター内で空いているもの）に変更

// PCのIPアドレスを入力すること
char server[] = "192.168.11.60"; // ここを適当なIPアドレス（PCのIPアドレス）に変更

// クライアント
EthernetClient client;

// CdSの値
int val  = 0;

// 使用するピン
int iPin = A0;

// POSTする間隔
int INTERVAL = 500;

bool post(int val) {
  String header = "POST /api/?val=";

  header += String(val);
  header += " HTTP/1.1";

  SERIAL.println("connecting...");

  if (client.connect(server, 3200)) {
    SERIAL.println("connected");
 
    client.println(header);
    client.println("Host: 192.168.11.60"); // PCのIPアドレス
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("User-Agent: Arduino Post Client");
    client.println("Connection: close");
    client.println();
    client.print("");
    client.stop();
    SERIAL.println("disconnecting.");
    
    return true;
  } else {
    SERIAL.println("connection failed");
   
    return false;
  }
}

void setup() {
  SERIAL.begin(115200);

  while (!SERIAL) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  if (Ethernet.begin(mac) == 0) {
    SERIAL.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }

  delay(1000);
}

void loop() {
  val = random(255);
  
  SERIAL.println(val);
  
  post(val);
  
  delay(INTERVAL);
}

