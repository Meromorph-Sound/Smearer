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

	auto state0=last0;
	auto state1=last1;

	auto p0 = (order==1) ? alpha : alpha*16.f;
	auto p1 = (order==1) ? 0 : alpha3;
	auto n = (order==1) ? alpha : alpha3;


		std::transform(vector.begin(),vector.end(),vector.begin(),[p0,p1,n,&state0,&state1](float32 x) {
			auto s= n*x - p0*state0 - p1*state1;
			state1=state0;
			state0=s;
			return s;
		});
		last0=state0;
		last1=state1;


}



} /* namespace smearer */
} /* namespace meromorph */
