#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#include "LedSequence.h"
#include "LedSequenceController.h"
#include "LedSequenceList.h"
#include "Song.h"
#include "SongController.h"
#include "SongList.h"

#define LidAddress    0x74
#define LidVersion    1

#define NEOPIX_COUNT  4
#define NEOPIX_PIN    10

#define PIEZO_PIN     8

LedSequenceController ledSequenceController(NEOPIX_COUNT, NEOPIX_PIN);
LedSequenceList ledSequenceList;
SongController songController(PIEZO_PIN);
SongList songList;
String i2cResponse;

String processCommand(String command);

void ReceiveData(int count) {
  String command;
  for (size_t i = 0; i < count; ++i) {
    command.concat((char)Wire.read());
  }
  i2cResponse = processCommand(command);
}

void RequestData() {
  const char *response = i2cResponse.c_str();
  while (response[0]) {
    Wire.write(response[0]);
  }
  i2cResponse = "";
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Wire.begin(LidAddress);
  Wire.onReceive(ReceiveData);
  Wire.onRequest(RequestData);
  ledSequenceController.begin();
  ledSequenceList.begin();
  songController.begin();
  songList.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  ledSequenceController.playLedSequence(ledSequenceList.ledSequenceAtIndex(0));
  songController.playSong(songList.songAtIndex(0));
}

void loop() {
  songController.loop();
  ledSequenceController.loop();
  listenForSerial();
  if (Serial.available()) {
    char character = Serial.read();
    
    if (character == 's' || character == 'S') {
      ledSequenceController.stopPlaying();
    } else if (character >= '0' && character <= '2') {
      ledSequenceController.playLedSequence(ledSequenceList.ledSequenceAtIndex(character - '0'));
    }
  }
}

String processCommand(String command) {
  if (command.startsWith("PL")) {
    String index = command.substring(2);
    int ledSequenceIndex = index.toInt();
    LedSequence *ledSequence = ledSequenceList.ledSequenceAtIndex(ledSequenceIndex);
    if (ledSequence) {
      ledSequenceController.playLedSequence(ledSequence);
      return "+";
    }
    return "-";
  } else if (command.startsWith("SL")) {
    if (ledSequenceController.isPlaying()) {
      ledSequenceController.stopPlaying();
      return "+";
    }
    return "-";
  } else if (command.startsWith("PS")) {
    String index = command.substring(2);
    int songIndex = index.toInt();
    Song *song = songList.songAtIndex(songIndex);
    if (song) {
      songController.playSong(song);
      return "+";
    }
    return "-";
  } else if (command.startsWith("SS")) {
    if (songController.isPlaying()) {
      songController.stopPlaying();
      return "+";
    }
    return "-";
  } else if (command.startsWith("V")) {
    return String(LidVersion);
  }
  return "-";
}

String command;

void listenForSerial() {
  bool commandComplete = false;
  while (Serial.available()) {
    char character = Serial.read();
    if (character == '\n' || character == '\r') {
      commandComplete = true;
      break;
    }
    command.concat(character);
  }
  if (commandComplete) {
    String result = processCommand(command);
    command = "";
    Serial.println(result);
  }
}
