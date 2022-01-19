/*
 * OscillatorCore.cpp
 *
 *  Created on: 16 Jan 2022
 *      Author: julianporter
 */
#include "OscillatorCore.hpp"

namespace meromorph {
namespace smearer {

float32 OscillatorCore::operator()(const float32 phase) { return 0; }
float32 SineOscillator::operator()(const float32 phase) { return cos(phase); }
float32 SawtoothOscillator::operator()(const float32 phase) {
		return (phase/Pi)-1;
	}
float32 ExponentialOscillator::operator()(const float32 phase) {
		return 2*exp(-phase)-1;
	}
float32 TriangleOscillator::operator()(const float32 phase) {
		auto normalised = 2*(phase/Pi)-1; //(2*phase/Pi)-1.f;
		return (phase<Pi) ? normalised : 2-normalised;
	}
float32 SquareOscillator::operator()(const float32 phase) {
		return (phase<Pi) ? -1 : 1;
}
float32 Step3Oscillator::operator()(const float32 phase) {
	auto norm = 3.f*phase/Pi;
	return (norm<1) ? -1 : (norm>2) ? 1 : 0;
}
float32 Step4Oscillator::operator()(const float32 phase) {
	auto norm = 4.f*phase/Pi;
	return (norm<1) ? -1 : (norm<2) ? -intermediate : (norm < 3) ? intermediate : 1.f ;
}
float32 StepUpDownOscillator::operator()(const float32 phase) {
	auto norm = 5.f*phase/Pi;
	return (norm<1) ? -1 : (norm<2) ? 0 : (norm<3) ? 1 : (norm<4) ? 0 : -1 ;
}
float32 PseudoRandomOscillator::operator()(const float32 phase) {
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
		return std::make_shared<OscillatorCore>();
	}
}

}}
