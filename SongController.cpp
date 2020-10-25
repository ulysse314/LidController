#include "SongController.h"
#include "Song.h"

SongController::SongController(unsigned char pin) :
  _pin(pin),
  _playingSong(NULL),
  _noteIndex(0) {
}

SongController::~SongController() {
}

void SongController::begin() {
}

void SongController::loop() {
  unsigned long long current = millis();
  if (!_playingSong || (long long)(current - _nextNoteDate) < 0) {
    return;
  }
  // stop the waveform generation before the next note.
  noTone(_pin);

  uint16_t frequency = _playingSong->frequencyAtIndex(_noteIndex);
  uint16_t duration = _playingSong->durationAtIndex(_noteIndex);
  // we only play the note for 90% of the duration, leaving 10% as a pause
  if (frequency) {
    tone(_pin, frequency, duration*0.9);
  }

  // Wait for the specief duration before playing the next note.
  _nextNoteDate = current + duration;

  ++_noteIndex;
  if (_noteIndex == _playingSong->noteCount()) {
    _playingSong = NULL;
  }
}

void SongController::playSong(const Song *song) {
  stopPlaying();
  _noteIndex = 0;
  _playingSong = song;
  _nextNoteDate = millis();
}

void SongController::stopPlaying() {
  _playingSong = NULL;
  noTone(_pin);
}
