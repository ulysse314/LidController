#ifndef Song_h
#define Song_h

#include <Arduino.h>

#define NOTE_C1  0x10
#define NOTE_CS1 0x11
#define NOTE_D1  0x12
#define NOTE_DS1 0x13
#define NOTE_E1  0x14
#define NOTE_F1  0x15
#define NOTE_FS1 0x16
#define NOTE_G1  0x17
#define NOTE_GS1 0x18
#define NOTE_A1  0x19
#define NOTE_AS1 0x1A
#define NOTE_B1  0x1B
#define NOTE_C2  0x20
#define NOTE_CS2 0x21
#define NOTE_D2  0x22
#define NOTE_DS2 0x23
#define NOTE_E2  0x24
#define NOTE_F2  0x25
#define NOTE_FS2 0x26
#define NOTE_G2  0x27
#define NOTE_GS2 0x28
#define NOTE_A2  0x29
#define NOTE_AS2 0x2A
#define NOTE_B2  0x2B
#define NOTE_C3  0x30
#define NOTE_CS3 0x31
#define NOTE_D3  0x32
#define NOTE_DS3 0x33
#define NOTE_E3  0x34
#define NOTE_F3  0x35
#define NOTE_FS3 0x36
#define NOTE_G3  0x37
#define NOTE_GS3 0x38
#define NOTE_A3  0x39
#define NOTE_AS3 0x3A
#define NOTE_B3  0x3B
#define NOTE_C4  0x40
#define NOTE_CS4 0x41
#define NOTE_D4  0x42
#define NOTE_DS4 0x43
#define NOTE_E4  0x44
#define NOTE_F4  0x45
#define NOTE_FS4 0x46
#define NOTE_G4  0x47
#define NOTE_GS4 0x48
#define NOTE_A4  0x49
#define NOTE_AS4 0x4A
#define NOTE_B4  0x4B
#define NOTE_C5  0x50
#define NOTE_CS5 0x51
#define NOTE_D5  0x52
#define NOTE_DS5 0x53
#define NOTE_E5  0x54
#define NOTE_F5  0x55
#define NOTE_FS5 0x56
#define NOTE_G5  0x57
#define NOTE_GS5 0x58
#define NOTE_A5  0x59
#define NOTE_AS5 0x5A
#define NOTE_B5  0x5B
#define NOTE_C6  0x60
#define NOTE_CS6 0x61
#define NOTE_D6  0x62
#define NOTE_DS6 0x63
#define NOTE_E6  0x64
#define NOTE_F6  0x65
#define NOTE_FS6 0x66
#define NOTE_G6  0x67
#define NOTE_GS6 0x68
#define NOTE_A6  0x69
#define NOTE_AS6 0x6A
#define NOTE_B6  0x6B
#define NOTE_C7  0X70
#define NOTE_CS7 0x71
#define NOTE_D7  0x72
#define NOTE_DS7 0x73
#define NOTE_E7  0x74
#define NOTE_F7  0x75
#define NOTE_FS7 0x76
#define NOTE_G7  0x77
#define NOTE_GS7 0x78
#define NOTE_A7  0x79
#define NOTE_AS7 0x7A
#define NOTE_B7  0x7B
#define NOTE_C8  0x80
#define NOTE_CS8 0x81
#define NOTE_D8  0x82
#define NOTE_DS8 0x83
#define REST     0

class Song {
public:
  using Frequency = uint16_t;
  using Duration = uint8_t;
  using Tempo = uint16_t;

  Song(Tempo tempo, size_t noteCount, const uint8_t *notes, bool copyBuffer);
  ~Song();
 
  uint16_t tempo() const { return _tempo; };
  size_t noteCount() const { return _noteCount; };
  uint16_t frequencyAtIndex(size_t index) const;
  uint16_t durationAtIndex(size_t index) const;

private:
  Tempo _tempo;
  size_t _noteCount;
  bool _bufferCopied;
  const uint8_t *_notes;
};

#endif  // Song_h
