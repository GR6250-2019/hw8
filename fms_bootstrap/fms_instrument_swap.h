// fms_instrument_swap.h - Interest rate swap.
// A swap is determined by (maturity, frequency, coupon). It has cashflows
// -1 at 0, coupon/frequency, at times i/frequency for i = 1, 2, ..., n - 1,
// and 1 + coupon/frequence at maturity = n/frequency.
// Time is measured in years. Frequency is the number of coupons per year.
#pragma once
#include "fms_instrument_sequence.h"


namespace fms::instrument {

	template<class U = double, class T = double>
	auto make_time(U maturity, T frequency) {
		fms::sequence::list<U> tsq{ (0) };

		for (int i = 1;i <= maturity * frequency;i++) {
			tsq.push_back(i * 1.0 / frequency);
		}
		return tsq;
	}

	template<class U = double, class T = double, class C = double>
	auto make_cash(U maturity, T frequency, C coupon) {
		fms::sequence::list<U> csq{ (-1) };

		for (int i = 1;i < maturity * frequency;i++) {
			csq.push_back(coupon / frequency);
		}
		csq.push_back(1 + coupon / frequency);
		return csq;
	}

	template<class U = double, class C = double,class T= double>
	struct swap : public sequence<fms::sequence::list<U>, fms::sequence::list<C>> {
		swap(U maturity, T frequency, C coupon)
			: sequence<fms::sequence::list<U>, fms::sequence::list<C>>(
				make_time(maturity, frequency), make_cash(maturity, frequency, coupon)
				)
		{ }
			

	};

	
}



	
	//!!! Implement helper functions.
	// auto make_time(....) -> (0, 1/freq,  ..., maturity)
	// auto make_cash(....) -> (-1, c/freq, ..., 1 + c/freq)

	//!!! Implement the class interest_rate_swap in namespace fms::instrument.

