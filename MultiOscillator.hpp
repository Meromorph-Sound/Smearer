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
	Oscillator(const float32 phi0) : phase(phi0), delta(0), amplitude(1) {};
	Oscillator() : Oscillator(0) {};
	virtual ~Oscillator() = default;
	Oscillator(const Oscillator &) = default;
	Oscillator &operator=(const Oscillator &) = default;



	void reset(const float32 phi0 = 0) { phase=phi0; }
	void jitter(const float32 j=0.01) { phase+=j; }
	void init(const float32 d,const float32 a) { delta=d; amplitude=a; }
	void step();
	float32 value();
};

class OscillatorBank {
private:
	const static uint32 MaxN;

	uint32 N;
	std::vector<std::shared_ptr<Oscillator>> bank;
	std::vector<int32> remainder;
	Random random;
	WindowType windowType;
	float32 lower, width;
	float32 rate;
	float32 jitterRate;
	bool jitterOn;


	float32 randomFreq();
	int32 randomLifetime();
	float32 window(const float32 f);

	int32 initOscillator(const uint32);
	void jitter(const float32 limit=0.01);

public:
	OscillatorBank();
	virtual ~OscillatorBank() = default;
	OscillatorBank(const OscillatorBank &) = default;
	OscillatorBank &operator=(const OscillatorBank &) = default;

	void reset();

	void initialise(const float32 lower_,const float32 upper_);
	void nOscillators(const uint32 n) { N=std::min(n,MaxN); }
	void setSampleRate(const float32);
	void setWindow(const WindowType w) { windowType=w; }
	void setJitterOn(const bool b) { jitterOn=b; };
	void setJitterRate(const float32 j) { jitterRate=j; }

	float32 operator()();
};



} /* namespace smearer */
} /* namespace meromorph */

#endif /* MULTIOSCILLATOR_HPP_ */
