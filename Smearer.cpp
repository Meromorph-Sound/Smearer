/*
 * Clicker.cpp
 *
 *  Created on: 31 Jan 2021
 *      Author: julianporter
 */

#include "Smearer.hpp"



namespace meromorph {
namespace smearer {





Smearer::Smearer() : RackExtension(), osc(BUFFER_SIZE,0), left("Left"), right("Right") {
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
		filter.setWidth(halfWidth/sampleRate);
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
	case Tags::FILTER_ORDER: {
		uint32 c = 1+toInt(diff.fCurrentValue); //log2(1+clampedFloat(diff.fCurrentValue));
		trace("Filter order is ^0",c);
		//filter.setOrder(c);
		break;
	}
	case Tags::DURATION_MIN: {
		auto f = clampedFloat(diff.fCurrentValue);
		oscillator.setMinimumLifetime(f);
		break;
	}
	case Tags::DURATION_RANGE: {
		auto f = scaledFloat(diff.fCurrentValue,0.f,9.f);
		oscillator.setLifetimeRange(f);
		break;
	}
	case Tags::OSCILLATOR_WAVEFORM: {
		auto i = toInt(diff.fCurrentValue);
		if(i>=0 && i<9) {
			auto core = static_cast<OscillatorCores>(i);
			oscillator.setCore(core);
		}
		break;
	}
	case Tags::SILENCE: {
		auto s=clampedFloat(diff.fCurrentValue);
		oscillator.setSilence(s);
		set(oscillator.isSilent() ? 1.f : 0.f,Tags::SILENCE_ON);
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

	if(!initialised) {
		oscillator.setSilence(0.5);
		initialised=true;
	}
//		oscillator.setCore(OscillatorCores::Sinusoid);
//		initialised=true;
//	}


	switch(state) {
	case State::On: {
		//trace("on!");
		auto factor=scaleFactor;
		for(auto i=0;i<BUFFER_SIZE;i++) osc[i]=(1.f-factor)+factor*oscillator();
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
