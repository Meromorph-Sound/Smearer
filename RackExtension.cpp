#include <cmath>
#include <cstring>
#include "RackExtension.hpp"
#include <algorithm>

namespace meromorph {


const uint32 RackExtension::BUFFER_SIZE = 64;


RackExtension::RackExtension() : buffer(RackExtension::BUFFER_SIZE) {
	props=JBox_GetMotherboardObjectRef("/custom_properties");
	transport=JBox_GetMotherboardObjectRef("/transport");
	noteState = JBox_GetMotherboardObjectRef("/note_states");
}


float32 RackExtension::transportPosition() {
	auto val=JBox_LoadMOMPropertyByTag(transport,kJBox_TransportPlayPos);
	return toFloat(val);

}


void RackExtension::processMIDIEvent(const TJBox_PropertyDiff &diff) {
	auto event = JBox_AsNoteEvent(diff);
	if(forwarding) JBox_OutputNoteEvent(event); // forwarding notes
}

 void RackExtension::processSystemCall(const TJBox_PropertyDiff &diff) {

	auto tag = diff.fPropertyTag;
	switch(tag) {
		case kJBox_EnvironmentSystemSampleRate: {
			trace("Sample rate......");
			auto sampleRate = toFloat(diff.fCurrentValue);
			setSampleRate(sampleRate);
			break; }
		case kJBox_EnvironmentMasterTune: {
			trace("Master tune......");
			auto masterTune  = toFloat(diff.fCurrentValue)/100.0;
			setMasterTune(masterTune);
			break; }
		case kJBox_TransportRequestResetAudio:
			trace("Reset request");
			reset();
			break;
	}
}

void RackExtension::RenderBatch(const TJBox_PropertyDiff diffs[], TJBox_UInt32 nDiffs) {
	for(auto i=0;i<nDiffs;i++) {
		auto diff=diffs[i];
		if(diff.fPropertyRef.fObject == noteState) processMIDIEvent(diff);
		else {
			processSystemCall(diff);
			processApplicationMessage(diff);
		}
	}
	process();
}

}


