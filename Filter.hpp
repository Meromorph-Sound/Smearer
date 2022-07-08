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
	bool active = false;
	float32 omega = 1;
	float32 rho = 0;
	float32 alpha = 0;
	float32 alpha3 = 0;
	float32 last0 = 0,last1 = 0;
	uint32 order = 1;

	void reset();


public:
	Filter() {};
	virtual ~Filter() = default;
	Filter(const Filter &other) = default;
	Filter(Filter &&other) = default;
	Filter& operator=(const Filter &other) = default;
	Filter& operator=(Filter &&other) = default;

	void setActive(const bool b);
	void setOrder(const uint32);
	void setAlpha(const float32 a) ;
	void filter(std::vector<float32> &vector);

};

} /* namespace smearer */
} /* namespace meromorph */

#endif /* FILTER_HPP_ */
