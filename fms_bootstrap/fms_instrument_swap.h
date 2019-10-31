  // fms_instrument_swap.h - Interest rate swap.
// A swap is determined by (maturity, frequency, coupon). It has cashflows
// -1 at 0, coupon/frequency, at times i/frequency for i = 1, 2, ..., n - 1,
// and 1 + coupon/frequence at maturity = n/frequency.
// Time is measured in years. Frequency is the number of coupons per year.
#pragma once
#include "fms_instrument_sequence.h"
#include <list>
#include <iostream>

namespace fms::instrument {
	
	//!!! Implement helper functions.
	template<class U = double, class C = double>
	auto make_time(U m, U f) {
		std::vector<U> myList = {};
		for (int i = 0; i <= m * f; i++) {
			if (i == 0){
				myList.push_back(i);
			}
			else {
				myList.push_back(i / f);
			}
		 }
		return myList;
		//(0, 1 / freq, ..., maturity)
	}

	template<class U = double, class C = double>
	auto make_cash(U m, U f, C c) {
		std::vector<U> myList2 = {};
		for (int i = 0; i <= m * f; i++) {
			if (i == 0) {
				myList2.push_back(-1);
			}
			else if (i == m * f) {
				myList2.push_back(1 + c / f);
			}
			else {
				myList2.push_back(c / f);
			}
		}
		return myList2;
		//(-1, c/freq, ..., 1 + c/freq)
	}

	//!!! Implement the class interest_rate_swap in namespace fms::instrument.
	template<class U = double, class C = double>
	struct interest_rate_swap : public sequence<fms::sequence::list<U>, fms::sequence::list<C>> {
		interest_rate_swap(U maturity, U frequency, C coupon)
			: sequence<fms::sequence::list<U>, fms::sequence::list<C>>(
				fms::sequence::list<U>(make_time(maturity, frequency)), fms::sequence::list<C>(make_cash(maturity, frequency, coupon))
				)
		{ }
	};
}
