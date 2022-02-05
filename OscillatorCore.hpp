/*
 * OscillatorCore.hpp
 *
 *  Created on: 16 Jan 2022
 *      Author: julianporter
 */

#ifndef OSCILLATORCORE_HPP_
#define OSCILLATORCORE_HPP_

#include "base.hpp"


namespace meromorph {
namespace smearer {

enum OscillatorCores : uint32 {
	Sinusoid = 0,
	Triangle = 1,
	Square = 2,
	Sawtooth = 3,
	Random = 4,
	Exponential = 5,
	Step3 = 6,
	Step4 = 7,
	StepUpDown = 8
};

class OscillatorCore {
protected:
	float32 multiplier;

	constexpr static float32 GainReduction = 1.5f;

public:
	OscillatorCore(const float32 m=1.f);
	virtual ~OscillatorCore() = default;

	virtual float32 value(const float32 phase);
	float32 operator()(const float32 phase);
};

class SineOscillator : public OscillatorCore {
public:
	SineOscillator() : OscillatorCore(4.f) {}
	virtual ~SineOscillator() = default;

	virtual float32 value(const float32 phase);
};

class SawtoothOscillator : public OscillatorCore {
public:
	SawtoothOscillator()  : OscillatorCore(2.f) {}
	virtual ~SawtoothOscillator() = default;

	virtual float32 value(const float32 phase);
};
class ExponentialOscillator : public OscillatorCore {
public:
	ExponentialOscillator() : OscillatorCore(1.f/9.f) {}
	virtual ~ExponentialOscillator() = default;

	virtual float32 value(const float32 phase);
};
class TriangleOscillator : public OscillatorCore {
public:
	TriangleOscillator()  : OscillatorCore(1.5f) {}
	virtual ~TriangleOscillator() = default;

	virtual float32 value(const float32 phase);
};
class Step3Oscillator : public OscillatorCore {
public:
	Step3Oscillator()  : OscillatorCore(1.5f) {}
	virtual ~Step3Oscillator() = default;

	virtual float32 value(const float32 phase);
};
class Step4Oscillator : public OscillatorCore {
public:
	Step4Oscillator() : OscillatorCore(1.8f) {};
	virtual ~Step4Oscillator() = default;

	virtual float32 value(const float32 phase);
};
class StepUpDownOscillator : public OscillatorCore {
public:
	StepUpDownOscillator() : OscillatorCore(10.f/3.f) {};
	virtual ~StepUpDownOscillator() = default;

	virtual float32 value(const float32 phase);
};
class PseudoRandomOscillator : public OscillatorCore {
public:
	constexpr static float32 shift1=10000.f;
	constexpr static float32 shift2=3746.3f;
	PseudoRandomOscillator() : OscillatorCore(4.f) {};
	virtual ~PseudoRandomOscillator() = default;

	virtual float32 value(const float32 phase);
};
class SquareOscillator : public OscillatorCore {
public:
	SquareOscillator() : OscillatorCore(4.f) {}
	virtual ~SquareOscillator() = default;

	virtual float32 value(const float32 phase);
};

std::shared_ptr<OscillatorCore> makeCore(const OscillatorCores c);

}}

#endif /* OSCILLATORCORE_HPP_ */
