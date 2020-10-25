#ifndef LedSequence_h
#define LedSequence_h

#include <Arduino.h>

class LedSequence {
public:
  LedSequence(size_t ledCount, size_t frameCount, const uint32_t *colors, uint16_t frameDuration, bool repeat, bool copyBuffer);
  ~LedSequence();

  uint32_t ledColorForFrame(size_t frameIndex, size_t ledIndex) const;
  uint16_t durationForFrame(size_t frameIndex) const;
  size_t ledCount() const { return _ledCount; };
  size_t frameCount() const { return _frameCount; };
  bool repeat() const { return _repeat; };

private:
  size_t _ledCount;
  size_t _frameCount;
  const uint32_t *_colors;
  uint16_t _frameDuration;
  bool _repeat;
  bool _bufferCopied;
};

#endif  // LedSequence_h
