#include <Arduino.h>
#include <FastLED.h>

const uint8_t NUM_LEDS = 1;
const gpio_num_t DATA_PIN = GPIO_NUM_48;

CRGB leds[NUM_LEDS];

void prettyPrintBytes(size_t bytes) {
  if (bytes < 1024) {
    Serial.printf("%d b\n", bytes);
  } else if (bytes < (1024 * 1024)) {
    Serial.printf("%.2f kb\n", bytes / 1024.0);
  } else {
    Serial.printf("%.2f mb\n", bytes / (1024.0 * 1024));
  }
}

// clang-format off
void printESPInfo() {
  Serial.println("ESP32-S3 info");
  Serial.println("Internal RAM");
  Serial.print("  getHeapSize: "); prettyPrintBytes(ESP.getHeapSize());
  Serial.print("  getFreeHeap: "); prettyPrintBytes(ESP.getFreeHeap());
  Serial.print("  getMinFreeHeap: "); prettyPrintBytes(ESP.getMinFreeHeap());
  Serial.print("  getMaxAllocHeap: "); prettyPrintBytes(ESP.getMaxAllocHeap());
  Serial.println("PSRAM");
  Serial.print("  getPsramSize: "); prettyPrintBytes(ESP.getPsramSize());
  Serial.print("  getFreePsram: "); prettyPrintBytes(ESP.getFreePsram());
  Serial.print("  getMinFreePsram: "); prettyPrintBytes(ESP.getMinFreePsram());
  Serial.print("  getMaxAllocPsram: "); prettyPrintBytes(ESP.getMaxAllocPsram());
  Serial.println("Flash");
  Serial.print("  getFlashChipSize: "); prettyPrintBytes(ESP.getFlashChipSize());
  Serial.printf("  getFlashChipSpeed: %d MHz\n", ESP.getFlashChipSpeed() / 1000 / 1000);
  // ESP.getFlashChipMode() on the ESP32-S3 crashes the CPU
  Serial.print("  getFlashChipMode: "); Serial.println("SKIPPED");
//  switch (ESP.getFlashChipMode()) {
//    case FM_QIO:
//      Serial.println("QIO");
//      break;
//    case FM_QOUT:
//      Serial.println("QOUT");
//      break;
//    case FM_DIO:
//      Serial.println("DIO");
//      break;
//    case FM_DOUT:
//      Serial.println("DOUT");
//      break;
//    case FM_FAST_READ:
//      Serial.println("FAST_READ");
//      break;
//    case FM_SLOW_READ:
//      Serial.println("SLOW_READ");
//      break;
//    case FM_UNKNOWN:
//      Serial.println("UNKNOWN");
//      break;
//    default:
//      Serial.println("???");
//      break;
//  }
  Serial.println("CPU");
  Serial.printf("  getChipRevision: %d\n", ESP.getChipRevision());
  Serial.printf("  getChipModel: %s\n", ESP.getChipModel());
  Serial.printf("  getChipCores: %d\n", ESP.getChipCores());
  Serial.printf("  getCpuFreqMHz: %d\n", ESP.getCpuFreqMHz());
  Serial.printf("  getEfuseMac: %llX\n", ESP.getEfuseMac());
  Serial.println("Software");
  Serial.printf("  getSdkVersion: %s\n", ESP.getSdkVersion());
  Serial.print("  getSketchSize: "); prettyPrintBytes(ESP.getSketchSize());
  Serial.printf("  getFreeSketchSpace: %d kb\n", ESP.getFreeSketchSpace() / 1024);
  Serial.printf("  getSketchMD5: %s\n", ESP.getSketchMD5().c_str());
}
// clang-format on

void setup() {
  Serial.begin(115200);
  // WS2818 is compatible with WS2811 but uses GRB
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(32);

  delay(1000);
  printESPInfo();
  
}

void loop() {
  while (true) {
    leds[0] = CRGB::Red;
    FastLED.delay(500);
    leds[0] = CRGB::Green;
    FastLED.delay(500);
    leds[0] = CRGB::Blue;
    FastLED.delay(500);
    leds[0] = CRGB::Black;
    FastLED.delay(500);
  }
}
