#include <Arduino.h>

#ifndef SongList_h
#define SongList_h

class Song;

class SongList {
public:
  SongList();
  ~SongList();

  void begin();

  const Song* songAtIndex(size_t index) const { return (index < _songCount) ? _songs[index] : NULL; };
  size_t songCount() const { return _songCount; };

private:
  void empty();

  Song **_songs;
  size_t _songCount;
};

#endif  // SongList_h
