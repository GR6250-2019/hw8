// fms_instrument_swap.h - Interest rate swap.
// A swap is determined by (maturity, frequency, coupon). It has cashflows
// -1 at 0, coupon/frequency, at times i/frequency for i = 1, 2, ..., n - 1,
// and 1 + coupon/frequence at maturity = n/frequency.
// Time is measured in years. Frequency is the number of coupons per year.
#pragma once
#include "fms_instrument_sequence.h"



namespace fms::instrument {

	

	template<class U = double, class C = double>
	struct interest_rate_swap : public sequence<fms::sequence::list<U>, fms::sequence::list<C>> {
		interest_rate_swap(U maturity, U frequency, C coupon)
			: sequence<fms::sequence::list<U>, fms::sequence::list<C>>(
				fms::sequence::list<U>(make_time(frequency, maturity)), fms::sequence::list<C>(make_cash(frequency, maturity, coupon))
				)
		{ }

		auto make_time(U freq, U matu)
		{

			std::vector<U> UU;
			int n = int(matu * freq);
			for (int i = 0; i <= n; i++) {
				UU.push_back(i / freq);
			}
			return UU;

		};

		auto make_cash(U freq, U matu, C coupon) {
			std::vector<C> CC;
			int n = int(matu * freq);
			CC.push_back(-1);
			for (int i = 1; i < n; i++) {
				CC.push_back(coupon / freq);
			}
			CC.push_back(1 + coupon / freq);
			return CC;
		};
	};
	//!!! Implement the class interest_rate_swap in namespace fms::instrument.

}



	//!!! Implement helper functions.
	// auto make_time(....) -> (0, 1/freq,  ..., maturity)
	// auto make_cash(....) -> (-1, c/freq, ..., 1 + c/freq)