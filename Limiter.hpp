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
	bool didLimit;

	static constexpr float32 SOFT_THRESHOLD=0.15;
	static constexpr float32 epsilon=1.0e-5;
public:

	Limiter() : scale(1.0), mode(Mode::HARD), active(true), didLimit(false) {};
	virtual ~Limiter() = default;
	Limiter(const Limiter &other) = default;
	Limiter& operator=(const Limiter &other) = default;

	void setLimit(const float32 s) { scale=s; }
	void setMode(const Mode m) { mode=m; }
	void setActive(const bool a) { active=a; }

	template<typename T>
	bool limit(T *data,const uint32 n) {
		didLimit=false;
		if(!active) return false;

		switch(mode) {
		case Mode::SOFT:
			for(auto i=0;i<n;i++) {
				auto in = data[i];
				auto d=scale*tanh(in/scale);
				data[i]=d;
				didLimit = didLimit || (abs(d-in)>SOFT_THRESHOLD);
			}
			break;
		case Mode::HARD:
			for(auto i=0;i<n;i++) {
				auto n = std::max(scale,std::abs(data[i]));
				data[i]=data[i]/n;
				didLimit = didLimit || (n>1);
			}
			break;
		}
		return didLimit;
	}

};

struct Limiters {
protected:
	Limiter left;
	Limiter right;

public:
	Limiters() : left(), right() {}
	virtual ~Limiters() = default;
	Limiters(const Limiters &) = default;
	Limiters & operator=(const Limiters &) = default;

	void setLimit(const float32 s) { left.setLimit(s); right.setLimit(s); }
	void setMode(const Limiter::Mode m) { left.setMode(m); right.setMode(m); }
	void setActive(const bool a) { left.setActive(a); right.setActive(a); }

	template<typename T>
	bool limit(T *lData,T *rData,const uint32 n) {
		auto l = left.limit(lData,n);
		auto r = right.limit(rData,n);
		return l || r;
	}
	template<typename T>
	bool limit(std::vector<T> &l,std::vector<T> &r) { return limit(l.data(),r.data(),l.size()); }
};

template <typename T>
T max3(const T x,const T y,const T z) {
	return std::max(x,std::max(y,z));
}

class StereoLimiter {


private:

	float32 scale;
	Limiter::Mode mode;
	bool active;
	bool didLimit;

	static constexpr float32 SOFT_THRESHOLD=0.15;
	static constexpr float32 epsilon=1.0e-5;
public:

	StereoLimiter() : scale(1.0), mode(Limiter::Mode::HARD), active(true), didLimit(false) {};
	virtual ~StereoLimiter() = default;
	StereoLimiter(const StereoLimiter &other) = default;
	StereoLimiter& operator=(const StereoLimiter &other) = default;

	void setLimit(const float32 s) { scale=s; }
	void setMode(const Limiter::Mode m) { mode=m; }
	void setActive(const bool a) { active=a; }

	template<typename T>
	bool limit(T *left, T *right,const uint32 n) {
		didLimit=false;
		if(!active) return false;

		switch(mode) {
		case Limiter::Mode::SOFT:
			for(auto i=0;i<n;i++) {
				auto inL = left[i];
				auto inR = right[i];
				auto rmsScaled = hypot(inL,inR)*scale;
				auto dL = (rmsScaled==0) ? 0.f : rmsScaled*tanh(inL/rmsScaled);
				auto dR = (rmsScaled==0) ? 0.f : rmsScaled*tanh(inR/rmsScaled);
				left[i]=dL;
				right[i]=dR;
				didLimit = didLimit || (abs(dL-inL)>SOFT_THRESHOLD) || (abs(dR-inR)>SOFT_THRESHOLD);
			}
			break;
		case Limiter::Mode::HARD:
			for(auto i=0;i<n;i++) {
				auto n = max3(scale,std::fabs(left[i]),std::fabs(right[i]));
				left[i]=left[i]/n;
				right[i]=right[i]/n;
				didLimit = didLimit || (n>1);
			}
			break;
		}
		return didLimit;
	}

};

} /* namespace meromorph */

#endif /* LIMITER_HPP_ */
