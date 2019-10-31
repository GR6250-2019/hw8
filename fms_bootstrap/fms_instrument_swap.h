// fms_instrument_swap.h - Interest rate swap.
// A swap is determined by (maturity, frequency, coupon). It has cashflows
// -1 at 0, coupon/frequency, at times i/frequency for i = 1, 2, ..., n - 1,
// and 1 + coupon/frequence at maturity = n/frequency.
// Time is measured in years. Frequency is the number of coupons per year.
// n = maturity*frequency
#pragma once
#include "fms_instrument_sequence.h"

namespace fms::instrument {
	template<class U = double>

	//!!! Implement helper functions.
	// auto make_time(....) -> (0, 1/freq,  ..., maturity)
	// auto make_cash(....) -> (-1, c/freq, ..., 1 + c/freq)
	auto make_time(U frequency,U maturity) {
		int n = (int)( maturity * frequency );
		//typename U::fms::sequence::list times;
		fms::sequence::list<U> times({ 0 });
		
		for (double i = 1; i < n; i = i + 1) {
			times.push_back(i / frequency);
		}
		times.push_back(maturity);

		return times;
	};
	template<class U = double, class C = double>
	auto make_cash( U maturity , U frequency,C coupon) {
		int n = (int)(maturity * frequency );
		fms::sequence::list<C> cash({ -1. });
		//cash.push_back(-1);
		for (int i = 1; i < n; i = i + 1) {
			cash.push_back(coupon / frequency);
		}
		cash.push_back(1 + coupon / frequency);

		return cash;
	};
	//!!! Implement the class interest_rate_swap in namespace fms::instrument.
	template<class U = double, class C = double>
	struct interest_rate_swap : public sequence<fms::sequence::list<U>, fms::sequence::list<U>> {
		interest_rate_swap(U maturity, U frequency, C coupon)
			: sequence<fms::sequence::list<U>, fms::sequence::list<C>>(
				make_time(frequency, maturity),make_cash(frequency, coupon, maturity)
				)
		{ }
	};
}
