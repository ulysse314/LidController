#include <Arduino.h>

#ifndef LedSequenceList_h
#define LedSequenceList_h

class LedSequence;

class LedSequenceList {
public:
  LedSequenceList();
  ~LedSequenceList();

  void begin();

  const LedSequence* ledSequenceAtIndex(size_t index) const { return (index < _ledSequenceCount) ? _ledSequences[index] : NULL; };
  size_t ledSequenceCount() const { return _ledSequenceCount; };

private:
  void empty();

  const LedSequence **_ledSequences;
  size_t _ledSequenceCount;
};

#endif  // LedSequenceList_h
