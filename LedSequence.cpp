#include "LedSequence.h"

LedSequence::LedSequence(size_t ledCount, size_t frameCount, const uint32_t *colors, uint16_t frameDuration, bool repeat, bool copyBuffer) :
    _ledCount(ledCount),
    _frameCount(frameCount),
    _frameDuration(frameDuration),
    _repeat(repeat),
    _bufferCopied(copyBuffer) {
  if (!_bufferCopied) {
    _colors = colors;
  } else {
    size_t bufferSize = sizeof(*colors) * _ledCount * _frameCount;
    _colors = (uint32_t *)malloc(bufferSize);
    memcpy((void *)_colors, (void *)colors, bufferSize);
  }
}

LedSequence::~LedSequence() {
  if (_bufferCopied) {
    free((void *)_colors);
  }
}

uint32_t LedSequence::ledColorForFrame(size_t frameIndex, size_t ledIndex) const {
  return _colors[frameIndex * _ledCount + ledIndex];
}

uint16_t LedSequence::durationForFrame(size_t) const {
  return _frameDuration;
}
