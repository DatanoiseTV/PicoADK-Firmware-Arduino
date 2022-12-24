#include <I2S.h>
#include "demo.h" // Vult compiled code using  vultc -ccode -o demo -real fixed -i examples/osc -i examples/util -i examples/env demo.vult


Demo_process_type ctx;

// Create the I2S port using a PIO state machine
I2S i2s(OUTPUT);

int32_t sample;

int32_t fix16_to_int32(fix16_t x)
{
  fix16_t out;
  if (x >= int_to_fix(1))
    out = int_to_fix(1) - 1;
  else if (x <= int_to_fix(-1))
    out = int_to_fix(-1) + 1;
  else
    out = x;
  return out << 15u;
}

void cb() {
  while (i2s.availableForWrite()) {
    fix16_t smp = Demo_process(ctx, 0.0);
    // write the same sample twice, once for left and once for the right channel
    i2s.write(fix16_to_int32(smp));
    i2s.write(fix16_to_int32(smp));

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
//  Demo_default_init(ctx);
//  Demo_default(ctx);

  Serial.begin(115200);
  Serial.println("I2S simple tone");

  i2s.setBitsPerSample(32);
  i2s.onTransmit(cb);
  // start I2S at the sample rate with 16-bits per sample
  if (!i2s.begin(44100)) {
    Serial.println("Failed to initialize I2S!");
  }

}

void loop() {

  static bool ledState, event;
  static unsigned long lastNoteOn;

  unsigned long now = millis();
  if (now - lastNoteOn >= 250) {
    ledState = !ledState;
    event = rand() % 2;
    digitalWrite(2, ledState);

    uint8_t note = 32 + (rand() % 12);
    if (event) {
      Demo_noteOn(ctx, note, 127, 1);
      Demo_noteOn(ctx, note+16, 127, 1);
      Demo_controlChange(ctx, 33, rand() % 127, 1);
    } else {
      Demo_noteOff(ctx, note, 1);
    }
    lastNoteOn = now;
  }


}
