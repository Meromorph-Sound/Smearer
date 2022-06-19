/*
 * Oscillator.cpp
 *
 *  Created on: 28 Jan 2022
 *      Author: julianporter
 */

#include "Oscillator.hpp"

namespace meromorph {
namespace smearer {


void SmoothedValue::load(const float32 target,const float32 linear) {
	auto inc=(target-delta);
	if(inc<0) inc+=TwoPi;
	increment=inc/(float)SmoothingPeriod;
	count=0;
	linIncrement=(linear-lin)/(float)SmoothingPeriod;
}

void SmoothedValue::step() {
	if(count<SmoothingPeriod) {
		lin+=linIncrement;
		delta+=increment;
		//trace("Reminder is ^0 delta is ^1",remainder,delta);
		count++;
	}
	phase=std::remainder(phase+delta,TwoPi);
}

float32 SmoothedValue::value() {
	step();
	return phase;
}


void Oscillator::jitter(const float32 j) { phase=std::remainder(-phase+j*delta*0.05f,TwoPi); }
void Oscillator::bump() { phase=std::remainder(-phase,TwoPi); }

void Oscillator::init(const float32 d,const float32 a) {
	auto inc=(d-delta);
	if(inc<0) inc+=TwoPi;
	increment=inc/(float)SmoothingPeriod;
	remainder=0;
	amplitudeIncrement=(a-amplitude)/(float)SmoothingPeriod;
}

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
