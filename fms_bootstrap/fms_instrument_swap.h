// fms_instrument_swap.h - Interest rate swap.
// A swap is determined by (maturity, frequency, coupon). It has cashflows
// -1 at 0, coupon/frequency, at times i/frequency for i = 1, 2, ..., n - 1,
// and 1 + coupon/frequence at maturity = n/frequency.
// Time is measured in years. Frequency is the number of coupons per year.
#pragma once
#include "fms_instrument_sequence.h"
#include"cassert"
#include<list>


namespace fms::instrument {
	template<class U = double, class C = double>

	//!!! Implement helper functions.
		// auto make_time(....) -> (0, 1/freq,  ..., maturity)
	auto make_time(U maturity, U frequency) {

		fms::sequence::list<U> temp{(0)};

		assert(maturity > 0);
		assert(frequency > 0);

		for (int i = 1; i < frequency * maturity; i++) {
			temp.push_back(i / frequency);
		}
		temp.push_back(maturity);
		return temp;
	}
	// auto make_cash(....) -> (-1, c/freq, ..., 1 + c/freq)
	template<class U = double, class C = double>
	auto make_cash(U maturity, U frequency, C coupon) {
		fms::sequence::list<C> temp{(-1)};

		assert(maturity > 0);
		assert(frequency > 0);
		assert(coupon > 0);

		for (int i = 1; i < frequency * maturity; i++) {
			temp.push_back(coupon / frequency);
		}
		temp.push_back(1 + coupon / frequency);
		return temp;
	}
	template<class U = double, class C = double>
	struct interest_rate_swap : public sequence<fms::sequence::list<U>, fms::sequence::list<C>> {
		interest_rate_swap(U maturity, U frequency, C coupon)
			: sequence<fms::sequence::list<U>, fms::sequence::list<C>>(
				make_time(maturity, frequency), make_cash(maturity, frequency, coupon)
				)
		{ }
		
		
	};

}




