// fms_instrument_swap.h - Interest rate swap.
// A swap is determined by (maturity, frequency, coupon). It has cashflows
// -1 at 0, coupon/frequency, at times i/frequency for i = 1, 2, ..., n - 1,
// and 1 + coupon/frequence at maturity = n/frequency.
// Time is measured in years. Frequency is the number of coupons per year.
#pragma once
#include "fms_instrument_sequence.h"

namespace fms::instrument {
	
	template<class U = double, class F = double, class C = double>
	//Implement helper functions.
	//auto make_time(....) -> (0, 1/freq,  ..., maturity)
	auto make_time(const U& maturity, const F& frequency) {
		assert(maturity > 0);
		assert(frequency > 0);
		fms::sequence::list<double> tm({ 0 });
		int i;
		for (i = 1; double(i) / frequency < maturity; i++) {
			tm.push_back(double(i) / frequency);
		}

	// auto make_cash(....) -> (-1, c/freq, ..., 1 + c/freq)
	auto make_cash(const U & maturity, const F & frequency, const C & coupon) {
		assert(maturity > 0);
		assert(frequency > 0);
		fms::sequence::list<double> cs({ -1 });
		int i;
		for (i = 1; double(i) / frequency < maturity; i++) {
			cs.push_back(coupon / frequency);
		}
		if (std::abs(double(i) / frequency - maturity) < std::numeric_limits<U>::epsilon()) {
			cs.push_back(coupon / frequency + 1);
		}
		else {
			cs.push_back(1);
		}
		return cs;
	}

	//Implement the class interest_rate_swap in namespace fms::instrument
	struct interest_rate_swap : public sequence<fms::sequence::list<U>, fms::sequence::list<C>> {
	interest_rate_swap(U maturity, F frequency, C coupon)
			: sequence<fms::sequence::list<U>, fms::sequence::list<C>>(
				make_time(maturity, frequency), make_cash(maturity, frequency, coupon)
				)
		{ }
	};
}
