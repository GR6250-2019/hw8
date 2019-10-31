// fms_instrument_swap.h - Interest rate swap.
// A swap is determined by (maturity, frequency, coupon). It has cashflows
// -1 at 0, coupon/frequency, at times i/frequency for i = 1, 2, ..., n - 1,
// and 1 + coupon/frequence at maturity = n/frequency.
// Time is measured in years. Frequency is the number of coupons per year.
#pragma once
#include "fms_instrument_sequence.h"
#include <vector>

namespace fms::instrument {
	
	//!!! Implement helper functions.
	template<class U = double, class C = double>
	auto make_time(U freq, U maturity) {
		std::vector<U> time;
		for (int i = 0; i <= freq * maturity; i++)
			time.push_back(i / freq);
		return time;
	}//-> (0, 1/freq,  ..., maturity)
	template<class U = double, class C = double>
	auto make_cash(U freq, U maturity, C c) {
		std::vector<C> cash;
		cash.push_back(-1);
		for (int i = 1; i < maturity * freq ; i++)
			cash.push_back(c / freq);
		cash.push_back(1 + c/freq);
		return cash;
		
	}//-> (-1, c / freq, ..., 1 + c / freq)

	//!!! Implement the class interest_rate_swap in namespace fms::instrument.
	template<class U = double, class C = double>
	struct interest_rate_swap : public sequence<fms::sequence::list<U>, fms::sequence::list<C>> {
		interest_rate_swap(U maturity, U freq, C c)
			: sequence<fms::sequence::list<U>, fms::sequence::list<C>>(
				fms::sequence::list<U>( make_time(freq, maturity) ), fms::sequence::list<C>( make_cash(freq,maturity, c) )
				)
		{ }
	};
}
