#include <driver/i2s_pdm.h>

// ======== CONFIGURACION DE AUDIO ========
#define SAMPLE_RATE 48000
#define BUFFER_LEN 512

// ======== GANANCIA PDM ========
#define DEFAULT_AUDIO_GAIN_PERCENT 100
#define MIN_AUDIO_GAIN_PERCENT 50
#define MAX_AUDIO_GAIN_PERCENT 800

// ======== COMANDOS SERIALES ========
#define RAW_START_COMMAND 'R'
#define GAIN_COMMAND 'G'
#define SERIAL_WRITE_TIMEOUT_MS 20

// ======== PINES PDM ========
#define PDM_CLK_PIN  2
#define PDM_DATA_PIN 3

// PDM slot: LEFT o RIGHT según pin SEL del micrófono
// Si audio con ruido, prueba I2S_PDM_SLOT_RIGHT
#define PDM_MIC_SLOT I2S_PDM_SLOT_LEFT

// ======== VARIABLES GLOBALES ========
i2s_chan_handle_t rx_handle;
int16_t audioBuffer[BUFFER_LEN];
uint16_t audioGainPercent = DEFAULT_AUDIO_GAIN_PERCENT;
uint16_t pendingGainPercent = 0;
bool parsingGainCommand = false;
bool gainCommandHasDigit = false;

void send_raw_header() {
  Serial.println("RAW");
  Serial.flush();
  delay(100);
}

void apply_gain(int16_t *buffer, int samples) {
  if (audioGainPercent == 100) {
    return;
  }

  for (int i = 0; i < samples; i++) {
    int32_t sample = ((int32_t)buffer[i] * audioGainPercent) / 100;

    if (sample > 32767) {
      sample = 32767;
    } else if (sample < -32768) {
      sample = -32768;
    }

    buffer[i] = (int16_t)sample;
  }
}

void commit_pending_gain() {
  if (gainCommandHasDigit) {
    if (pendingGainPercent < MIN_AUDIO_GAIN_PERCENT) {
      pendingGainPercent = MIN_AUDIO_GAIN_PERCENT;
    } else if (pendingGainPercent > MAX_AUDIO_GAIN_PERCENT) {
      pendingGainPercent = MAX_AUDIO_GAIN_PERCENT;
    }
    audioGainPercent = pendingGainPercent;
  }

  pendingGainPercent = 0;
  parsingGainCommand = false;
  gainCommandHasDigit = false;
}

void process_serial_command(char command) {
  if (command == RAW_START_COMMAND) {
    send_raw_header();
  } else if (command == GAIN_COMMAND) {
    parsingGainCommand = true;
    pendingGainPercent = 0;
    gainCommandHasDigit = false;
  }
}

void handle_serial_commands() {
  while (Serial.available() > 0) {
    char command = Serial.read();

    // Ignorar whitespace y finalizar comando de ganancia
    if (command == '\n' || command == '\r' || command == ' ' || command == '\t') {
      if (parsingGainCommand) {
        commit_pending_gain();
      }
      continue;
    }

    if (parsingGainCommand) {
      if (command >= '0' && command <= '9') {
        gainCommandHasDigit = true;
        pendingGainPercent = (pendingGainPercent * 10) + (command - '0');
        if (pendingGainPercent > MAX_AUDIO_GAIN_PERCENT) {
          pendingGainPercent = MAX_AUDIO_GAIN_PERCENT;
        }
      } else {
        commit_pending_gain();
        process_serial_command(command);
      }
    } else {
      process_serial_command(command);
    }
  }
}



void setup() {
  Serial.begin(2000000);
  delay(1000);

  // Crear canal RX
  i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(
      I2S_NUM_0,
      I2S_ROLE_MASTER);

  esp_err_t err = i2s_new_channel(&chan_cfg, NULL, &rx_handle);
  if (err != ESP_OK) {
    Serial.println("ERROR: No se pudo crear canal I2S");
    delay(5000);
    ESP.restart();
  }

  // Configuración PDM para 48kHz
  i2s_pdm_rx_config_t pdm_cfg = {
      .clk_cfg = I2S_PDM_RX_CLK_DEFAULT_CONFIG(SAMPLE_RATE),
      .slot_cfg = {
          .data_bit_width = I2S_DATA_BIT_WIDTH_16BIT,
          .slot_bit_width = I2S_SLOT_BIT_WIDTH_AUTO,
          .slot_mode = I2S_SLOT_MODE_MONO,
          .slot_mask = PDM_MIC_SLOT,
      },
      .gpio_cfg = {
          .clk = (gpio_num_t)PDM_CLK_PIN,
          .din = (gpio_num_t)PDM_DATA_PIN,
          .invert_flags = {
              .clk_inv = false,
          },
      },
  };

  err = i2s_channel_init_pdm_rx_mode(rx_handle, &pdm_cfg);
  if (err != ESP_OK) {
    Serial.println("ERROR: No se pudo inicializar modo PDM");
    delay(5000);
    ESP.restart();
  }
  
  err = i2s_channel_enable(rx_handle);
  if (err != ESP_OK) {
    Serial.println("ERROR: No se pudo habilitar canal");
    delay(5000);
    ESP.restart();
  }

  send_raw_header();
}

void loop() {
  // Procesar comandos seriales ANTES de leer audio
  handle_serial_commands();

  size_t bytes_read = 0;

  // Timeout corto (10ms) para permitir procesar comandos frecuentemente
  esp_err_t err = i2s_channel_read(
          rx_handle,
          audioBuffer,
          sizeof(audioBuffer),
          &bytes_read,
          pdMS_TO_TICKS(10));
  
  if (err == ESP_OK && bytes_read > 0) {
    int samples = bytes_read / sizeof(int16_t);
    apply_gain(audioBuffer, samples);
    
    // Enviar datos binarios
    size_t data_size = samples * sizeof(int16_t);
    Serial.write((uint8_t*)audioBuffer, data_size);
  }
  
  // Procesar comandos seriales DESPUES de enviar audio también
  handle_serial_commands();
  
  // Alimentar watchdog
  yield();
}