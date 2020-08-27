#define MOEDEIRO_SINAL  2
#define NOTEIRO_SINAL   3

volatile float ValorCaptura;
volatile unsigned long time_captura_ini, time_captura_fim;
volatile bool entrada;

// interrupção do noteiro
void noteiro_int() {
    // Atualizando acumulador
    if (!digitalRead(NOTEIRO_SINAL)) {
      time_captura_ini = millis();
      entrada = true;
    } else if (entrada) {
      time_captura_fim = millis();
      entrada = false;
    
      if (time_captura_fim - time_captura_ini > 47 
       && time_captura_fim - time_captura_ini < 53) {
        ValorCaptura += 1.0;
      }
    }
}

void setup() {
  // Configurando interrupções dos sinais
  pinMode(NOTEIRO_SINAL, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(NOTEIRO_SINAL), noteiro_int, CHANGE);

  Serial.begin(9600);
  delay(50);

  time_captura_fim = millis();
  time_captura_ini = millis();

  ValorCaptura = 0.0;

  entrada = false;

}

void loop() {

  if (time_captura_fim > time_captura_ini) {

    Serial.print("Valor da captura: R$ ");
    Serial.print(ValorCaptura);
    Serial.print(" - Tempo: ");
    Serial.print(time_captura_fim - time_captura_ini);
    Serial.print(" - Tipo: ");
    Serial.println(entrada ? "ENTRADA" : "SAIDA");

    time_captura_fim = millis();
    time_captura_ini = millis();
    
  }

  

}
