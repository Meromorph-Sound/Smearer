/*
 * Stereo.cpp
 *
 *  Created on: 26 Mar 2022
 *      Author: julianporter
 */

#include "Stereo.hpp"

namespace meromorph {
namespace smearer {

/*

void StereoBuffer::zero() {
	left.assign(BUFFER_SIZE,0.f);
	right.assign(BUFFER_SIZE,0.f);
}

void StereoBuffer::product(const StereoBuffer &o) {
	auto oL = o.lData();
	auto oR = o.rData();
	for(auto i=0;i<BUFFER_SIZE;i++) {
		left[i]  = left[i]*oL[i] - right[i]*oR[i];
		right[i] = left[i]*oR[i] + right[i]*oL[i];
	}
}
void StereoBuffer::product(float32 *lBuffer,float32 *rBuffer) {
	for(auto i=0;i<BUFFER_SIZE;i++) {
		auto re=lBuffer[i];
		auto im=rBuffer[i];
		auto oRe = re*left[i] - im*right[i];
		auto oIm = re*right[i] + im*left[i];
		left[i] = oRe;
		right[i] = oIm;
		//auto z=buffer[i] * self(i);
		//self(i,z);
	}
}

void StereoBuffer::set(const unsigned n,const float32 r,const float32 i) {
	left[n]=r;
	right[n]=i;
}
void StereoBuffer::get(const unsigned n,float32 &r,float32 &i) {
	r=left[n];
	i=right[n];
}

*/

uint32 StereoChannel::read(port_t channel,float32 *buffer) {
	auto ref = JBox_LoadMOMPropertyByTag(channel, IN_BUFFER);
	auto length = std::min<int64>(JBox_GetDSPBufferInfo(ref).fSampleCount,BUFFER_SIZE);
	if(length>0) JBox_GetDSPBufferData(ref, 0, length, buffer);
	return static_cast<int32>(length);
}

void StereoChannel::write(port_t channel,float32 *buffer) {
	auto ref = JBox_LoadMOMPropertyByTag(channel, OUT_BUFFER);
	JBox_SetDSPBufferData(ref, 0, BUFFER_SIZE,buffer);
}



void StereoChannel::read() {
	read(inL,left.data());
	read(inR,right.data());
//	read(inL,stereo.lData());
//	read(inR,stereo.rData());
}

void StereoChannel::write() {
	write(outL,left.data());
	write(outR,right.data());
}

StereoChannel::StereoChannel(const port_t inL_,const port_t inR_,const port_t outL_,const port_t outR_) :
		inL(inL_), inR(inR_), outL(outL_), outR(outR_), left(BUFFER_SIZE,0.f), right(BUFFER_SIZE,0.f) {}

StereoChannel::StereoChannel(const char *nameL,const char *nameR) : left(BUFFER_SIZE,0.f), right(BUFFER_SIZE,0.f) {
	char str[80];
	strcpy(str,"/audio_inputs/");
	strcat(str,nameL);
	inL=JBox_GetMotherboardObjectRef(str);

	strcpy(str,"/audio_outputs/");
	strcat(str,nameL);
	outL=JBox_GetMotherboardObjectRef(str);

	strcpy(str,"/audio_inputs/");
	strcat(str,nameR);
	inR=JBox_GetMotherboardObjectRef(str);

	strcpy(str,"/audio_outputs/");
	strcat(str,nameR);
	outR=JBox_GetMotherboardObjectRef(str);
}



void StereoChannel::bypass() {
	read();
	write();
}

void StereoChannel::process(float32 *osc) {
	if(true) {
		left.assign(BUFFER_SIZE,0.f);
		right.assign(BUFFER_SIZE,0.f);
		read();
		for(auto i=0;i<BUFFER_SIZE;i++) {
				left[i]*=osc[i];
				right[i]*=osc[i];
			}
		limiter.limit(left.data(),right.data(),BUFFER_SIZE);
		write();
	}
}

} /* namespace smearer */
} /* namespace meromorph */
