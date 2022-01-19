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
public:
	OscillatorCore() = default;
	virtual ~OscillatorCore() = default;

	virtual float32 operator()(const float32 phase);
};

class SineOscillator : public OscillatorCore {
public:
	SineOscillator() = default;
	virtual ~SineOscillator() = default;

	virtual float32 operator()(const float32 phase);
};

class SawtoothOscillator : public OscillatorCore {
public:
	SawtoothOscillator() = default;
	virtual ~SawtoothOscillator() = default;

	virtual float32 operator()(const float32 phase);
};
class ExponentialOscillator : public OscillatorCore {
public:
	ExponentialOscillator() = default;
	virtual ~ExponentialOscillator() = default;

	virtual float32 operator()(const float32 phase);
};
class TriangleOscillator : public OscillatorCore {
public:
	TriangleOscillator() = default;
	virtual ~TriangleOscillator() = default;

	virtual float32 operator()(const float32 phase);
};
class Step3Oscillator : public OscillatorCore {
public:
	constexpr static float32 cutoff=1.f/3.f;
	Step3Oscillator() = default;
	virtual ~Step3Oscillator() = default;

	virtual float32 operator()(const float32 phase);
};
class Step4Oscillator : public OscillatorCore {
public:
	constexpr static float32 intermediate=1.f/3.f;
	Step4Oscillator() = default;
	virtual ~Step4Oscillator() = default;

	virtual float32 operator()(const float32 phase);
};
class StepUpDownOscillator : public OscillatorCore {
public:
	constexpr static float32 cutoff1=2.f/5.f;
	constexpr static float32 cutoff2=4.f/5.f;
	StepUpDownOscillator() = default;
	virtual ~StepUpDownOscillator() = default;

	virtual float32 operator()(const float32 phase);
};
class PseudoRandomOscillator : public OscillatorCore {
public:
	constexpr static float32 shift1=10000.f;
	constexpr static float32 shift2=3746.3f;
	PseudoRandomOscillator() = default;
	virtual ~PseudoRandomOscillator() = default;

	virtual float32 operator()(const float32 phase);
};
class SquareOscillator : public OscillatorCore {
public:
	SquareOscillator() = default;
	virtual ~SquareOscillator() = default;

	virtual float32 operator()(const float32 phase);
};

std::shared_ptr<OscillatorCore> makeCore(const OscillatorCores c);

}}

#endif /* OSCILLATORCORE_HPP_ */
