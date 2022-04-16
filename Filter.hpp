/*
 * Filter.hpp
 *
 *  Created on: 11 Dec 2021
 *      Author: julianporter
 */

#ifndef FILTER_HPP_
#define FILTER_HPP_

#include "base.hpp"

namespace meromorph {
namespace smearer {

template <typename T>
class Filter {

private:
	bool active = false;
	float32 omega = 1;
	float32 rho = 0;
	float32 par0 = 0,par1 = 0;
	T last = 0,last2 = 0;
	uint32 order = 1;

	void setParameters() {
		par0 = omega*rho;
		par1 = omega-par0;
	}


	void filter1(std::vector<T> &vector) {
		if(!active) return;

		auto state1=last;
		auto p0 = par0;
		auto p1 = par1;

		std::transform(vector.begin(),vector.end(),vector.begin(),[p0,p1,&state1](T x) {
			auto s= p0*x + p1*state1;
			state1=s;
			return s;
		});
		last=state1;
	}

	void filter2(std::vector<T> &vector) {
		if(!active) return;

		auto state1=last;
		auto state2=last2;
		auto p0 = par0;
		auto p2 = par1;

		std::transform(vector.begin(),vector.end(),vector.begin(),[p0,p2,&state1,&state2](T x) {
			auto s= p0*x + p2*state2;
			state2=state1;
			state1=s;
			return s;
		});
		last=state1;
		last2=state2;
	}

public:
	Filter() {};
	virtual ~Filter() = default;
	Filter(const Filter &other) = default;
	Filter(Filter &&other) = default;
	Filter& operator=(const Filter &other) = default;
	Filter& operator=(Filter &&other) = default;

	void setActive(const bool b) {
		active=b;
		last=0;
		last2=0;
	}
	void setQ(const float32 q) { rho=q; setParameters(); }
	void setWidth(const float32 w) { omega=w; setParameters(); }
	void setOrder(uint32 o) {
		order=o;
		last=0;
		last2=0;
	}

	void filter(std::vector<T> &vector) {
		if(!active) return;

		auto state1=last;
		auto state2=last2;
		auto p0 = par0;
		auto p1 = (order==1) ? par1 : 0;
		auto p2 = (order==1) ? 0 : par1;

		std::transform(vector.begin(),vector.end(),vector.begin(),[p0,p1,p2,&state1,&state2](T x) {
			auto s= p0*x + p1*state1 + p2*state2;
			state2=state1;
			state1=s;
			return s;
		});

		last=state1;
		last2=state2;
	}

};

} /* namespace smearer */
} /* namespace meromorph */

#endif /* FILTER_HPP_ */
