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
  Demo_default_init(ctx);
  Demo_default(ctx);

  Serial.begin(115200);
  Serial.println("I2S simple tone");

  i2s.setBitsPerSample(32);
  i2s.onTransmit(cb);
  // start I2S at the sample rate with 16-bits per sample
  if (!i2s.begin(48000)) {
    Serial.println("Failed to initialize I2S!");
  }

  // Feedback and Time of delay at 50%.
  // Demo_controlChange(ctx, 34, 64, 1);
  // Demo_controlChange(ctx, 35, 64, 1);
  
}

void loop() {

  static bool ledState;
  static uint8_t event;
  static unsigned long lastNoteOn;
  static uint8_t beatCount = 0;

  uint8_t noteIntervals[] = {0, 2, 4, 6, 7, 9, 11, 12, 14, 18, 22};
  uint8_t lydianScale[7] = {0, 2, 4, 6, 7, 9, 11};
  uint8_t noteIntervalIndex;
  unsigned long now = millis();
  if (now - lastNoteOn >= 150) {
    noteIntervalIndex = rand() % (sizeof(noteIntervals) / sizeof(uint8_t));
    ledState = !ledState;
    event = rand() % 4; // randomize note on or off
    digitalWrite(2, ledState);

    uint8_t note = 32 + lydianScale[rand() % 7];
    if (event == 0) {
      Demo_noteOn(ctx, note, 127, 1);
      Demo_noteOn(ctx, note + noteIntervals[noteIntervalIndex], 127, 1);
      Demo_controlChange(ctx, 32, rand() % 127, 1); // randomize filter frequency
      Demo_controlChange(ctx, 33, rand() % 64, 1);  // randomize resonance
    } else if (event == 1) {
      Demo_noteOff(ctx, note, 1);
      Demo_noteOff(ctx, note + noteIntervals[noteIntervalIndex], 1);
    } else if (event == 2){
      Demo_controlChange(ctx, 34, rand() % 127, 1); // randomize delay time
    } else if (event == 3){
      Demo_controlChange(ctx, 35, rand() % 80, 1);  // randomize delay feedback
    }
    lastNoteOn = now;
  }


}
