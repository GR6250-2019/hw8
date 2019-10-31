// fms_instrument_swap.h - Interest rate swap.
// A swap is determined by (maturity, frequency, coupon). It has cashflows
// -1 at 0, coupon/frequency, at times i/frequency for i = 1, 2, ..., n - 1,
// and 1 + coupon/frequence at maturity = n/frequency.
// Time is measured in years. Frequency is the number of coupons per year.
#pragma once
#include "fms_instrument_sequence.h"
#include <cassert>
#include <vector>

namespace fms::instrument {
	
	//!!! Implement helper functions.
	// auto make_time(....) -> (0, 1/freq,  ..., maturity)
	// auto make_cash(....) -> (-1, c/freq, ..., 1 + c/freq)

	template<class U = double, class C = double>
	auto make_time(U maturity, U frequency) {
		
		assert(frequency != 0);

		std::vector<U> times;
		for (int i = 0; i < maturity * frequency; i++) {
			times.push_back(i / frequency);
		}
		times.push_back(maturity);

		return times;
	}

	template<class U = double, class C = double>
	auto make_cash(U maturity, U frequency, C coupon) {
		assert(frequency != 0);

		std::vector<C> cash;
		cash.push_back(-1);
		for (int i = 1; i < maturity * frequency; i++) {
			cash.push_back(coupon / frequency);
		}
		cash.push_back(1 + coupon / frequency);

		return cash;
	}
	
	//!!! Implement the class interest_rate_swap in namespace fms::instrument.

	template<class U = double, class C = double>
	struct interest_rate_swap : public sequence<fms::sequence::list<U>, fms::sequence::list<C>> {
		interest_rate_swap(U maturity, U frequency, C coupon)
			: sequence<fms::sequence::list<U>, fms::sequence::list<C>>(
				fms::sequence::list<U>(make_time(maturity, frequency)), fms::sequence::list<C>(make_cash(maturity, frequency, coupon))
				)
		{ }
	};

}
