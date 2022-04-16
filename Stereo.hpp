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

struct StereoValue {
	float32 left;
	float32 right;

	StereoValue() : left(0), right(0) {}
	StereoValue(const StereoValue &) = default;
	StereoValue & operator=(const StereoValue &) = default;
	virtual ~StereoValue() = default;
};

struct StereoBuffer {
	using vec_t = std::vector<float32>;
	const static uint32 BUFFER_SIZE = 64;

	vec_t left;
	vec_t right;

	StereoBuffer() : left(BUFFER_SIZE,0.f), right(BUFFER_SIZE,0.f) {};
	StereoBuffer(const StereoBuffer &) = default;
	StereoBuffer & operator=(const StereoBuffer &) = default;
	virtual ~StereoBuffer() = default;

	void zero();

	float32 * lData() noexcept { return left.data(); }
	float32 * rData() noexcept { return right.data(); }

	const float32 * lData() const noexcept { return left.data(); }
	const float32 * rData() const noexcept { return right.data(); }

	cx32 self(const unsigned n) const { return cx32(left[n],right[n]); }
	void self(const unsigned n,const cx32 z) { left[n]=z.real(); right[n]=z.imag(); }

	void product(const StereoBuffer &o);
	void product(cx32 *buffer);

	void set(const unsigned n,const float32 r,const float32 i);
	void get(const unsigned n,float32 &r,float32 &i);

};



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

		StereoBuffer stereo;

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
		void process(cx32 *oscillator);

		void setLimiterActive(const bool a) { limiter.setActive(a); }
		void setLimiterMode(const Limiter::Mode m) { limiter.setMode(m); }
		void setLimiterLimit(const float32 l) { limiter.setLimit(l); }

};

} /* namespace smearer */
} /* namespace meromorph */



#endif /* STEREO_HPP_ */
