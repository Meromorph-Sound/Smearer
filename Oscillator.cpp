/*
 * Oscillator.cpp
 *
 *  Created on: 28 Jan 2022
 *      Author: julianporter
 */

#include "Oscillator.hpp"

namespace meromorph {
namespace smearer {




void Oscillator::smoothing(const uint32 s) {
	SmoothingPeriod = s;
}
void Oscillator::reset(const float32 phi0 ) { phase=phi0; }
void Oscillator::jitter(const float32 j) {
	phase=std::remainder(-phase+j*delta*0.05f,TwoPi);
}
void Oscillator::bump() { phase=std::remainder(-phase,TwoPi); }

void Oscillator::init(const float32 d,const float32 a) {
	auto inc=(d-delta);
	if(inc<0) inc+=TwoPi;
	increment=inc/(float)SmoothingPeriod;
	remainder=0;
	amplitudeIncrement=(a-amplitude)/(float)SmoothingPeriod;
}

void Oscillator::silence() { init(delta,0); }

void Oscillator::step() {
	if(remainder<SmoothingPeriod) {
		amplitude+=amplitudeIncrement;
		delta+=increment;
		//trace("Reminder is ^0 delta is ^1",remainder,delta);
		remainder++;
	}
	phase=std::remainder(phase+delta,TwoPi);
}


float32 Oscillator::value() {
	step();
	return phase;
}


}}
