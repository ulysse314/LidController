#ifndef LedSequenceController_h
#define LedSequenceController_h

#include <Arduino.h>

class LedSequence;
class Adafruit_NeoPixel;

class LedSequenceController {
public:
  LedSequenceController(size_t ledCount, unsigned char pin);
  ~LedSequenceController();

  void begin();
  void loop();

  void playLedSequence(const LedSequence *sequence);
  void stopPlaying();
  bool isPlaying() const { return _playingSequence != NULL; };

private:
  Adafruit_NeoPixel *_neoPixel;
  const LedSequence *_playingSequence;
  size_t _frameIndex;
  unsigned long long _nextFrameDate;
};

#endif  // LedSequenceController_h
