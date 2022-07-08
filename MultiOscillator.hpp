/*
 * MultiOscillator.hpp
 *
 *  Created on: 29 Nov 2021
 *      Author: julianporter
 */

#ifndef MULTIOSCILLATOR_HPP_
#define MULTIOSCILLATOR_HPP_

#include "base.hpp"
#include "Random.hpp"
#include "OscillatorCore.hpp"
#include "Oscillator.hpp"

namespace meromorph {
namespace smearer {

enum WindowType : uint32 {
	Rectangular = 0,
	Triangular = 1,
	Tanh = 2,
	Hanning = 3,
	Hamming = 4,
	Gaussian = 5
};


class OscillatorBank {
private:
	const static uint32 MaxN;

	float32 minLifetime = 597.f;
	float32 lifetimeRange = 20000.f;


	uint32 N=1;
	float32 Ndiv=1.f;
	std::vector<std::shared_ptr<Oscillator>> bank;
	std::vector<std::shared_ptr<OscillatorCore>> cores;
	std::vector<int32> remainder;

	meromorph::Generator generator;
	meromorph::Random random;
	meromorph::Bernoulli probability;
	meromorph::Bernoulli probabilityJ;
	WindowType windowType = Triangular;
	std::shared_ptr<OscillatorCore> core;
	float32 lower = 0, width = 1;
	float32 sampleRate;
	float32 invRate;
	float32 jitterRate = 0;
	bool jitterOn = false;
	bool silenceOn = false;


	float32 randomFreq();
	int32 randomLifetime();
	float32 window(const float32 f);

	int32 initOscillator(const uint32);

public:
	OscillatorBank();
	virtual ~OscillatorBank() = default;
	OscillatorBank(const OscillatorBank &) = default;
	OscillatorBank &operator=(const OscillatorBank &) = default;

	void reset();

	void initialise(const float32 lower_,const float32 upper_);
	void nOscillators(const uint32 n) ;
	void setSampleRate(const float32);
	void setWindow(const WindowType w) { windowType=w; }
	void setJitterOn(const bool b) { jitterOn=b; };
	void setJitterRate(const float32 j) { jitterRate=j; }

	void setMinimumLifetime(const float32 m);
	void setLifetimeRange(const float32 r);

	void setCore(const OscillatorCores c);

	void setSilence(const float32 s);
	bool isSilent() const { return silenceOn; }
	void setJitter(const float32 s);
	bool isJitter() const { return jitterOn; }

	void setSmoothing(const uint32 s);

	float32 operator()();

	void reseed(const float32 f=Pi);

};

} /* namespace smearer */
} /* namespace meromorph */

#endif /* MULTIOSCILLATOR_HPP_ */
