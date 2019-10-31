// fms_instrument_swap.h - Interest rate swap.
// A swap is determined by (maturity, frequency, coupon). It has cashflows
// -1 at 0, coupon/frequency, at times i/frequency for i = 1, 2, ..., n - 1,
// and 1 + coupon/frequence at maturity = n/frequency.
// Time is measured in years. Frequency is the number of coupons per year.
#pragma once
#include "fms_instrument_sequence.h"

template<class U = double, class C = double>
auto make_time(U frequency, U maturity)
{
	fms::sequence::list<U> time_series({ 0 });
	U n =frequency * maturity;
	for (int i = 1; i <= n; i++)
	{
		time_series.push_back(i / frequency);
	}
	return time_series;
}
template<class U = double, class C = double>
auto make_cash(U maturity, U frequency, C coupon)
{
	fms::sequence::list<C> cash_series({ -1 });
	C c = coupon / frequency;
	U n = frequency * maturity;
	for (int i = 1; i <= n-1; i++)
	{
		cash_series.push_back(c);
	}
	cash_series.push_back(1+c);
	return cash_series;
}

namespace fms::instrument {
	template<class U = double, class C = double>
	struct interest_rate_swap : public sequence<fms::sequence::list<U>, fms::sequence::list<C> > {
		interest_rate_swap(U maturity, U frequency, C coupon)
			:sequence<fms::sequence::list<U>, fms::sequence::list<C> >(
				fms::sequence::list<U>(make_time(frequency, maturity)), fms::sequence::list<C>(make_cash(maturity, frequency, coupon))
				)
				{}
		};
		//!!! Implement helper functions.
		// auto make_time(....) -> (0, 1/freq,  ..., maturity)
		// auto make_cash(....) -> (-1, c/freq, ..., 1 + c/freq)

		//!!! Implement the class interest_rate_swap in namespace fms::instrument.

}

