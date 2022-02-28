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


const uint32 OscillatorBank::MaxN = 500;

float32 OscillatorBank::randomFreq() { return (lower+random()*width)*invRate; }
int32 OscillatorBank::randomLifetime() { return 64+int32(minLifetime+lifetimeRange*random()); }

float32 OscillatorBank::window(const float32 f) {
	if(f<=0.0) return 0.f;

	auto scaledWidth=width*invRate;
	auto sf=fabs(f/scaledWidth);
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
	case WindowType::Tanh:
		return 1.0f-tanh(Pi*sf);
	case WindowType::Gaussian:
		return exp(-Pi*sf*sf);
	default:
		return 1.f;
	}
}

template <typename T>
inline std::shared_ptr<OscillatorCore> makeOsc() {
	return std::static_pointer_cast<OscillatorCore>(std::make_shared<T>());
}

OscillatorBank::OscillatorBank() : bank(MaxN), cores(9), remainder(MaxN,0), sampleRate(44100), invRate(2*Pi/sampleRate) {
	for(auto n=0;n<MaxN;n++) bank[n]=std::make_shared<Oscillator>(random());
	for(auto n=0;n<9;n++) cores[n]=makeCore(static_cast<OscillatorCores>(n));
	core=cores[Sinusoid];
}

int32 OscillatorBank::initOscillator(const uint32 n) {

	auto lifetime = randomLifetime();
	if(silenceOn && (bool)probability) {
		bank[n]->silence();
	}
	else {
		auto freq = randomFreq();
		auto amp =  window(freq);
		bank[n]->init(freq,amp);
	}

	return lifetime;
}

void OscillatorBank::reset() {
	for(auto n=0;n<MaxN;n++) bank[n]->reset(random()*TwoPi);
	reseed();
}




void OscillatorBank::initialise(const float32 lower_,const float32 upper_) {
	lower=lower_;
	width=upper_-lower_;
	for(auto n=0;n<MaxN;n++) initOscillator(n);
}

void OscillatorBank::setSampleRate(const float32 sr) {
	sampleRate = std::max(0.f,sr);
	invRate = (sr<=0.f) ? 0.f : 2.f*Pi/sr;
	for(auto n=0;n<MaxN;n++) remainder[n]=initOscillator(n);
}

void OscillatorBank::setMinimumLifetime(const float32 m) {
	minLifetime=std::max(65.f,sampleRate*m);
	trace(">>> MIN LIFETIME Raw ^0 Processed ^1",m,minLifetime);
}
void OscillatorBank::setLifetimeRange(const float32 r) {
	lifetimeRange=sampleRate*r;
	trace(">>> RANGE       Raw ^0 Processed ^1",r,lifetimeRange);
}
void OscillatorBank::setCore(const OscillatorCores c) {
	core = cores.at(static_cast<uint32>(c));
	//for(auto n=0;n<MaxN;n++) bank[n]->setCore(core);
}
void OscillatorBank::setSilence(const float32 s) {
	silenceOn=s>0;
	probability.setThreshold(s);
}
void OscillatorBank::setJitter(const float32 j) {
	jitterOn=j>0;
	probabilityJ.setThreshold(j/64.f);
}
void OscillatorBank::setSmoothing(const uint32 s) {
	for(auto n=0;n<MaxN;n++) bank[n]->smoothing(s);
}

float32 OscillatorBank::operator()() {
	if(!core) return 0.f;
	auto out=0.f;
	for(auto n=0;n<N;n++) {
		auto r=remainder[n];
		if(r<=1) r=initOscillator(n);
		remainder[n]=r-1;
		out+=(*core)(bank[n]->value())*bank[n]->amplitude;

		if(jitterOn &&(bool)probabilityJ) {
			bank[n]->jitter((float)random()-0.5f);

		}
	}
	return out;
}

void OscillatorBank::reseed(const float f) {
	generator.reset();
	generator(lower+f);
	generator(width-f);
	generator(invRate);
	generator(sampleRate);
	generator(jitterRate);
	generator(N);
	random.reseed(generator);
	generator(random());
	probability.reseed(generator);
	generator(random());
	probabilityJ.reseed(generator);
}

} /* namespace smearer */
} /* namespace meromorph */
