#include "SongList.h"

#include "Song.h"

namespace  {

// The badinerie, tempo 120
uint8_t startSong[] = {
  NOTE_G4,4, NOTE_G5,4, NOTE_G4,4,
};

// The badinerie, tempo 120
uint8_t badinerieNotes[] = {
  NOTE_B5,12, NOTE_D6,4, NOTE_B5,4,
    NOTE_FS5,12, NOTE_B5,4, NOTE_FS5,4, NOTE_D5,12, NOTE_FS5,4, NOTE_D5,4, NOTE_B4,16,
    NOTE_F4,4, NOTE_B4,4, NOTE_D5,4, NOTE_B4,4, NOTE_CS5,4, NOTE_B4,4, NOTE_CS5,4,
    NOTE_B4,4, NOTE_AS4,4, NOTE_CS5,4, NOTE_E5,4, NOTE_CS5,4, NOTE_D5,8, NOTE_B4,8,
};

 // The godfather, tempo 80
uint8_t godFatherNotes[] = {
  NOTE_E4,8, NOTE_A4,8, NOTE_C5,8, //1
  NOTE_B4,8, NOTE_A4,8, NOTE_C5,8, NOTE_A4,8, NOTE_B4,8, NOTE_A4,8, NOTE_F4,8, NOTE_G4,8,
  NOTE_E4,32,
};

// Imperal march, temp 120
uint8_t imperalMarchNotes[] = {
  NOTE_A4,16, NOTE_A4,16, NOTE_A4,16, NOTE_F4,12, NOTE_C5,4,
  NOTE_A4,16, NOTE_F4,12, NOTE_C5,4, NOTE_A4,32,//4
};

}  // namespace

SongList::SongList() :
    _songCount(0),
    _songs(NULL) {
}

SongList::~SongList() {
  empty();
}

void SongList::begin() {
  empty();
  _songCount = 4;
  _songs = (Song **)calloc(_songCount, sizeof(*_songs));
  _songs[0] = new Song(120, sizeof(startSong) / sizeof(*startSong), startSong, false);
  _songs[1] = new Song(120, sizeof(badinerieNotes) / sizeof(*badinerieNotes), badinerieNotes, false);
  _songs[2] = new Song(80, sizeof(godFatherNotes) / sizeof(*godFatherNotes), godFatherNotes, false);
  _songs[3] = new Song(120, sizeof(imperalMarchNotes) / sizeof(*imperalMarchNotes), imperalMarchNotes, false);
}

void SongList::empty() {
  for (size_t i = 0; i < _songCount; i++) {
    delete _songs[i];
  }
  _songCount = 0;
  if (_songs) {
    free((void *)_songs);
    _songs = NULL;
  }
}
