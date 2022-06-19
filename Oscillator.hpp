/*
 * Oscillator.hpp
 *
 *  Created on: 28 Jan 2022
 *      Author: julianporter
 */

#ifndef OSCILLATOR_HPP_
#define OSCILLATOR_HPP_

#include "base.hpp"

namespace meromorph {
namespace smearer {

class SmoothedValue {
private:
	float32 SmoothingPeriod=250.0;
	float32 increment = 0;
	float32 linIncrement = 0;
	float32 delta = 0;
	uint32 count = 0;

	void step();

public:
	float32 phase = 0;
	float32 lin = 0;

	SmoothedValue() {};
	virtual ~SmoothedValue() = default;
	SmoothedValue(const SmoothedValue &) = default;
	SmoothedValue &operator=(const SmoothedValue &) = default;

	void load(const float32 target,const float32 linear=0.f);
	float32 value();
};

class Oscillator {
private:
	uint32 SmoothingPeriod=250;
	float32 increment=0.f;
	float32 amplitudeIncrement=0.f;
	uint32 remainder=0;



public:

	float32 phase;
	float32 delta;
	float32 amplitude;



	Oscillator(const float32 phi0) : phase(phi0), delta(0), amplitude(1.0) {};
	Oscillator() : Oscillator(0) {};
	virtual ~Oscillator() = default;
	Oscillator(const Oscillator &) = default;
	Oscillator &operator=(const Oscillator &) = default;

	void smoothing(const uint32 s) { SmoothingPeriod=s; }

	void reset(const float32 phi0 = 0) { phase=phi0; }
	void jitter(const float32 j=0.01);
	void bump();
	void init(const float32 d,const float32 a);
	void silence() { init(delta,0); }

	void step();
	float32 value();
};

}}


#endif /* OSCILLATOR_HPP_ */
