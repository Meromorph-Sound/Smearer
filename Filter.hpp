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

class Filter {

private:
	bool active;
	float32 Q;
	float32 omega;
	float32 rho,rhoC;
	float32 last;
	float32 last2;

public:
	Filter() : active(false), Q(1), omega(1), rho(0), rhoC(1), last(0), last2(0) {};
	virtual ~Filter() = default;
	Filter(const Filter &other) = default;
	Filter(Filter &&other) = default;
	Filter& operator=(const Filter &other) = default;
	Filter& operator=(Filter &&other) = default;

	void setActive(const bool b);
	void setQ(const float32 p);
	void setWidth(const float32 f);

	void filter(std::vector<float32> &vector);
};

} /* namespace smearer */
} /* namespace meromorph */

#endif /* FILTER_HPP_ */
