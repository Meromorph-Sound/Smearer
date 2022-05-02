/*
 * Stereo.hpp
 *
 *  Created on: 26 Mar 2022
 *      Author: julianporter
 */

#ifndef STEREO_HPP_
#define STEREO_HPP_

#include "base.hpp"
#include "Limiter.hpp"
#include "Filter.hpp"


namespace meromorph {
namespace smearer {

using port_t = TJBox_ObjectRef;



class StereoChannel {
private:
	const static uint32 BUFFER_SIZE = 64;

		static const uint32 IN_BUFFER = kJBox_AudioInputBuffer;
		static const uint32 OUT_BUFFER = kJBox_AudioOutputBuffer;
		static const uint32 IN_CONN = kJBox_AudioInputConnected;
		static const uint32 OUT_CONN = kJBox_AudioOutputConnected;

		port_t inL,inR;
		port_t outL,outR;
		Limiters limiter;

		//StereoBuffer stereo;
		vec_t left, right;

		uint32 read(port_t channel,float32 *buffer);
		void write(port_t channel,float32 *buffer);

protected:

		void read();
		void write();

public:
		StereoChannel(const port_t,const port_t,const port_t,const port_t);
		StereoChannel(const char *nameL,const char *nameR);
		virtual ~StereoChannel() = default;
		StereoChannel(const StereoChannel &) = default;
		StereoChannel(StereoChannel &&) = default;
		StereoChannel & operator=(const StereoChannel &) = default;
		StereoChannel & operator=(StereoChannel &&) = default;

		void bypass();
#ifdef COMPLEX_SAMPLES
		void process(cx32 *oscillator);
#else
		void process(float32 *oscL,float32 *oscR);
#endif

		void setLimiterActive(const bool a) { limiter.setActive(a); }
		void setLimiterMode(const Limiter::Mode m) { limiter.setMode(m); }
		void setLimiterLimit(const float32 l) { limiter.setLimit(l); }

};

} /* namespace smearer */
} /* namespace meromorph */



#endif /* STEREO_HPP_ */
