# Estação Meteorológica IoT com Arduino

Este é um projeto de uma Estação Meteorológica IoT usando Arduino, sensores DHT22, LDR, sensor de chuva e módulo WiFi ESP8266. Ele permite monitorar dados de temperatura, umidade, luminosidade e detecção de chuva em tempo real. Além disso, os dados são enviados para a plataforma ThingSpeak, onde podem ser visualizados e analisados de forma remota.

## Componentes Necessários

- Arduino board (qualquer modelo compatível)
- Sensor DHT22 (ou DHT11) para medição de temperatura e umidade
- Sensor de chuva para detecção de chuva (pode ser um módulo com saída analógica)
- Sensor de luz LDR (Light Dependent Resistor) para medição de luminosidade
- Módulo WiFi ESP8266 para conectividade com a Internet
- Display LCD 16x2 com interface I2C para exibir informações
- Jumpers e resistores conforme necessário

## Bibliotecas Necessárias

- DHT sensor library (Adafruit DHT sensor library)
- Adafruit Unified Sensor Library
- LiquidCrystal_I2C
- ESP8266WiFi
- ThingSpeak

## Conexões

1. Sensor DHT22:
   - VCC ao pino 5V do Arduino
   - GND ao pino GND do Arduino
   - Data ao pino digital 2 do Arduino

2. Sensor de Chuva:
   - VCC ao pino 5V do Arduino
   - GND ao pino GND do Arduino
   - Saída analógica ao pino A0 do Arduino

3. Sensor de Luz LDR:
   - Um lado do LDR ao pino 5V do Arduino
   - Outro lado do LDR a um resistor de 10k ohms
   - Outro lado do resistor ao pino A1 do Arduino
   - O ponto de junção do LDR e do resistor ao GND do Arduino

4. Display LCD 16x2:
   - VCC ao pino 5V do Arduino
   - GND ao pino GND do Arduino
   - SDA ao pino A4 (ou SDA) do Arduino
   - SCL ao pino A5 (ou SCL) do Arduino

5. Módulo WiFi ESP8266:
   - VCC ao pino 3.3V do Arduino
   - GND ao pino GND do Arduino
   - TX ao pino digital 3 do Arduino
   - RX ao pino digital 4 do Arduino

## Configuração e Uso

1. Certifique-se de ter todas as bibliotecas necessárias instaladas no seu ambiente Arduino IDE.

2. Conecte os componentes como mencionado nas conexões acima.

3. Abra o arquivo "estacao_meteorologica_iot.ino" neste projeto com o Arduino IDE.

4. No código, substitua as informações de `WIFI_SSID`, `WIFI_PASSWORD` e `THINGSPEAK_API_KEY` com as credenciais da sua rede WiFi e da sua conta ThingSpeak.

5. Faça o upload do código para o Arduino.

6. Abra o monitor serial para visualizar os dados lidos pelos sensores e o status da conexão WiFi.

7. As informações de temperatura, umidade, luminosidade, status da luz e detecção de chuva serão exib

idas no display LCD.

8. Os dados também serão enviados automaticamente para a plataforma ThingSpeak, onde você pode visualizá-los e analisá-los remotamente.

## Observações

- O limiar `LDR_THRESHOLD` pode ser ajustado conforme necessário para determinar a sensibilidade da detecção de luz. Esse valor pode variar dependendo do ambiente em que o sensor LDR está sendo utilizado.

- Certifique-se de ter uma conexão WiFi estável para que os dados sejam enviados corretamente para o ThingSpeak.

- O código pode ser estendido e modificado para adicionar mais sensores ou funcionalidades conforme sua necessidade.

## Aviso

Este projeto é apenas um exemplo básico e pode não abranger todas as situações ou condições de uso. Verifique se todas as conexões e componentes estão corretamente instalados e funcionando adequadamente. O autor não se responsabiliza por quaisquer danos ou prejuízos causados pelo uso deste projeto.