#ifndef PLUMBING_H
#define PLUMBING_H
#include "everything.h"

template <typename T>
class Oscillator {
protected:
  T phase, frequency, increment;

public:
  // Default constructor & destructor
  Oscillator() : phase(0), frequency(0), increment(0) {}
  ~Oscillator() {}

  // Copy constructor
  Oscillator(const Oscillator& o) {
    this->phase = o.phase;
    this->frequency = o.frequency;
    this->increment = o.increment;
  }

  // Copy assignment operator 
  Oscillator<T>& operator=(const Oscillator<T>& o) {
    this->phase = o.phase;
    this->frequency = o.frequency;
    this->increment = o.increment;
    return *this;
  }

  virtual T operator()() {
    phase += increment;
    phase -= std::floor(phase);
    return phase;
  }

  // phase set/get
  virtual T getPhase() const { return this->phase; }
  virtual void setPhase(const T& p) { this->phase = p; }

  // frequency set/get
  virtual T getFrequency() const { return this->frequency; }
  virtual void setFrequency(const T& freq) { 
    this->frequency = freq; 
    this->increment = freq / SAMPLE_RATE;
  }
};

template <typename T>
class SinOsc : public Oscillator<T> {
public:
  SinOsc() : Oscillator<T>() {}
  ~SinOsc() {}
  T operator()() {
    return std::sin(Oscillator<T>::operator()() * 2 * M_PI);
  }
};

template <typename T>
class Impulse : public Oscillator<T> {
public:
  Impulse() : Oscillator<T>(){}
  ~Impulse() {}
  T operator()() {
    T output = 0;
    size_t harm = 1;
    Oscillator<T>::operator()();
    while (harm * this->frequency < SAMPLE_RATE / 2) {
      output += std::sin(harm * 2 * M_PI * this->phase * this->frequency);
      harm++;
    }
    output /= harm;
    return output;
  }
};

template <typename T>
class Saw : public Oscillator<T> {
public:   
  Saw() : Oscillator<T>(){}
  ~Saw() {}
  T operator()() {
    T output = 0;
    size_t harm = 1;
    Oscillator<T>::operator()();
    while (harm * this->frequency < SAMPLE_RATE / 2) {
      output += std::sin(harm * 2 * M_PI * this->phase * this->frequency) / harm;
      harm++;
    }
    output /= 2;
    return output;
  }
};

template <typename T>
class Square : public Oscillator<T> {
public:
  Square() : Oscillator<T>() {}
  ~Square() {}
  T operator()() {
    T output = 0;
    size_t harm = 1;
    Oscillator<T>::operator()();
    while (harm * this->frequency < SAMPLE_RATE / 2) {
      output += std::sin(harm * 2 * M_PI * this->phase * this->frequency) / harm;
      harm += 2;
    }
    output *= 4 / M_PI;
    return output;
  }
};

template <typename T>
class Tri : public Oscillator<T> {
public:
  Tri() : Oscillator<T>() {}
  ~Tri() {}
  T operator()() {
    T output = 0;
    size_t harm = 1;
    Oscillator<T>::operator()();
    while (harm * this->frequency < SAMPLE_RATE / 2) {
      output += std::sin(harm * 2 * M_PI * this->phase * this->frequency) * std::pow(-1, (harm - 1) / 2) / std::pow(harm, 2);
      harm += 2;
    }
    output *= 8 / std::pow(M_PI, 2);
    return output;
  }
};
#endif