#include "plumbing.h"
#include <memory>

int main(int argc, char* argv[]) {
  std::unique_ptr<Oscillator<float>> oscBank[4];
  oscBank[0] = std::make_unique<Impulse<float>>();
  oscBank[1] = std::make_unique<Saw<float>>();
  oscBank[2] = std::make_unique<Square<float>>();
  oscBank[3] = std::make_unique<Tri<float>>();

  // stable pitch (1 second at 220 Hz) 
  for (auto& osc : oscBank) {
    osc->setFrequency(220);
    for (size_t samp = 0; samp < SAMPLE_RATE; samp++) {
      mono(osc->operator()() * 0.707); // print output
    }
    
    // some silence to break them up
    for (size_t samp = 0; samp < SAMPLE_RATE/4; samp++) {
      mono(0); // print output
    }
  }

  // sweep pitch (MIDI 127 to 0)
  for (auto& osc : oscBank) {
    for (float note = 127; note > 0; note -= 0.001) { // for each note
      osc->setFrequency(mtof(note)); // mtof
      mono(osc->operator()() * 0.707); // print output
    }

    // some silence to break them up
    for (size_t samp = 0; samp < SAMPLE_RATE/4; samp++) {
      mono(0); // print output
    }
  }
  
  return 0;
}