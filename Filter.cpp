/*
 * Filter.cpp
 *
 *  Created on: 11 Dec 2021
 *      Author: julianporter
 */

#include "Filter.hpp"

namespace meromorph {
namespace smearer {

void Filter::setActive(const bool b) {
		active=b;
		last=0;
		last2=0;
	}


	void Filter::setQ(const float32 q) {
		rho=q;
		rhoC=1.f-q;
	}

	void Filter::filter(std::vector<float32> &vector) {
		if(!active) return;
		else {
			auto state1=last;
			auto state2=last2;
			auto p1=rho*rhoC;
			auto p2=rhoC;
			std::transform(vector.begin(),vector.end(),vector.begin(),[p1,p2,&state1,&state2](float32 x) {
				//auto s=rho*rho*x + rho*rhoC*state2 + rhoC*state1;
				auto s = x + p1*state2 + p2*state1;
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
