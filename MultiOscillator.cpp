/*
 * MultiOscillator.cpp
 *
 *  Created on: 29 Nov 2021
 *      Author: julianporter
 */

#include "MultiOscillator.hpp"
#include <cstdlib>

namespace meromorph {
namespace smearer {


void Oscillator::step() {
	phase+=delta;
	if(phase>2*Pi) phase-=2*Pi;
}


float32 Oscillator::value() {
	step();
	return cos(phase)*amplitude ;
}

const uint32 OscillatorBank::MaxN = 500;

float32 OscillatorBank::randomFreq() { return (lower+random()*width)*rate; }
int32 OscillatorBank::randomLifetime() { return int32(597+20000*random()); }

float32 OscillatorBank::window(const float32 f) {
	auto sf=fabs(f/width);
	if(sf>=1.f) return 0.f;

	switch(windowType) {
	case WindowType::Rectangular:
		return 1.f;
	case WindowType::Triangular:
		return 1.f-sf;
	case WindowType::Hanning:
		return 0.5f*(1.f+cos(Pi*sf));
	case WindowType::Hamming:
		return 0.54f+0.46f*cos(Pi*sf);
	default:
		return 1.f;
	}
}

OscillatorBank::OscillatorBank() : N(1), bank(MaxN), remainder(MaxN,0), windowType(WindowType::Triangular),
		lower(0), width(1), rate(2*Pi/44100), jitterRate(0), jitterOn(false) {
	for(auto n=0;n<MaxN;n++) bank[n]=std::make_shared<Oscillator>(random());
};


int32 OscillatorBank::initOscillator(const uint32 n) {
	auto freq = randomFreq();
	auto lifetime = randomLifetime();
	auto amp  = window(freq);

	bank[n]->init(freq,amp);
	return lifetime;
}

void OscillatorBank::reset() {
	for(auto n=0;n<MaxN;n++) bank[n]->reset(random());
}

void OscillatorBank::jitter(const float32 limit) {
	if(!jitterOn || random()>=jitterRate) return;
	for(auto n=0;n<MaxN;n++) bank[n]->jitter(random()*limit);
}



void OscillatorBank::initialise(const float32 lower_,const float32 upper_) {
	lower=lower_;
	width=upper_-lower_;
	for(auto n=0;n<MaxN;n++) initOscillator(n);
}

void OscillatorBank::setSampleRate(const float32 sr) {
	rate = (sr<=0.f) ? 0.f : 2.f*Pi/sr;
	for(auto n=0;n<MaxN;n++) remainder[n]=initOscillator(n);
}

float32 OscillatorBank::operator()() {
	auto out=0.f;
	for(auto n=0;n<N;n++) {
		auto r=remainder[n];
		if(r<=1) r=initOscillator(n);
		remainder[n]=r-1;
		out+=bank[n]->value();
	}
	jitter();
	return out;
}



} /* namespace smearer */
} /* namespace meromorph */
