#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

const char* ssid = "DESKTOPBruno";
const char* password = "BbbbbbbB";
//DESKTOPBruno
//dlink-EF64
//BbbbbbbB
//Residência Soares
//3897476531
String motor;
String direção;
Servo myservo;
int pos;
int velocidade = 10;

ESP8266WebServer server(80);

void handleDataMotor() {
  if (server.hasArg("motor")) {
    motor = server.arg("motor");
    // Faça algo com o valor recebido
    Serial.println(motor);

    server.sendHeader("Access-Control-Allow-Origin", "*");  // Permitir acesso de qualquer origem

    server.send(200, "text/plain", "OK");
  } else {
    server.send(400, "text/plain", "Erro: Valor não fornecido");
  }
}
void handleDataDirecao() {
  if (server.hasArg("direcao")) {
    direção = server.arg("direcao");
    // Faça algo com o valor recebido
    Serial.println(direção);

    server.sendHeader("Access-Control-Allow-Origin", "*");  // Permitir acesso de qualquer origem

    server.send(200, "text/plain", "OK");
  } else {
    server.send(400, "text/plain", "Erro: Valor não fornecido");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao Wi-Fi...");
  }

  Serial.println("Conectado ao Wi-Fi");

  server.on("/motor", handleDataMotor);
  server.on("/direcao", handleDataDirecao);
  server.begin();
  Serial.println("Servidor iniciado");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //-------------------------------------//
  pinMode(LED_BUILTIN, OUTPUT);
  myservo.attach(2); // D4
  pinMode(5, OUTPUT); // D1
  pinMode(4, OUTPUT); // D2
}

void loop() {
  server.handleClient();
  while (motor == "e") {
    digitalWrite(5, HIGH);
    delay(10);
    Serial.println("Valor recebido: " + motor);
    server.handleClient();
  }
  while (motor == "d") {
    digitalWrite(4, HIGH);
    delay(10);
    Serial.println("Valor recebido: " + motor);
    server.handleClient();
  }
  while (motor == "c") {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(10);
    Serial.println("Valor recebido: " + motor);
    server.handleClient();
  }
  while (direção == "e") {
    if (pos <= 180)
      pos += velocidade;  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);  // tell servo to go to position in variable 'pos'
    delay(10);           // waits 15ms for the servo to reach the position
    Serial.println("Valor recebido: " + direção + " velocidade: " + pos);
    server.handleClient();
  }
  while (direção == "d") {
    if (pos >= 0)
      pos -= velocidade;  // goes from 180 degrees to 0 degrees
    myservo.write(pos);   // tell servo to go to position in variable 'pos'
    delay(10);            // waits 15ms for the servo to reach the position
    Serial.println("Valor recebido: " + direção + " velocidade: " + pos);
    server.handleClient();
  }
  while (direção == "c") {
    if (pos <= 90)
      pos += velocidade;
    if (pos >= 90)
      pos -= velocidade;
    myservo.write(pos);
    delay(10);
    server.handleClient();
  }
}