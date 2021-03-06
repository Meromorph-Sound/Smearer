/*
 * Random.cpp
 *
 *  Created on: 14 Dec 2020
 *      Author: julianporter
 */

#include "Random.hpp"
#include <cstdint>

namespace meromorph {

const float32 RNDBase::I32Max = (float32)UINT32_MAX;

//static const uint64 sconst[] = {
//0x37e1c9b5e1a2b843, 0x56e9d7a3d6234c87, 0xc361be549a24e8c7, 0xd25b9768a1582d7b,
//0x18b2547d3de29b67, 0xc1752836875c29ad, 0x4e85ba61e814cd25, 0x17489dc6729386c1,
//0x7c1563ad89c2a65d, 0xcdb798e4ed82c675, 0xd98b72e4b4e682c1, 0xdacb7524e4b3927d,
//0x53a8e9d7d1b5c827, 0xe28459db142e98a7, 0x72c1b3461e4569db, 0x1864e2d745e3b169,
//0x6a2c143bdec97213, 0xb5e1d923d741a985, 0xb4875e967bc63d19, 0x92b64d5a82db4697,
//0x7cae812d896eb1a5, 0xb53827d41769542d, 0x6d89b42c68a31db5, 0x75e26d434e2986d5,
//0x7c82643d293cb865, 0x64c3bd82e8637a95, 0x2895c34d9dc83e61, 0xa7d58c34dea35721,
//0x3dbc5e687c8e61d5, 0xb468a235e6d2b193,
//};
//
//union Float2Int {
//	float64 f;
//	uint64 i;
//
//	Float2Int(const float32 ff) : f(ff) {};
//};
//
//uint64 asInteger(const float32 ff) { return Float2Int(ff).i; }
//
//uint64 generateSeed(const uint64 initial) {
//
//   /* initialize state for local msws rng */
//
//   auto r = initial / 100000000;
//   auto t = initial % 100000000;
//   auto ss = sconst[r%30];
//   r /= 30;
//   auto xx = t*ss + r*ss*100000000;
//   MSWS msws(xx,xx,ss);
//
//   /* get odd random number for low order digit */
//
//   auto u = (msws() % 8) * 2 + 1;
//   auto v = (1<<u);
//
//   /* get rest of digits */
//
//   for (auto m=60,c=0;m>0;) {
//      auto j = msws();                /* get 8 digit 32-bit random word */
//      for (auto i=0;i<32;i+=4) {
//         auto k = (j>>i) & 0xf;        /* get a digit */
//         if (k!=0 && (c & (1<<k)) == 0) { /* not 0 and not previous */
//            c |= (1<<k);
//            u |= (k<<m);          /* add digit to output */
//            m -= 4;
//	    if (m==24 || m==28) c = (1<<k) | v;
//            if (m==0) break;
//         }
//      }
//   }
//   return u;
//}


Generator::Generator(const std::vector<float32> &ins) {
	for(auto it=ins.begin();it!=ins.end();it++) (*this)(*it);
}
uint64 Generator::operator()(const float32 f) {
	conv.f=conv.f+exp(f);
	auto i=conv.i;
	conv.i=(i>>32) | (i<<32);
	return conv.i;
}

/* local copy of msws rng */

uint32 MSWS::operator()() {
		x *= x;
		x += (w += s);
		x = (x>>32) | (x<<32);
		return (uint32)x;
	}
void MSWS::reset(const uint64 x_,const uint64 w_,const uint64 s_) {
	x=x_;
	w=w_;
	s=s_;
}

float32 Random::next() {
	return lower+(upper-lower)*nextFloat();
}



void RNDBase::init(const uint64 n) {
	rng.reset(0,0,n);
}
void RNDBase::reseed(const uint64 n) {
	rng.reset(0,0,n);
}




} /* namespace meromorph */
