#include "LedSequenceList.h"

#include "LedSequence.h"

namespace {

// Led[0] => Stern Starboard
// Led[1] => Stern Port
// Led[2] => Bow   Port
// Led[3] => Bow   Starboard

// Frame duration 100
const uint32_t startSequence[] = {
  0xFFFFFF, 0x000000, 0x000000, 0x000000,
  0x000000, 0xFFFFFF, 0x000000, 0x000000,
  0x000000, 0x000000, 0xFFFFFF, 0x000000,
  0x000000, 0x000000, 0x000000, 0xFFFFFF,
  0x000000, 0x000000, 0x000000, 0x000000,
  0x000000, 0x000000, 0x000000, 0x000000,
  0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF,
};

// Frame duration 500
const uint32_t ledSequence1[] = {
  0xFF0000, 0x00FF00, 0x000000, 0x000000,
  0x00FF00, 0xFF0000, 0x000000, 0x000000,
};

// Frame duration 1000
const uint32_t ledSequence2[] = {
  0xFF0000, 0x000000, 0x00FF00, 0x000000,
  0x000000, 0x00FF00, 0x000000, 0xFF0000,
};

}  // namespace

LedSequenceList::LedSequenceList() :
    _ledSequenceCount(0),
    _ledSequences(NULL) {
}

LedSequenceList::~LedSequenceList() {
  empty();
}

void LedSequenceList::begin() {
  empty();
  _ledSequenceCount = 2;
  _ledSequences = (LedSequence **)calloc(_ledSequenceCount, sizeof(*_ledSequences));
  _ledSequences[0] = new LedSequence(4, sizeof(startSequence) / sizeof(*startSequence) / 4, startSequence, 100, false, false);
  _ledSequences[1] = new LedSequence(4, sizeof(ledSequence1) / sizeof(*ledSequence1) / 4, ledSequence1, 500, false, false);
  _ledSequences[2] = new LedSequence(4, sizeof(ledSequence2) / sizeof(*ledSequence2) / 4, ledSequence2, 1000, true, false);
}

void LedSequenceList::empty() {
  for (size_t i = 0; i < _ledSequenceCount; i++) {
    delete _ledSequences[i];
  }
  _ledSequenceCount = 0;
  if (_ledSequences) {
    free((void *)_ledSequences);
    _ledSequences = NULL;
  }
}
