#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
/* Set these to your desired credentials. */
const char *ssid = “wifiRC”;
const char *password = “11111111”;

ESP8266WebServer server(80);

String form ="<html><head><meta name=viewport content=width=100></head><body>

<form action=FD class='btn-square left-right'><input type=submit value=FORWARD></form><form action=TL class='btn-square'><input type=submit value=LEFT></form><form action=TR class='btn-square'><input type=submit value=RIGHT></form><form action=BK class='btn-square left-right'><input type=submit value=BACK></form>
<form action=ST class='btn-square'><input type=submit value=STOP></form>
/* Just a little test message. Go to http://192.168.4.1 in a web browser

connected to this access point to see it.
/
/ void handleRoot() {
server.send(200, “text/html”, “
You are connected
”);
} */
/* プロトタイプ宣言 */
void handleRoot();
void handle_stop();
void handle_forward();
void handle_turn_left();
void handle_turn_right();
void handle_back();
void ST_ACT();
void FD_ACT();
void TL_ACT();
void TR_ACT();
void BK_ACT();

void setup() {
delay(1000);
Serial.begin(115200);
Serial.println();
Serial.print(“Configuring access point…”);
/* You can remove the password parameter if you want the AP to be open. */
WiFi.softAP(ssid, password);

IPAddress myIP = WiFi.softAPIP();
Serial.print("AP IP address: ");
Serial.println(myIP);
server.on("/", handleRoot);
/* 各アクション時のハンドル設定 */
server.on("/ST", handle_stop);
server.on("/FD", handle_forward);
server.on("/TL", handle_turn_left);
server.on("/TR", handle_turn_right);
server.on("/BK", handle_back);

server.begin();
Serial.println("HTTP server started");
pinMode(12, OUTPUT); // 出力ピンの設定
pinMode(13, OUTPUT);
pinMode(14, OUTPUT);
pinMode(16, OUTPUT);
digitalWrite(12,LOW); // 最初はストップから
digitalWrite(13,LOW);
digitalWrite(14,LOW);
digitalWrite(16,LOW);
Serial.println(“STOP”);
}

void loop() {
server.handleClient();
}

/------ ここから下は全て新しく追加するプログラムです ----------/
/* 各ハンドルの内容記述 /
/ ハンドル初期状態の記述 /
void handleRoot() {
server.send(200, “text/html”, form);
}
/ ストップハンドルの記述 /
void handle_stop() {
Serial.println(“STOP”);
ST_ACT();
server.send(200, “text/html”, form);
}
/ 前進ハンドルの記述 /
void handle_forward() {
Serial.println(“FORWARD”);
FD_ACT();
server.send(200, “text/html”, form);
}
/ 左折ハンドルの記述 /
void handle_turn_left() {
Serial.println(“LEFT”);
TL_ACT();
server.send(200, “text/html”, form);
}
/ 右折ハンドルの記述 /
void handle_turn_right() {
Serial.println(“RIGHT”);
TR_ACT();
server.send(200, “text/html”, form);
}
/ バックハンドルの記述 /
void handle_back() {
Serial.println(“BACK”);
BK_ACT();
server.send(200, “text/html”, form);
}
/-------------- 各ハンドル記述内の関数内容 ------------------/
/ ストップの関数 /
void ST_ACT(){
digitalWrite(12,LOW);
digitalWrite(13,LOW);
digitalWrite(14,LOW);
digitalWrite(16,LOW);
}
/ 前進の関数 /
void FD_ACT(){
digitalWrite(12,LOW);
digitalWrite(13,HIGH);
digitalWrite(14,HIGH);
digitalWrite(16,LOW);
}
/ OK 左折の関数 */
void TL_ACT(){
digitalWrite(12,LOW);
digitalWrite(13,HIGH);
digitalWrite(14,LOW);
digitalWrite(16,LOW);
}

/* OK 右折の関数 /
void TR_ACT(){
digitalWrite(12,LOW);
digitalWrite(13,LOW);
digitalWrite(14,HIGH);
digitalWrite(16,LOW);
}
/ バックの関数 */
void BK_ACT(){
digitalWrite(12,HIGH);
digitalWrite(13,LOW);
digitalWrite(14,LOW);
digitalWrite(16,HIGH);
}
