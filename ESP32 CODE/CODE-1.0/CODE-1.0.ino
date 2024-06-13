#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <time.h>

const char* ssid = "TIM2GLONG";
const char* password = "casa6065";

// Define o fuso horário (GMT-3 para o horário de Brasília)
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -3 * 3600;
const int daylightOffset_sec = 0;

// Servidores post e get
const char* serverName1 = "http://192.168.100.103:8080/dog/motor/estadomotor";
const char* serverName2 = "http://192.168.100.103:8080/dog/getinfo/get";
const char* serverName3 = "http://192.168.100.103:8080/dog/tempoalimentacao/gettempoalimentacao.php";

// Parâmetros da primeira alimentação
int horaAlimentacao1 = 0, minutoAlimentacao1 = 0, demosComida1 = 0;

// Parâmetros da segunda alimentação
int horaAlimentacao2 = 0, minutoAlimentacao2 = 0, demosComida2 = 0;

// Parâmetros da terceira alimentação
int horaAlimentacao3 = 0, minutoAlimentacao3 = 0, demosComida3 = 0;

// Hora e minuto atuais
int horaAtual = 0;
int minutoAtual = 0;

const int ledPin = 12;
int ledState = HIGH;

unsigned long tempoAnterior = 0;
int intervalo = 5000; // tempo de alimenção

String estado = "";
String tempo;

String obterEstado() {
  String estado = ""; // Inicializa a variável para armazenar o estado

  // Verifica a conexão WiFi
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName1);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String jsonResponse = http.getString();

      StaticJsonDocument<512> doc;
      DeserializationError error = deserializeJson(doc, jsonResponse);

      if (!error && doc.containsKey("estado")) {
        estado = doc["estado"].as<String>(); // Obtém o estado do JSON
      } else {
        Serial.println("Falha ao analisar JSON ou chave 'estado' não encontrada.");
      }
    } else {
      Serial.print("Erro na requisição HTTP: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi não conectado.");
  }

  return estado;
}

int convertsectomills(int sec){
  
  int secconvert = sec *1000;
  return secconvert; 

}



String obterTempoAlimentacao() {
  String tempo = ""; // Inicializa a variável para armazenar o tempo de alimentação

  // Verifica a conexão WiFi
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName3);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String jsonResponse = http.getString();
      Serial.println("Resposta da API: " + jsonResponse);

      StaticJsonDocument<512> doc;
      DeserializationError error = deserializeJson(doc, jsonResponse);

      if (!error) {
        // Verifica se a resposta é um array
        if (doc.is<JsonArray>()) {
          // Obtém o primeiro elemento do array
          tempo = doc[0].as<String>();
        } else {
          Serial.println("O JSON recebido não é um array.");
        }
      } else {
        Serial.print("Erro ao analisar JSON: ");
        Serial.println(error.c_str());
      }
    } else {
      Serial.print("Erro na requisição HTTP: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi não conectado.");
  }

  return tempo;
}


void getHorarios() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName2);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String jsonResponse = http.getString();

      // Parse JSON
      DynamicJsonDocument doc(1024);
      DeserializationError error = deserializeJson(doc, jsonResponse);

      if (!error) {
        if (doc.containsKey("Horario1")) {
          horaAlimentacao1 = doc["Horario1"]["hora"];
          minutoAlimentacao1 = doc["Horario1"]["minuto"];
        }
        if (doc.containsKey("Horario2")) {
          horaAlimentacao2 = doc["Horario2"]["hora"];
          minutoAlimentacao2 = doc["Horario2"]["minuto"];
        }
        if (doc.containsKey("Horario3")) {
          horaAlimentacao3 = doc["Horario3"]["hora"];
          minutoAlimentacao3 = doc["Horario3"]["minuto"];
        }
      } else {
        Serial.print("Falha ao analisar JSON: ");
        Serial.println(error.c_str());
      }
    } else {
      Serial.print("Erro na requisição HTTP: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }
}

void enviarSolicitacaoPOST() {
  // URL do servidor PHP
  String url = "http://192.168.100.103:8080/dog/motor/postestadomotor";

  // Dados a serem enviados (formatados como JSON)
  String data = "{\"estado\": 0}";

  // Inicia a comunicação com o servidor
  HTTPClient http;

  // Configuração da requisição
  http.begin(url);
  http.addHeader("Content-Type", "application/json");

  // Envia a requisição POST
  int httpResponseCode = http.POST(data);

  // Verifica se a requisição foi bem-sucedida
  if (httpResponseCode > 0) {
    String resposta = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(resposta);
  } else {
    Serial.print("Erro na requisição: ");
    Serial.println(httpResponseCode);
  }

  // Fecha a conexão com o servidor
  http.end();
}

void updateLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Falha ao obter o tempo");
    return;
  }
  // Salva a hora e o minuto em variáveis distintas
  horaAtual = timeinfo.tm_hour;
  minutoAtual = timeinfo.tm_min;
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nConectado ao WiFi");

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);



}

void loop() {
  unsigned long tempoDoPrograma = millis();
  estado = obterEstado();
  tempo = obterTempoAlimentacao();
  int tempoint = tempo.toInt();
  intervalo = convertsectomills(tempoint);

  updateLocalTime();
  getHorarios();

  if (estado == "1") {
    if ((ledState == HIGH) && (tempoDoPrograma - tempoAnterior >= intervalo)) {
      tempoAnterior = tempoDoPrograma;
      ledState = LOW;
      digitalWrite(ledPin, ledState);
    } else if ((ledState == LOW) && (tempoDoPrograma - tempoAnterior >= intervalo)) {
      tempoAnterior = tempoDoPrograma;
      ledState = HIGH;
      digitalWrite(ledPin, ledState);
      enviarSolicitacaoPOST();
    }
  }

  if (horaAtual == horaAlimentacao1 && minutoAtual == minutoAlimentacao1 && demosComida1 == 0) {
    if ((ledState == HIGH) && (tempoDoPrograma - tempoAnterior >= intervalo)) {
      tempoAnterior = tempoDoPrograma;
      ledState = LOW;
      digitalWrite(ledPin, ledState);
    } else if ((ledState == LOW) && (tempoDoPrograma - tempoAnterior >= intervalo)) {
      tempoAnterior = tempoDoPrograma;
      ledState = HIGH;
      digitalWrite(ledPin, ledState);
      demosComida1 = 1;
    }
  }

  if (horaAtual == horaAlimentacao2 && minutoAtual == minutoAlimentacao2 && demosComida2 == 0) {
    if ((ledState == HIGH) && (tempoDoPrograma - tempoAnterior >= intervalo)) {
      tempoAnterior = tempoDoPrograma;
      ledState = LOW;
      digitalWrite(ledPin, ledState);
    } else if ((ledState == LOW) && (tempoDoPrograma - tempoAnterior >= intervalo)) {
      tempoAnterior = tempoDoPrograma;
      ledState = HIGH;
      digitalWrite(ledPin, ledState);
      demosComida2 = 1;
    }
  }

  if (horaAtual == horaAlimentacao3 && minutoAtual == minutoAlimentacao3 && demosComida3 == 0) {
    if ((ledState == HIGH) && (tempoDoPrograma - tempoAnterior >= intervalo)) {
      tempoAnterior = tempoDoPrograma;
      ledState = LOW;
      digitalWrite(ledPin, ledState);
    } else if ((ledState == LOW) && (tempoDoPrograma - tempoAnterior >= intervalo)) {
      tempoAnterior = tempoDoPrograma;
      ledState = HIGH;
      digitalWrite(ledPin, ledState);
      demosComida3 = 1;
    }
  }
    Serial.print("Primeira Alimentação:");
    Serial.println(horaAlimentacao1);
    Serial.print("Seguda Alimentação:");
    Serial.println(horaAlimentacao2);
    Serial.print("Terceira Alimentação:");
    Serial.println(horaAlimentacao3);
    Serial.print("HORA ATUAL:");
    Serial.println (horaAtual);
    Serial.print ("MINUTO ATUAL:");
    Serial.println (minutoAtual);
    Serial.print ("Tempo Alimentacao:");
    Serial.println (tempo); 
    Serial.print ("Tempo Alimentacao em Mills:");
    Serial.println (intervalo); 

}
