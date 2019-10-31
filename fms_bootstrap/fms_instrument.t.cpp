// fms_instrument.t.cpp - Test fms::instrument
#include <cassert>
#include "../fms_sequence/fms_sequence.h"
#include "fms_instrument.h"

using namespace fms::sequence;
using namespace fms::instrument;

template<class U, class C>
int test_instrument_sequence()
{
	sequence s(iota<U>(1), constant<C>(2));
	assert(s);
	auto p = std::pair<U, C>(1, 2);
	assert(p == *s);
	++s;
	++p.first;
	assert(p == *s);

	return 0;
}
int test_instrument_sequence_int_int = test_instrument_sequence<int, int>();

template<class U, class C>
int test_instrument_cd()
{
	cash_deposit<U, C> cd(2, 3);

	auto u = cd.time();
	assert(0 == *u);
	++u;
	assert(2 == *u);

	auto c = cd.cash();
	assert(-1 == *c);
	++c;
	assert(1 + 2 * 3 == *c);

	assert(std::pair(0, -1) == *cd);
	++cd;
	assert(std::pair(2, 1 + 2 * 3) == *cd);
	++cd;
	assert(!cd);

	return 0;
}
int test_instrument_cd_int_int = test_instrument_cd<int, int>();

template<class U, class C>
int test_instrument_fra()
{
	forward_rate_agreement<U, C> fra(2, 3 , 0.2);


	auto u = fra.time();
	assert(0. == *u);
	++u;
	assert(2. == *u);
	++u;
	assert(5. == *u);

	auto c = fra.cash();
	assert(0. == *c);
	++c;
	assert(-1. == *c);
	++c;
	assert(1 + 0.2 * 3 == *c);

	assert(*fra == std::pair(0., 0.));
	++fra;
	assert(std::pair(2., -1.) == *fra);
	++fra;
	assert(std::pair(5., 1 + 0.2 * 3) == *fra);
	++fra;
	assert(!fra);

	return 0;
}
int test_instrument_fra_double_3 = test_instrument_fra<double, double>();

template<class U, class C>
int test_instrument_swap()
{
	//maturity 6, frequency 2, coupon 0.2
	interest_rate_swap<U, C> swap(6, 2, 0.2);

	auto u = swap.time();
	assert(0. == *u);
	++u;
	for (int i = 1; i < 12; i = i + 1) {
		assert(i / 2. == *u);
		++u;
	}
	assert(6. == *u);

	auto c = swap.cash();

	assert(-1. == *c);
	++c;
	for (int k = 1; k < 12; k = k + 1) {
		assert(0.1 == *c);
		++c;
	}
	assert(1. + 0.2 /2 == *c);

	assert(std::pair(0., -1.) == *swap);
	++swap;
	for (int j = 1; j < 12; j = j + 1) {
		assert(std::pair(j / 2., 0.2 / 2) == *swap);
		++swap;
	}
	assert(std::pair(6., 1 + 0.2 / 2) == *swap);
	++swap;
	assert(!swap);

	return 0;
}
int test_instrument_swap_double_3 = test_instrument_swap<double, double>();