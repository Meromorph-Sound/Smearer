/*
 * OscillatorCore.cpp
 *
 *  Created on: 16 Jan 2022
 *      Author: julianporter
 */
#include "OscillatorCore.hpp"

namespace meromorph {
namespace smearer {

inline float32 sign(const float32 f) {
	return (f>0.f) ? 1.f : (f<0.f) ? -1.f : 0.f;
}

OscillatorCore::OscillatorCore(const float32 m) : multiplier(GainReduction/m) {}
float32 OscillatorCore::operator()(const float32 phase) { return value(phase)*multiplier; }
float32 OscillatorCore::value(const float32 phase) { return 0.f; }

float32 SineOscillator::value(const float32 phase) { return cos(phase); }
float32 SawtoothOscillator::value(const float32 phase) {
		return (phase/Pi)-1.f;
	}
float32 ExponentialOscillator::value(const float32 phase) {
		return (2.f*exp(-phase)-1.f);
	}
float32 TriangleOscillator::value(const float32 phase) {
		return 2.f*abs((phase/Pi)-1.f)-1.f;
	}
float32 SquareOscillator::value(const float32 phase) {
	return phase<1 ? 0.9 : -0.8;
}
float32 Step3Oscillator::value(const float32 phase) {
	auto norm = std::min(1.5f*phase/Pi,2.99f);
	return floor(norm)-1.f;
}
float32 Step4Oscillator::value(const float32 phase) {
	auto norm = std::min(2.f*phase/Pi,2.99f);
	return (floor(norm)*2.f/3.f-1.f);

}
float32 StepUpDownOscillator::value(const float32 phase) {
	auto norm = 2.5f*phase/Pi;
	return (norm<1) ? -1 : (norm<2) ? 0 : (norm<3) ? 1 : (norm<4) ? 0 : -1 ;
}
float32 PseudoRandomOscillator::value(const float32 phase) {
	auto norm = trunc(sin(phase)*shift1)/shift2;
	return norm-trunc(norm);
}


template <typename T>
std::shared_ptr<OscillatorCore> makeOsc() {
	return std::static_pointer_cast<OscillatorCore>(std::make_shared<T>());
}

std::shared_ptr<OscillatorCore> makeCore(const OscillatorCores c) {
	switch(c) {
	case Sinusoid:
		return makeOsc<SineOscillator>();
	case Triangle:
		return makeOsc<TriangleOscillator>();
	case Square:
		return makeOsc<SquareOscillator>();
	case Sawtooth:
		return makeOsc<SawtoothOscillator>();
	case Random:
		return  makeOsc<PseudoRandomOscillator>();
	case Exponential:
		return makeOsc<ExponentialOscillator>();
	case Step3:
		return makeOsc<Step3Oscillator>();
	case Step4:
		return makeOsc<Step4Oscillator>();
	case StepUpDown:
		return makeOsc<StepUpDownOscillator>();
	default:
		return std::make_shared<SquareOscillator>();
	}
}

}}
