// fms_bootstrap_extend.h - Bootstrap extension to piecewise constant forward curves.
// https://github.com/keithalewis/papers/blob/master/bootstrap.pdf
#pragma once
#include <limits>
#include <utility>
#include "../fms_sequence/fms_sequence.h"
#include "fms_pwflat.h"

namespace fms::bootstrap {

	template<class X>
	constexpr X NaN = std::numeric_limits<X>::quiet_NaN();

	// Extend curve having one cash flow past the end of the curve.
	// p = sum_{u_j < u} c_j D_j + cu Du exp(-f du) = pv + cu Du exp(-f du); 
	template<class P, class C, class T>
	inline C extend1(P p, P pv, C cu, P Du, T du)
	{
		return  - log((p - pv) / (cu*Du)) / du;
	}

	// Extend curve having two cash flows past the end of the curve
	// 0 = c0 D0 + c1 D1, Dj = D(u) exp(-f (uj - u))
	template<class C, class T>
	inline C extend2(C c0, T u0, C c1, T u1)
	{
		return  log(-c1/c0)/(u1 - u0);
	}

	// Extrapolate forward curve for given a price and instrument.
	// p = sum_{u_j <= t} c_j D_j + sum_{u_k > t} c_k D(t) exp(-f (u_k - t)) = pv_ + _pv
	template<class P, class T, class C>
	inline std::pair<T, C> extend(pwflat::forward<T,C>& f, const T& t, const P& p, T u, C c)
	{
        using fms::sequence::apply;
        using fms::sequence::filter;
        using fms::sequence::sum;

		// set extrapolated value to NaN
		f.extrapolate();

		// discount function
		auto D = [&f](const T& t) { return f.discount(t); };

		// Cash flow times up to t.
		auto u_ = filter([t](auto _u) { return _u <= t; }, u);		
		auto pv_ = sum(c * apply(D, u_));

		auto n_ = length(u_);
		auto _u = skip(n_, u);
		auto _c = skip(n_, c);
		auto _n = length(_u); // remaining cash flows

		if (_n == 0) {
			return std::pair(NaN<decltype(*u)>, NaN<decltype(*c)>);
		}
		if (_n == 1) {
			return std::pair(*_u, extend1(p, pv_, *_c, D(t), *_u - t));
		}
		if (_n == 2 and (p - pv_) + 1 == 1) {
			auto u0 = *_u;
			auto u1 = *++_u;
			auto c0 = *_c;
			auto c1 = *++_c;

			return std::pair(u1, extend2(c0, u0, c1, u1));
		}
		
		auto _pv = [_u, _c, &f](C _f) { f.extrapolate(_f);  return sum(_c, apply(D, _u)); };

		C f0 = 0.01, f1 = 0.02; // initial guesses for secant
		auto _pv0 = _pv(f0);
		auto _pv1 = _pv(f1);
		/*
		// Find root using secant method.
		while (fabs(-p + pv_ + _pv(f)) >= .00001) {
			m = a / b;
			f_ = f + m * (f - f_);
			std::swap(f, f_);
		}
		*/
		
		return std::pair<decltype(*u),decltype(*c)>(0, 0);

	}

}