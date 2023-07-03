#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

// Defina os pinos para o sensor DHT22, sensor de chuva e sensor de luz LDR
#define DHTPIN 2
#define RAINDROPPIN A0
#define LDRPIN A1

// Configure o tipo de sensor DHT22 (DHT22 ou DHT11)
#define DHTTYPE DHT22

// Informações do Display LCD
#define LCD_ADDRESS 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

// Informações da rede WiFi e ThingSpeak
#define WIFI_SSID "wifi_ssid"
#define WIFI_PASSWORD "senha_wifi"
#define THINGSPEAK_API_KEY "api_key_thingspeak"

// Limiar para determinar se está claro ou escuro
#define LDR_THRESHOLD 500

// Inicializar o sensor DHT
DHT dht(DHTPIN, DHTTYPE);

// Inicializar o display LCD
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS);

// Função para ler o valor do sensor de chuva (0 - Sem chuva, 1023 - Chuva forte)
int readRainDropValue() {
  return analogRead(RAINDROPPIN);
}

void setup() {
  // Inicializar o monitor serial
  Serial.begin(9600);

  // Inicializar o sensor DHT
  dht.begin();

  // Inicializar o display LCD
  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.print("Temp: ");
  lcd.setCursor(0, 1);
  lcd.print("Umidade: ");

  // Conectar-se à rede WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando à rede WiFi...");
  }
  Serial.println("Conectado à rede WiFi!");

  // Inicializar a conexão com o ThingSpeak
  ThingSpeak.begin(WiFiClient);
}

void loop() {
  // Ler os valores do sensor DHT
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Ler o valor do sensor de chuva
  int rainValue = readRainDropValue();

  // Ler o valor do sensor de luz LDR
  int ldrValue = analogRead(LDRPIN);

  // Determinar se está claro ou escuro
  String lightStatus = (ldrValue < LDR_THRESHOLD) ? "Escuro" : "Claro";

  // Exibir os valores no monitor serial
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.print(" °C, Umidade: ");
  Serial.print(humidity);
  Serial.print("%, Valor do sensor de chuva: ");
  Serial.print(rainValue);
  Serial.print(", Luminosidade: ");
  Serial.print(ldrValue);
  Serial.print(", Status da Luz: ");
  Serial.println(lightStatus);

  // Enviar os dados para o ThingSpeak
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, rainValue);
  ThingSpeak.setField(4, ldrValue);
  ThingSpeak.setField(5, lightStatus);
  int response = ThingSpeak.writeFields(THINGSPEAK_API_KEY);

  if (response == 200) {
    Serial.println("Dados enviados para o ThingSpeak com sucesso!");
  } else {
    Serial.print("Erro ao enviar os dados para o ThingSpeak. Código de resposta HTTP: ");
    Serial.println(response);
  }

  // Obter e exibir a data e hora atual
  lcd.setCursor(0, 0);
  lcd.print("Hora: ");
  lcd.print(getFormattedTime());
  lcd.setCursor(0, 1);

  // Atualizar o display LCD com os valores lidos
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C  ");

  lcd.setCursor(0, 2);
  lcd.print("Umidade: ");
  lcd.print(humidity);
  lcd.print("%  ");

  lcd.setCursor(0, 3);
  lcd.print("Luminosidade: ");
  lcd.print(ldrValue);
  lcd.print("  ");
  lcd.print(lightStatus);

  delay(5000); // Aguardar 5 segundos para fazer a próxima leitura
}

String getFormattedTime() {
  // Obter a data e hora atual
  time_t now = time(nullptr);

  // Converter para uma string formatada (HH:MM:SS)
  char timeString[9];
  strftime(timeString, sizeof(timeString), "%H:%M:%S", localtime(&now));

  return String(timeString);
}
