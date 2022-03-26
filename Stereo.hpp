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
#include <complex>

namespace meromorph {
namespace smearer {

using port_t = TJBox_ObjectRef;

class Stereo {
private:
	const static uint32 BUFFER_SIZE = 64;
	using cx32 = std::complex<float32>;

		static const uint32 IN_BUFFER = kJBox_AudioInputBuffer;
		static const uint32 OUT_BUFFER = kJBox_AudioOutputBuffer;
		static const uint32 IN_CONN = kJBox_AudioInputConnected;
		static const uint32 OUT_CONN = kJBox_AudioOutputConnected;

		port_t inL,inR;
		port_t outL,outR;
		Limiter limiter;

		std::vector<float32> left,right;
		std::vector<cx32> stereo;

		void read(port_t channel,float32 *buffer);
		void write(port_t channel,float32 *buffer);

protected:
		void write(float32 *l,float32 *r);

		void read();
		void write();

public:
		void process(cx32 *oscillator);

};

} /* namespace smearer */
} /* namespace meromorph */

#endif /* STEREO_HPP_ */
