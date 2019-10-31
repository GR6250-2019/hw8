// fms_instrument_swap.h - Interest rate swap.
// A swap is determined by (maturity, frequency, coupon). It has cashflows
// -1 at 0, coupon/frequency, at times i/frequency for i = 1, 2, ..., n - 1,
// and 1 + coupon/frequence at maturity = n/frequency.
// Time is measured in years. Frequency is the number of coupons per year.
#pragma once
#include "fms_instrument_sequence.h"

namespace fms::instrument {

	//!!! Implement helper functions.
	template<class U = double, class C = double>
	auto make_time(U maturity, U frequency) {
		std::vector<U> time;
		
		int i;
		for (i = 0; i < maturity*frequency+1; i++) {
			time.push_back(i / frequency) ;

		}
		return time;
	}

	template<class U = double, class C = double>
	auto make_cash(U maturity, U frequency, C coupon) {

		std::vector<C> cf;
		
		cf.push_back(-1);
		int i;
		for (i = 1; i < maturity*frequency ; i++) {

			cf.push_back(coupon/frequency) ;

		}
		cf.push_back(1 + coupon / frequency);
		return cf;

	}

	//!!! Implement the class interest_rate_swap in namespace fms::instrument.


	template<class U = double, class C = double>
	struct swap : public sequence<fms::sequence::list<U>, fms::sequence::list<C>> {
		swap(U maturity, U frequency, C coupon)
			:sequence<fms::sequence::list<U>, fms::sequence::list<C>>(
				fms::sequence::list<U>(make_time(maturity, frequency)), fms::sequence::list<C>(make_cash(maturity, frequency, coupon)))

		{ }
	};




}
