/*
 * ChannelBase.hpp
 *
 *  Created on: 12 Apr 2022
 *      Author: julianporter
 */

#ifndef CHANNELBASE_HPP_
#define CHANNELBASE_HPP_

#include "base.hpp"

namespace meromorph {
namespace smearer {

class ChannelBase {

	void bypass();
	void process(float32 *oscillator);

//	void setLimiterActive(const bool a);
//	void setLimiterMode(const Limiter::Mode m) { limiter.setMode(m); }
//	void setLimiterLimit(const float32 l) { limiter.setLimit(l); }

};

} /* namespace smearer */
} /* namespace meromorph */

#endif /* CHANNELBASE_HPP_ */
