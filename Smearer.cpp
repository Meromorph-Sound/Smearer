/*
 * Clicker.cpp
 *
 *  Created on: 31 Jan 2021
 *      Author: julianporter
 */

#include "Smearer.hpp"



namespace meromorph {
namespace smearer {





Smearer::Smearer() : RackExtension(), osc(BUFFER_SIZE,0),lBuffer(BUFFER_SIZE,0),rBuffer(BUFFER_SIZE,0), left("Left"), right("Right") {
}



void Smearer::reset() {
	oscillator.reset();
	wasReseeded=false;
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

	case Tags::GAIN: {
		trace(">>> Processing GAIN @ tag ^0",tag);
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
		limiter.setActive(b);
		break;
	}
	case Tags::LIMIT_MODE: {
		auto m = static_cast<Limiter::Mode>(toInt(diff.fCurrentValue));
		trace("Limiter mode is ^0",m);
		limiter.setMode(m);
		break;
	}
	case Tags::LIMIT_DEPTH: {
		auto r = toFloat(diff.fCurrentValue);
		auto l = scaledFloat(diff.fCurrentValue,-12.f,0.f);
		auto p = pow(10.f,l*0.1f);
		trace("Limiter scale is ^0 <=> ^1",r,l);
		limiter.setLimit(p);
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
	case Tags::JITTER: {
		auto s=clampedFloat(diff.fCurrentValue);
		oscillator.setJitter(s);
		set(oscillator.isJitter() ? 1.f : 0.f,Tags::JITTER_ON);
		break;
	}
	case Tags::SMOOTHING: {
		auto s=scaledFloat(diff.fCurrentValue,1.f,250.f);
		oscillator.setSmoothing((uint32)s);
		break;
	}
	case Tags::RESEED: { // momentary boolean
		auto b = toBool(diff.fCurrentValue);
		if(b!=wasReseeded) {
			if(b) oscillator.reseed(transportPosition());
			wasReseeded=b;
		}
		break;
	}
	case Tags::MIX: {
		//mix_ext=clampedFloat(diff.fCurrentValue);
		factor=clampedFloat(diff.fCurrentValue);
		factor1=outGain*factor;
		factor2=outGain*sqrtf(1.f-factor*factor);
		break; }
	case Tags::MOD_GAIN: {
		auto f = scaledFloat(diff.fCurrentValue,SCALE_MIN,SCALE_MAX);
		oscGain=dbToLinear(f)*0.95;
		break; }
	case Tags::OUT_GAIN: {
		auto g = scaledFloat(diff.fCurrentValue,SCALE_MIN,SCALE_MAX);
		outGain=dbToLinear(g);
		factor1=outGain*factor;
		factor2=outGain*sqrtf(1.f-factor*factor);
		break; }

	case kJBox_AudioInputConnected:
	case kJBox_AudioOutputConnected:
		trace("Audio connected");
		break;
	}


}

float32 Smearer::operator()(const float32 buf,const float32 mul) const {
	return buf*mix_ext + mul*mix_int + buf*mul*mix_prod;
}

void Smearer::proc(Channel &ch) {
	ch.read(buffer.data());
	for(auto i=0;i<BUFFER_SIZE;i++) buffer[i]*=factor1*osc[i]+factor2;
	limiter.limit(buffer.data(),BUFFER_SIZE);
	ch.write(lBuffer.data());
}

void Smearer::process() {

	if(!initialised) {
		oscillator.reseed(transportPosition());
		//oscillator.setSilence(0.5);
		initialised=true;
	}


	switch(state) {
	case State::On: {
		for(auto i=0;i<BUFFER_SIZE;i++) osc[i]=oscGain*oscillator(); //(1.f-factor)+factor*oscillator();
		filter.filter(osc);

		proc(left);
		proc(right);

		break; }
	case State::Bypassed:
		if(left.read(buffer.data())>0) left.write(buffer.data());
		if(right.read(buffer.data())>0) right.write(buffer.data());
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
