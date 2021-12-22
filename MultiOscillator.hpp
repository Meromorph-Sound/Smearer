/*
 * MultiOscillator.hpp
 *
 *  Created on: 29 Nov 2021
 *      Author: julianporter
 */

#ifndef MULTIOSCILLATOR_HPP_
#define MULTIOSCILLATOR_HPP_

#include "base.hpp"
#include "Random.hpp"

namespace meromorph {
namespace smearer {

enum WindowType : uint32 {
	Rectangular = 1,
	Triangular = 2,
	Tanh = 3,
	Hanning = 4,
	Hamming = 5,
	Gaussian = 6
};

class Oscillator {
private:
	float32 phase;
	float32 delta;
	float32 amplitude;

public:
	Oscillator() : phase(0), delta(0), amplitude(1.0) {};
	virtual ~Oscillator() = default;
	Oscillator(const Oscillator &) = default;
	Oscillator &operator=(const Oscillator &) = default;



	void reset() { phase=0; }
	void init(const float32 d,const float32 a) { delta=d; amplitude=a; }
	void step();
	float32 operator()();
};

class OscillatorBank {
private:
	const static uint32 MaxN;

	uint32 N;
	std::vector<Oscillator> bank;
	std::vector<int32> remainder;
	Random random;
	WindowType windowType;
	float32 lower, width;
	float32 rate;

	float32 randomFreq();
	float32 window(const float32 f);

	int32 initOscillator(const uint32);

public:
	OscillatorBank() : N(1), bank(MaxN), remainder(MaxN,0), windowType(Triangular), lower(0), width(1), rate(44100) {};
	virtual ~OscillatorBank() = default;
	OscillatorBank(const OscillatorBank &) = default;
	OscillatorBank &operator=(const OscillatorBank &) = default;

	void reset();
	void initialise(const float32 lower_,const float32 upper_);
	void nOscillators(const uint32 n) { N=std::min(n,MaxN); }
	void setSampleRate(const float32);
	void setWindow(const WindowType w) { windowType=w; }

	float32 operator()();
};



} /* namespace smearer */
} /* namespace meromorph */

#endif /* MULTIOSCILLATOR_HPP_ */
