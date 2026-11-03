// UE0148: read the default RIGHT PDM channel on an ESP32-S3.
// Requires the DevLab_AudioInput library and Arduino-ESP32 3.x.
#if !defined(CONFIG_IDF_TARGET_ESP32S3)
#error "This example uses the ESP32-S3 PDM-to-PCM peripheral."
#endif
#include <DevLab_AudioInput.h>

DevLab_AudioInput microphone;
int16_t samples[256];

void setup() {
  Serial.begin(115200);
  if (!microphone.beginPDM(GPIO_NUM_2, GPIO_NUM_3, 48000,
                           I2S_PDM_SLOT_RIGHT)) {
    Serial.println("PDM initialization failed");
    while (true) delay(1000);
  }
  delay(25);  // Allow the ICS-41350 to settle after clock start.
}

void loop() {
  size_t count = microphone.read(samples, 256);
  if (count == 0) return;

  int32_t peak = 0;
  for (size_t i = 0; i < count; ++i) {
    int32_t value = samples[i];
    if (value < 0) value = -value;
    if (value > peak) peak = value;
  }
  Serial.println(peak);
}
