#ifndef SongController_h
#define SongController_h

#include <Arduino.h>

class Song;

class SongController {
public:
  SongController(unsigned char pin);
  ~SongController();

  void begin();
  void loop();

  void playSong(const Song *song);
  void stopPlaying();
  bool isPlaying() const { return _playingSong != NULL; };

private:
  unsigned char _pin;
  const Song *_playingSong;
  size_t _noteIndex;
  unsigned long long _nextNoteDate;
};

#endif  // SongController_h
