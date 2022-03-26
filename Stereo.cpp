/*
 * Stereo.cpp
 *
 *  Created on: 26 Mar 2022
 *      Author: julianporter
 */

#include "Stereo.hpp"

namespace meromorph {
namespace smearer {

void Stereo::read(port_t channel,float32 *buffer) {
	auto ref = JBox_LoadMOMPropertyByTag(channel, IN_BUFFER);
	auto length = std::min<int64>(JBox_GetDSPBufferInfo(ref).fSampleCount,BUFFER_SIZE);
	if(length>0) {
		JBox_GetDSPBufferData(ref, 0, length, buffer);
	}
	else {
		for(auto i=0;i<BUFFER_SIZE;i++) buffer[i]=0.f;
	}
}

void Stereo::write(port_t channel,float32 *buffer) {
	auto ref = JBox_LoadMOMPropertyByTag(channel, OUT_BUFFER);
	JBox_SetDSPBufferData(ref, 0, BUFFER_SIZE,buffer);
}



void Stereo::read() {
	read(inL,left.data());
	read(inR,right.data());
	for(auto i=0;i<BUFFER_SIZE;i++) stereo[i]=cx32(left[i],right[i]);
}

void Stereo::write() {
	for(auto i=0;i<BUFFER_SIZE;i++) {
		left[i]=stereo[i].real();
		right[i]=stereo[i].imag();
	}
	write(outL,left.data());
	write(outR,right.data());
}

void Stereo::process(cx32 *oscillator) {
	if(true) {
		read();
		for(auto i=0;i<BUFFER_SIZE;i++) stereo[i]*=oscillator[i];
		//limiter.limit(buffer);
		write();
	}


}

} /* namespace smearer */
} /* namespace meromorph */
