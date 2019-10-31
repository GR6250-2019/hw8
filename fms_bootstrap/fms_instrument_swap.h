// fms_instrument_swap.h - Interest rate swap.
// A swap is determined by (maturity, frequency, coupon). It has cashflows
// -1 at 0, coupon/frequency, at times i/frequency for i = 1, 2, ..., n - 1,
// and 1 + coupon/frequence at maturity = n/frequency.
// Time is measured in years. Frequency is the number of coupons per year.
#pragma once
#include "fms_instrument_sequence.h"

namespace fms::instrument {
	
	//!!! Implement helper functions.
	// auto make_time(....) -> (0, 1/freq,  ..., maturity)
	// auto make_cash(....) -> (-1, c/freq, ..., 1 + c/freq)

	//!!! Implement the class interest_rate_swap in namespace fms::instrument.

	template<class U = double, class C = double, class T=int>
	struct interest_rate_swap : public sequence<fms::sequence::list<U>, fms::sequence::list<C>> {
		interest_rate_swap(U maturity, T frequency, C coupon)
			: sequence<fms::sequence::list<U>, fms::sequence::list<C>>(
				make_time(maturity, frequency), make_cash(maturity,frequency,coupon)
				)
		{ }
		
		auto make_time(const U &maturity, const T &frequency) {
			assert(maturity >0);
			assert(frequency > 0);
			typename U::fms::sequency::list res();
			res.push_back(0);
			int i;
			for (i = 1; i / frequency < maturity; i++) {
				res.push_back(i / frequency);				
			}
			if (std::abs(i / frequency - maturity) < std::numeric_limits<U>::epsilon()) {
				
			}
			else {
				res.push_back(maturity);
			}
			return res;
		}
		auto make_cash(const U &maturity, const T &frequency, const C &coupon) {
			assert(maturity > 0);
			assert(frequency > 0);
			typename U::fms::sequency::list res();
			res.push_back(-1);
			int i;
			for (i = 1; i / frequency < maturity; i++) {
				res.push_back(coupon / frequency);
			}
			if (std::abs(i / frequency - maturity) < std::numeric_limits<U>::epsilon()) {
				res[res.size() - 1] += 1;
			}
			else {
				res.push_back(1);
			}
			return res;
		}
	};
}
