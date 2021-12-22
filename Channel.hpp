/*
 * Channel.hpp
 *
 *  Created on: 16 Dec 2021
 *      Author: julianporter
 */

#ifndef CHANNEL_HPP_
#define CHANNEL_HPP_

#include "base.hpp"
#include "Limiter.hpp"
#include "Filter.hpp"

namespace meromorph {
namespace smearer {

using port_t = TJBox_ObjectRef;





class Channel {
private:
	const static uint32 BUFFER_SIZE = 64;

	static const uint32 IN_BUFFER = kJBox_AudioInputBuffer;
	static const uint32 OUT_BUFFER = kJBox_AudioOutputBuffer;
	static const uint32 IN_CONN = kJBox_AudioInputConnected;
	static const uint32 OUT_CONN = kJBox_AudioOutputConnected;

	port_t in;
	port_t out;
	Limiter limiter;

	std::vector<float32> buffer;

	uint32 read(float32 *data);
	void write(float32 *data);

	bool isInputConnected();
	bool isOutputConnected();

public:
	Channel(const port_t,const port_t);
	Channel(const char *);
	virtual ~Channel() = default;
	Channel(const Channel &other) = default;
	Channel(Channel &&other) = default;
	Channel& operator=(const Channel &other) = default;
	Channel& operator=(Channel &&other) = default;

	void bypass();
	void process(float32 *oscillator);

	void setLimiterActive(const bool a) { limiter.setActive(a); }
	void setLimiterMode(const Limiter::Mode m) { limiter.setMode(m); }
	void setLimiterLimit(const float32 l) { limiter.setLimit(l); }

};

} /* namespace smearer */
} /* namespace meromorph */

#endif /* CHANNEL_HPP_ */
