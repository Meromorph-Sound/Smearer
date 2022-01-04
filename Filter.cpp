/*
 * Filter.cpp
 *
 *  Created on: 11 Dec 2021
 *      Author: julianporter
 */

#include "Filter.hpp"

namespace meromorph {
namespace smearer {

void Filter::setParameters() {
	par0 = omega*rho;
	auto other=omega-par0;
	par1 = (order==1) ? other : 0;
	par2 = (order==2) ? other : 0;
}

void Filter::setActive(const bool b) {
	active=b;
	last=0;
	last2=0;
}


void Filter::setQ(const float32 q) { rho=q; setParameters(); }
void Filter::setWidth(const float32 w) { omega=w; setParameters(); }
void Filter::setOrder(uint32 o) { order=o; setParameters(); }

void Filter::filter(std::vector<float32> &vector) {
	if(!active) return;
	else {
		auto state1=last;
		auto state2=last2;

		auto p0 = par0;
		auto p1 = par1;
		auto p2 = par2;

		std::transform(vector.begin(),vector.end(),vector.begin(),[p0,p1,p2,&state1,&state2](float32 x) {
			auto s= p0*x + p1*state1 + p2*state2;
			state2=state1;
			state1=s;
			return s;
		});
		last=state1;
		last2=state2;



	}
}

} /* namespace smearer */
} /* namespace meromorph */
