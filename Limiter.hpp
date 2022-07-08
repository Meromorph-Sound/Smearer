/*
 * Limiter.hpp
 *
 *  Created on: 20 Feb 2021
 *      Author: julianporter
 */

#ifndef LIMITER_HPP_
#define LIMITER_HPP_

#import "base.hpp"

namespace meromorph {

class Limiter {
public:
	enum Mode : uint32 {
		HARD=1,
		SOFT=2
	};

private:

	float32 scale;
	Mode mode;
	bool active;

public:

	Limiter() : scale(1.0), mode(Mode::HARD), active(true) {};
	virtual ~Limiter() = default;
	Limiter(const Limiter &other) = default;
	Limiter& operator=(const Limiter &other) = default;

	void setLimit(const float32 s) { scale=s; }
	void setMode(const Mode m) { mode=m; }
	void setActive(const bool a) { active=a; }

	void limit(float32 *data,const uint32 n);
	void limit(std::vector<float32> &v);

};



} /* namespace meromorph */

#endif /* LIMITER_HPP_ */
