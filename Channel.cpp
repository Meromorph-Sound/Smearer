/*
 * Channel.cpp
 *
 *  Created on: 16 Dec 2021
 *      Author: julianporter
 */

#include "Channel.hpp"
#include <memory>

namespace meromorph {
namespace smearer {

uint32 Channel::read(float32 *data) {
	auto ref = JBox_LoadMOMPropertyByTag(in, IN_BUFFER);
	auto length = std::min<int64>(JBox_GetDSPBufferInfo(ref).fSampleCount,BUFFER_SIZE);
	if(length>0) JBox_GetDSPBufferData(ref, 0, length, data);
	return static_cast<int32>(length);
}

void Channel::write(float32 *data) {
	auto refL = JBox_LoadMOMPropertyByTag(out, OUT_BUFFER);
	JBox_SetDSPBufferData(refL, 0, BUFFER_SIZE,data);
}

bool Channel::isInputConnected() {
	return true; // toBool(JBox_LoadMOMPropertyByTag(in,IN_CONN));
}
bool Channel::isOutputConnected() {
	return toBool(JBox_LoadMOMPropertyByTag(out,OUT_CONN));
}


Channel::Channel(const port_t in_,const port_t out_) : in(in_), out(out_), buffer(64,0) {}

Channel::Channel(const char *name) : buffer(64,0) {
	char str[80];
	strcpy(str,"/audio_inputs/");
	strcat(str,name);
	in=JBox_GetMotherboardObjectRef(str);

	strcpy(str,"/audio_outputs/");
	strcat(str,name);
	out=JBox_GetMotherboardObjectRef(str);
}


void Channel::bypass() {
	auto n = read(buffer.data());
	if(n>0) write(buffer.data());
}

void Channel::process(float32 *oscillator) {
	if(isInputConnected()) {
		read(buffer.data());
		for(auto i=0;i<BUFFER_SIZE;i++) buffer[i]*=oscillator[i];
		limiter.limit(buffer);
		write(buffer.data());
	}


}



} /* namespace smearer */
} /* namespace meromorph */
