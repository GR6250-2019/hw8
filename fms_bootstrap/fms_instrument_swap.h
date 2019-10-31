// fms_instrument_swap.h - Interest rate swap.
// A swap is determined by (maturity, frequency, coupon). It has cashflows
// -1 at 0, coupon/frequency, at times i/frequency for i = 1, 2, ..., n - 1,
// and 1 + coupon/frequence at maturity = n/frequency.
// Time is measured in years. Frequency is the number of coupons per year.
#pragma once 
 //!!! Implement helper functions.
 // auto make_time(....) -> (0, 1/freq,  ..., maturity)
 // auto make_cash(....) -> (-1, c/freq, ..., 1 + c/freq) //!!! Implement the class interest_rate_swap in namespace fms::instrument.
#include "fms_instrument_sequence.h"namespace fms::instrument {
template<class U = double, class T = int>
auto make_time(double maturity, double frequency) {
	fms::sequence::list<double> time({ 0 });
	for (int i = 1; i / frequency < maturity; i++) {
		time.push_back(i / frequency);
	}
	time.push_back(maturity);
	return time;
}
template<class U = double, class T = int, class C = double>
auto make_cash(double maturity, double frequency, double coupon) {
	fms::sequence::list<double> cash({ -1 });
	for (int i = 1; i / frequency < maturity; i++) {
		cash.push_back(coupon / frequency);
	}
	cash.push_back(1 + coupon / frequency);
	return cash;
} template<class U = double, class T = int, class C = double> struct interest_rate_swap : public sequence<fms::sequence::list<U>, fms::sequence::list<C>> {
	interest_rate_swap(U maturity, T frequency, C coupon)
		: sequence<fms::sequence::list<U>, fms::sequence::list<C>>(
			make_time(maturity, frequency), make_cash(maturity, frequency, coupon)
			)
	{ }
};
}