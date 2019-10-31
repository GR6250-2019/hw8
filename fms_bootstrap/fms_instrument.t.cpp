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
	forward_rate_agreement<U, C> fra(1, 2, 3);

	auto u = fra.time();
	assert(1 == *u);
	++u;
	assert(3 == *u);

	auto c = fra.cash();
	assert(-1 == *c);
	++c;
	assert(1 + 2 * 3 == *c);

	assert(std::pair(1, -1) == *fra);
	++fra;
	assert(std::pair(3, 1 + 2 * 3) == *fra);
	++fra;
	assert(!fra);

	return 0;
}
int test_instrument_fra_int_int = test_instrument_fra<int, int>();


template<class U, class C, class T>
int test_instrument_swap()
{
	swap<U, C, T> sp(1.0, 2.0, 2.0);

	auto u = sp.time();
	assert(0.0 == *u);
	++u;
	assert(0.5 == *u);
	++u;
	assert(1.0 == *u);

	auto c = sp.cash();
	assert(-1.0 == *c);
	++c;
	assert(1.0== *c);
	++c;
	assert(2.0 == *c);

	assert(std::pair(0.0, -1.0) == *sp);
	++sp;
	assert(std::pair(0.5, 1.0) == *sp);
	++sp;
	assert(!sp);

	return 0;
}
int test_instrument_swap_int_int = test_instrument_swap<double,double>();