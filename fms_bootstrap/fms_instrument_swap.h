// fms_instrument_swap.h - Interest rate swap.
// A swap is determined by (maturity, frequency, coupon). It has cashflows
// -1 at 0, coupon/frequency, at times i/frequency for i = 1, 2, ..., n - 1,
// and 1 + coupon/frequence at maturity = n/frequency.
// Time is measured in years. Frequency is the number of coupons per year.
#pragma once
#include "fms_instrument_sequence.h"

namespace fms::instrument {
	template<class U>
	auto make_time(U maturity, U frequency) {
		static std::vector<U> time;
		static int n = (int) std::round(maturity * frequency);

		for (int i = 0; i <= n; i++) {
			time.push_back(i / frequency);
		}
		return fms::sequence::list(time);
	}

	template<class U, class C>
	auto make_cash(U maturity, U frequency, C coupon) {
		static std::vector<C> cash;
		static int n = (int) std::round(maturity * frequency);
		static C each_coupon = coupon / frequency;

		cash.push_back(-1);
		for (int i = 1; i < n; i++) {
			cash.push_back(each_coupon);
		}
		cash.push_back(1 + each_coupon);
		return fms::sequence::list(cash);
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
