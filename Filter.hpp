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
	float32 param;
	float32 last;

public:
	Filter() : active(false), param(2*Pi), last(0) {};
	virtual ~Filter() = default;
	Filter(const Filter &other) = default;
	Filter(Filter &&other) = default;
	Filter& operator=(const Filter &other) = default;
	Filter& operator=(Filter &&other) = default;

	void setActive(const bool b);
	void setParam(const float32 p);

	void filter(float32 *data,const uint32 n);
	void filter(std::vector<float32> &vector);
};

} /* namespace smearer */
} /* namespace meromorph */

#endif /* FILTER_HPP_ */
