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
	}

	void Filter::setParam(const float32 p) { param=p; }

void Filter::filter(float32 *data,const uint32 n) {
		if(!active) return;
		auto a = param;
		for(auto i=0;i<n;i++) {
			auto oN = a*last + data[n];
			last=oN;
			data[n]=oN;
		}
	}
void Filter::filter(std::vector<float32> &vector) {
	filter(vector.data(),vector.size());
}

} /* namespace smearer */
} /* namespace meromorph */
