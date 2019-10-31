// fms_instrument.t.cpp - Test fms::instrument
#include <cassert>
#include "../fms_sequence/fms_sequence.h"
#include "fms_instrument.h"
#include "fms_instrument_fra.h"
#include "fms_instrument_swap.h"

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
int test_instrument_cd_int_int = test_instrument_cd<int,int>();

template<class U, class C>
int test_instrument_fra() 
{
	forward_rate_agreement<U, C> fra(2,3,4);
		
	auto u = fra.time();
	assert(0 == *u);
	++u;
	assert(2 == *u);
	++u;
	assert((2 + 3) == *u);

	auto c = fra.cash();
	assert(0 == *c);
	++c;
	assert(-1 == *c);
	++c;
	assert((1 + 3 * 4) == *c);

	assert(std::pair(0,0) == *fra);
	++fra;
	assert(std::pair(2,-1) == *fra);
	++fra;
	assert(std::pair(5,1 + 3 * 4) == *fra);
	++fra;
	assert(!fra);

	return 0;
}
int test_instrument_fra_int_int_int = test_instrument_fra<int,int>();

template<class U, class C>
int test_instrument_swap()
{
	/***
	interest_rate_swap<U, C> swap(2, 1, 6);

	auto u = swap.time();
	assert(0 == *u);
	++u;
	assert(1 == *u);
	++u;
	assert(2 == *u);

	auto c = swap.cash();
	assert(-1 == *c);
	++c;
	assert(6 == *c);
	++c;
	assert((1 + 6) == *c);

	assert(std::pair(0, -1) == *swap);
	++swap;
	assert(std::pair(1, 6) == *swap);
	++swap;
	assert(std::pair(2, 1 + 6) == *swap);
	++swap;
	assert(!swap); ***/

	
	interest_rate_swap<U, C> swap(2,5,4); //1,2,4

	auto u = swap.time();

	double res;
	int i = 0;
	assert(0 == *u);
	//while i != frequency * maturity
	while (i != (2 * 5 - 1)) {
		++u;
		++i;
		res = double(i) / 5;
		assert(res == *u);
	}
	++u;
	++i;
	assert(2 == *u);

	auto c = swap.cash();

	double res1;
	double j = 0;
	assert(-1 == *c);
	while (j != 9) {
		++c;
		++j;
		res1 = double(4) / 5;
		assert(res1 == *c);
	}
	++c;
	++j;
	assert((1+double(4)/5) == *c);

	std::pair<double, double> res2;
	double k = 0;
	assert(std::pair(0.0, -1.0) == *swap);
	while (k != 9) {
		++swap;
		++k;
		res2 = std::pair(k / 5,4.0/5.0);
		assert(res2 == *swap);
	}
	++swap;
	++k;
	assert(std::pair(2.0, 1.0+(double(4)/5)) == *swap);
	assert(!swap);
	
	return 0;
}
int test_instrument_swap_int_int_int = test_instrument_swap<double,double>();