// fms_instrument_swap.h - Interest rate swap.
// A swap is determined by (maturity, frequency, coupon). It has cashflows
// -1 at 0, coupon/frequency, at times i/frequency for i = 1, 2, ..., n - 1,
// and 1 + coupon/frequence at maturity = n/frequency.
// Time is measured in years. Frequency is the number of coupons per year.
#pragma once
#include "fms_instrument_sequence.h"

namespace fms::instrument {
	
	//Implement helper functions.
	//	auto make_time(....) -> (0, 1/freq,  ..., maturity)
	auto make_time(t);
	t = n / frequency;
	++n;
	assert(maturity == t);
	// auto make_cash(....) -> (-1, c/freq, ..., 1 + c/freq)
	auto make_cash(c) = c / frequency;
	++n;
	assert(maturity == make_cash());

	//Implement the class interest_rate_swap in namespace fms::instrument
	

	template<class U = double, class C = double>
	struct interest_rate_swap : public sequence<fms::sequence::list<U>, fms::sequence::list<C>>{
	interest_rate_swap(U maturity, U frequency, C coupon)
			: sequence<fms::sequence::list<U>, fms::sequence::list<C>>, fms::sequence::list<F>>(
				fms::sequence::list<U>({ 0, maturity }), fms::sequence::list<C>({ -1, 1 + coupon / frequency })
		{ }
	};

	
	
	


}
