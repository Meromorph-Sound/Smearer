/*
 * Clicker.cpp
 *
 *  Created on: 31 Jan 2021
 *      Author: julianporter
 */

#include "Smearer.hpp"



namespace meromorph {
namespace smearer {



//uint32 Smearer::read(const port_t port,float32 *data) {
//	auto ref = JBox_LoadMOMPropertyByTag(port, IN_BUFFER);
//	auto length = std::min<int64>(JBox_GetDSPBufferInfo(ref).fSampleCount,BUFFER_SIZE);
//	if(length>0) JBox_GetDSPBufferData(ref, 0, length, data);
//	return static_cast<int32>(length);
//}
//
//void Smearer::write(const port_t port,float32 *data) {
//	auto refL = JBox_LoadMOMPropertyByTag(port, OUT_BUFFER);
//	JBox_SetDSPBufferData(refL, 0, BUFFER_SIZE,data);
//}
//
//
//bool Smearer::isConnectedInput(const port_t port) {
//	return true; // toBool(JBox_LoadMOMPropertyByTag(port,IN_CONN));
//}
//bool Smearer::isConnectedOutput(const port_t port) {
//	return toBool(JBox_LoadMOMPropertyByTag(port,OUT_CONN));
//}

Smearer::Smearer() : RackExtension(), osc(BUFFER_SIZE,0), left("Left"), right("Right") {
//	inL  = JBox_GetMotherboardObjectRef("/audio_inputs/Left");
//	inR  = JBox_GetMotherboardObjectRef("/audio_inputs/Right");
//	outL = JBox_GetMotherboardObjectRef("/audio_outputs/Left");
//	outR = JBox_GetMotherboardObjectRef("/audio_outputs/Right");
}



void Smearer::reset() {
	oscillator.reset();
}

void Smearer::setSampleRate(const float32 rate) {
	sampleRate=rate;
	trace("Sample rate is ^0",rate);
	oscillator.setSampleRate(rate);
}

void Smearer::processApplicationMessage(const TJBox_PropertyDiff &diff) {
	Tag tag = diff.fPropertyTag;
	trace(">>> Processing tag ^0",(uint32)tag);
	switch(tag) {
	case kJBox_CustomPropertiesOnOffBypass: {
		trace("On/off/bypass status change");
		auto s = static_cast<State>(toFloat(diff.fCurrentValue));
		stateChanged = s!=state;
		state=s;
		break; }
	case Tags::HALF_WIDTH: {
		trace("Half widfth fired at ^0",tag);
		halfWidth = scaledFloat(diff.fCurrentValue,1.f,500.f);
		trace("Setting half width to ^0",halfWidth);
		oscillator.initialise(0,halfWidth);
		break;
	}
	case Tags::N_OSCILLATORS: {
		nOscillators = toInt(diff.fCurrentValue);
		trace("N Osc is ^0",nOscillators);
		oscillator.nOscillators(nOscillators);
		break;
	}

	case Tags::SCALE_FACTOR: {
		trace(">>> Processing SCALE @ tag ^0",tag);
		scaleFactor = scaledFloat(diff.fCurrentValue,SCALE_MIN,SCALE_MAX);
		trace("Scale is ^0",scaleFactor);

		break;
	}
	case Tags::WINDOW: {
		auto w=static_cast<WindowType>(toInt(diff.fCurrentValue));
		trace("Window type is ^0",(uint32)w);
		oscillator.setWindow(w);
		break;
	}
	case Tags::LIMIT_ON: {
		auto b = toBool(diff.fCurrentValue);
		if(b) trace("Limiter is ON");
		else trace("Limiter is OFF");
		//leftLimiter.setActive(b);
		//rightLimiter.setActive(b);
		left.setLimiterActive(b);
		right.setLimiterActive(b);
		break;
	}
	case Tags::LIMIT_MODE: {
		auto m = static_cast<Limiter::Mode>(toInt(diff.fCurrentValue));
		trace("Limiter mode is ^0",m);
		//leftLimiter.setMode(m);
		//rightLimiter.setMode(m);
		left.setLimiterMode(m);
		right.setLimiterMode(m);
		break;
	}
	case Tags::LIMIT_DEPTH: {
		//auto d = scaledFloat(diff.fCurrentValue,-12.f,3.f);
		auto r = toFloat(diff.fCurrentValue);
		auto l = scaledFloat(diff.fCurrentValue,-12.f,0.f);
		auto p = pow(10.f,l*0.1f);
		trace("Limiter scale is ^0 <=> ^1",r,l);
		//trace("Limiter depth is ^0",d);
		//leftLimiter.setLimit(d);
		//rightLimiter.setLimit(d);
		left.setLimiterLimit(p);
		right.setLimiterLimit(p);
		break;
	}
	case Tags::FILTER_ON: {
		auto b = toBool(diff.fCurrentValue);
		if(b) trace("Filter is ON");
		else trace("Filter is OFF");
		filter.setActive(b);
		break;
	}
	case Tags::FILTER_Q: {
		auto c = clampedFloat(diff.fCurrentValue); //log2(1+clampedFloat(diff.fCurrentValue));
		trace("Filter Q is ^0",c);
		filter.setQ(c);
		break;
	}
	case kJBox_AudioInputConnected:
	case kJBox_AudioOutputConnected:
		trace("Audio connected");
		break;
	}


}

float32 Smearer::operator()(const float32 buf,const float32 mul) const {
	return buf*(1.f + scaleFactor*mul);
}

void Smearer::process() {


	switch(state) {
	case State::On: {
		//trace("on!");
		auto factor=scaleFactor;
		for(auto i=0;i<BUFFER_SIZE;i++) osc[i]=1.f+factor*oscillator();
		filter.filter(osc);

		left.process(osc.data());
		right.process(osc.data());

//		if(isConnectedInput(inL)) {
//			read(inL,buffer.data());
//			for(auto i=0;i<BUFFER_SIZE;i++) buffer[i]*=osc[i];
//			leftLimiter.limit(buffer);
//			write(outL,buffer.data());
//		}
//		if(isConnectedInput(inR)) {
//			read(inR,buffer.data());
//			for(auto i=0;i<BUFFER_SIZE;i++) buffer[i]*=osc[i];
//			rightLimiter.limit(buffer);
//			write(outR,buffer.data());
//		}
		break; }
	case State::Bypassed:
		//trace("Bypassed!");
		left.bypass();
		right.bypass();
//		if(isConnectedInput(inL)) {
//			read(inL,buffer.data());
//			write(outL,buffer.data());
//		}
//		if(isConnectedInput(inR)) {
//			read(inR,buffer.data());
//			write(outR,buffer.data());
//		}
		break;
	default:
		break;
	}

	//	auto lr=left.getRMS();
	//	if(lr!=oldLRMS) set(lr,Tags::LEFT_VOL);
	//	oldLRMS=lr;
	//
	//	auto rr=right.getRMS();
	//	if(rr!=oldRRMS) set(rr,Tags::RIGHT_VOL);
	//	oldRRMS=rr;



}




} /* namespace click */
} /* namespace meromorph */
