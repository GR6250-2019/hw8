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

template<class U, class C>
int test_instrument_swap()
{
	U U_EPSILON = 1e-6;
	C C_EPSILON = 1e-6;
	interest_rate_swap<U, C> swap(2, 2, 6);

	auto u = swap.time();
	assert(std::abs(0.0 - *u) < U_EPSILON);
	++u;
	assert(std::abs(0.5 - *u) < U_EPSILON);
	++u;
	assert(std::abs(1.0 - *u) < U_EPSILON);
	++u;
	assert(std::abs(1.5 - *u) < U_EPSILON);
	++u;
	assert(std::abs(2.0 - *u) < U_EPSILON);

	auto c = swap.cash();
	assert(std::abs(-1.0 - *c) < C_EPSILON);
	++c;
	assert(std::abs(6.0 / 2.0 - *c) < C_EPSILON);
	++c;
	assert(std::abs(6.0 / 2.0 - *c) < C_EPSILON);
	++c;
	assert(std::abs(6.0 / 2.0 - *c) < C_EPSILON);
	++c;
	assert(std::abs(1.0 + 6.0 / 2.0 - *c) < C_EPSILON);
	++c;

	assert(std::abs(0.0 - (*swap).first) < U_EPSILON);
	assert(std::abs(-1.0 - (*swap).second < C_EPSILON));
	++swap;
	assert(std::abs(0.5 - (*swap).first) < U_EPSILON);
	assert(std::abs(6.0 / 2.0 - (*swap).second < C_EPSILON));
	++swap;
	assert(std::abs(1.0 - (*swap).first) < U_EPSILON);
	assert(std::abs(6.0 / 2.0 - (*swap).second < C_EPSILON));
	++swap;
	assert(std::abs(1.5 - (*swap).first) < U_EPSILON);
	assert(std::abs(6.0 / 2.0 - (*swap).second < C_EPSILON));
	++swap;
	assert(std::abs(2.0 - (*swap).first) < U_EPSILON);
	assert(std::abs(1.0 + 6.0 / 2.0 - (*swap).second < C_EPSILON));
	++swap;
	assert(!swap);
	return 0;
}
int test_instrument_swap_double_double = test_instrument_swap<double, double>();
