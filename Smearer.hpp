/*
 * Clicker.hpp
 *
 *  Created on: 31 Jan 2021
 *      Author: julianporter
 */

#ifndef SMEARER_HPP_
#define SMEARER_HPP_


#include "RackExtension.hpp"
#include "MultiOscillator.hpp"
#include "Limiter.hpp"
#include "Filter.hpp"
#include "Channel.hpp"


namespace meromorph {
namespace smearer {


#define HALF_WIDTH_MIN 1.f
#define HALF_WIDTH_MAX 90.f

#define SCALE_MIN 0.f
#define SCALE_MAX 2.0f


//using port_t = TJBox_ObjectRef;

/*
 * local PropertyTags = {
  HALF_WIDTH = 1,
  N_OSCILLATORS = 2,
  SCALE_FACTOR = 3,
  WINDOW = 4,
  FILTER_ON = 5,
  FILTER_Q = 6,
  LIMITER_ON = 7,
  LIMITER = 8,
  LIMITER_HARD_SOFT = 9,
  FILTER_MODE = 10,
  DURATION_MIN = 20,
  DURATION_RANGE = 21
}
 */

enum Tags : uint32 {
	HALF_WIDTH=1,
	N_OSCILLATORS=2,
	SCALE_FACTOR=3,
	WINDOW=4,
	FILTER_ON=5,
	FILTER_Q=6,
	LIMIT_ON=7,
	LIMIT_DEPTH=8,
	LIMIT_MODE=9,
	FILTER_ORDER=10,
	DURATION_MIN=20,
	DURATION_RANGE=21,
	OSCILLATOR_WAVEFORM=22,
	SILENCE=23,
	SILENCE_ON=24
};

class Smearer : public RackExtension {
private:

	State state = State::On;
	bool stateChanged=true;
	bool initialised=false;

	float32 halfWidth=1.f;
	float32 scaleFactor=0.8f;
	uint32 nOscillators=10;
	float32 sampleRate=44100.f;

	//port_t inL,inR;
	//port_t outL,outR;

	OscillatorBank oscillator;
	std::vector<float32> osc;

	Channel left, right;


	Filter filter;
	//Filter rightFilter;
	//Limiter leftLimiter;
	//Limiter rightLimiter;

	const static uint32 BUFFER_SIZE = 64;

	//static const uint32 IN_BUFFER = kJBox_AudioInputBuffer;
	//static const uint32 OUT_BUFFER = kJBox_AudioOutputBuffer;
	//static const uint32 IN_CONN = kJBox_AudioInputConnected;
	//static const uint32 OUT_CONN = kJBox_AudioOutputConnected;


	//static uint32 read(const port_t port,float32 *data);
	//static void write(const port_t port,float32 *data);
	//static bool isConnectedInput(const port_t port);
	//static bool isConnectedOutput(const port_t port);

protected:

	virtual void processApplicationMessage(const TJBox_PropertyDiff &diff);
	virtual void process();
	virtual void reset();
	virtual void setSampleRate(const float32 rate);

	float32 operator()(const float32 buf,const float32 mul) const;

public:
	Smearer();
	virtual ~Smearer() = default;
	Smearer(const Smearer &other) = default;
	Smearer& operator=(const Smearer &other) = default;



};

} /* namespace click */
} /* namespace meromorph */

#endif /* SMEARER_HPP_ */
