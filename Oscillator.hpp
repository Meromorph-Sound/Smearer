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



	Oscillator(const float32 phi0) : phase(phi0), delta(0), amplitude(0.0) {
	};
	Oscillator() : Oscillator(0) {};
	virtual ~Oscillator() = default;
	Oscillator(const Oscillator &) = default;
	Oscillator &operator=(const Oscillator &) = default;

	void smoothing(const uint32 s);

	void reset(const float32 phi0 = 0);
	void hardReset();
	void jitter(const float32 j=0.01);
	void bump();
	void init(const float32 d,const float32 a);
	void silence();

	void step();
	float32 value();
};

}}


#endif /* OSCILLATOR_HPP_ */
