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
	float32 par0 = 0,par1 = 0;
	float32 last = 0,last2 = 0;
	uint32 order = 1;

	void setParameters();
	void filter1(std::vector<float32> &vector);
	void filter2(std::vector<float32> &vector);

public:
	Filter() {};
	virtual ~Filter() = default;
	Filter(const Filter &other) = default;
	Filter(Filter &&other) = default;
	Filter& operator=(const Filter &other) = default;
	Filter& operator=(Filter &&other) = default;

	void setActive(const bool b);
	void setQ(const float32 q);
	void setWidth(const float32 w);
	void setOrder(uint32 o);

	void filter(std::vector<float32> &vector);

};

} /* namespace smearer */
} /* namespace meromorph */

#endif /* FILTER_HPP_ */
