#include <I2S.h>
#include "demo.h" // Vult compiled code using  vultc -ccode -o demo -real fixed -i examples/osc -i examples/util -i examples/env demo.vult


Demo_process_type ctx;

// Create the I2S port using a PIO state machine
I2S i2s(OUTPUT);

const int sampleRate = 22050;
int32_t sample;


void cb() {
  while(i2s.availableForWrite()) {
    int16_t sample = Demo_process(ctx, 0.0);

    // write the same sample twice, once for left and once for the right channel
    i2s.write(sample);
    i2s.write(sample);
  
  }
}

void setup() {
  // Debug LED
  pinMode(2, OUTPUT);
  digitalWrite(2, 1);

  // Soft mute and de-emphasis for audio codec
  pinMode(25, OUTPUT);
  digitalWrite(25, HIGH);
  pinMode(23, OUTPUT);
  digitalWrite(23, LOW);

  // Initialize vult
  Demo_process_init(ctx);
  Demo_default_init(ctx);
  Demo_default(ctx);

  Serial.begin(115200);
  Serial.println("I2S simple tone");

  i2s.setBitsPerSample(32);
  i2s.onTransmit(cb);
  // start I2S at the sample rate with 16-bits per sample
  if (!i2s.begin(sampleRate)) {
    Serial.println("Failed to initialize I2S!");
    while (1); // do nothing
  }

}

unsigned long lastRun = 0;
bool ledState = 0;

void loop() {

    unsigned long now = millis();
    if(now - lastRun >= 1000){
      ledState != ledState;
      digitalWrite(2, ledState);
      
      uint8_t note = 40 + (rand() % 12);
      Demo_noteOn(ctx, note, 127, 1);
      lastRun = now;
    }
  
}
