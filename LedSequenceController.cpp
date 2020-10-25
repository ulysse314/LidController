#include "LedSequenceController.h"

#include <Adafruit_NeoPixel.h>

#include "LedSequence.h"

LedSequenceController::LedSequenceController(size_t ledCount, unsigned char pin) :
    _neoPixel(new Adafruit_NeoPixel(ledCount, pin, NEO_GRB + NEO_KHZ800)),
    _playingSequence(NULL),
    _frameIndex(0),
    _nextFrameDate(0) {
}

LedSequenceController::~LedSequenceController() {
  delete _neoPixel;
}

void LedSequenceController::begin() {
  _neoPixel->begin();
  _neoPixel->setBrightness(255);
  _neoPixel->show(); // Initialize all pixels to 'off'
}
  
void LedSequenceController::loop() {
  unsigned long long current = millis();
  if (!_playingSequence || (long long)(current - _nextFrameDate) < 0) {
    return;
  }
  if (_frameIndex == _playingSequence->frameCount()) {
    if (!_playingSequence->repeat()) {
      stopPlaying();
      return;
    }
    _frameIndex = 0;
  }
  
  for (size_t ledIndex = 0; ledIndex < _playingSequence->ledCount(); ++ledIndex) {
    uint32_t color = _playingSequence->ledColorForFrame(_frameIndex, ledIndex);
    _neoPixel->setPixelColor(ledIndex, color);
  }
  _neoPixel->show();

  // Wait for the specief duration before playing the next frame.
  uint16_t frameDuration = _playingSequence->durationForFrame(_frameIndex);
  _nextFrameDate = current + frameDuration;

  ++_frameIndex;
}

void LedSequenceController::playLedSequence(const LedSequence *sequence) {
  stopPlaying();
  _frameIndex = 0;
  _nextFrameDate = millis();
  _playingSequence = sequence;
}

void LedSequenceController::stopPlaying() {
  for (size_t ledIndex = 0; ledIndex < _playingSequence->ledCount(); ++ledIndex) {
    _neoPixel->setPixelColor(ledIndex, 0);
  }
  _neoPixel->show();
  _playingSequence = NULL;
}
