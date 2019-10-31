// fms_instrument_swap.h - Interest rate swap.
// A swap is determined by (maturity, frequency, coupon). It has cashflows
// -1 at 0, coupon/frequency, at times i/frequency for i = 1, 2, ..., n - 1,
// and 1 + coupon/frequence at maturity = n/frequency.
// Time is measured in years. Frequency is the number of coupons per year.
#pragma once
#include "fms_instrument_sequence.h"
#include <vector>
#include <cassert>


namespace fms::instrument {
	template<class U = double, class C = double>
	//!!! Implement helper functions.
	auto make_time(U maturity, U frequency) { //-> (0, 1/freq,  ..., maturity)
		assert(frequency != 0);
		std::vector<U> times;
		for (int i = 0; i <= maturity * frequency - 1; i++) {
			times.push_back(i / frequency);
		}
		times.push_back(maturity);
		return times;
	};
	

	// auto make_cash(....) -> (-1, c/freq, ..., 1 + c/freq)
	template<class U = double, class C = double>
	auto make_cash(U maturity, U frequency, C coupon) {
		assert(frequency != 0);
		std::vector<C> cashes;
		cashes.push_back(-1);
		for (int i = 1; i <= maturity * frequency - 1; i++) {
			cashes.push_back(coupon / frequency);
		}
		cashes.push_back(1 + coupon / frequency);
		return cashes;
	};

	//!!! Implement the class interest_rate_swap in namespace fms::instrument.


	template<class U = double, class C = double>
	struct swap_contract : public sequence<fms::sequence::list<U>, fms::sequence::list<C>> {
		swap_contract(U maturity,U frequency, C coupon)
			: sequence<fms::sequence::list<U>, fms::sequence::list<C>>(
				fms::sequence::list<U>(make_time(maturity, frequency)), fms::sequence::list<C>(make_cash(maturity, frequency, coupon))
				)
		{ }
	};
}
