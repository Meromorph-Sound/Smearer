/*
 * Filter.cpp
 *
 *  Created on: 11 Dec 2021
 *      Author: julianporter
 */

#include "Filter.hpp"

namespace meromorph {
namespace smearer {


void Filter::reset() {
	last0=0.f;
	last1=0.f;
}

void Filter::setActive(const bool b) {
	active=b;
	reset();
}


void Filter::setOrder(const uint32 o) {
	order=o;
	reset();
}

void Filter::setAlpha(const float32 a) {
	alpha = clamp(a);
	alpha3= powf(alpha,3.f);
}

void Filter::filter(std::vector<float32> &vector) {
	if(!active) return;

	if(order==1) {
		auto state=last0;
		auto p = alpha;

		std::transform(vector.begin(),vector.end(),vector.begin(),[p,&state](float32 x) {
			auto s= x + p*state;
			state=s;
			return s;
		});
		last0=state;
	}
	else {
		auto state0=last0;
		auto state1=last1;
		auto p = alpha*0.5f;
		auto p3= alpha3;

		std::transform(vector.begin(),vector.end(),vector.begin(),[p,p3,&state0,&state1](float32 x) {
			auto s= x + p3*state0 + p*state1;
			state1=state0;
			state0=s;
			return s;
		});
		last0=state0;
		last1=state1;
	}

}



} /* namespace smearer */
} /* namespace meromorph */
