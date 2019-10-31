// fms_bootstrap.t.cpp - Test bootstrap algorithm.
#include <cassert>
#include "../fms_sequence/fms_sequence.h"
#include "fms_bootstrap.h"
#include "fms_instrument.h"
#include "fms_pwflat.h"

using namespace fms::bootstrap;
using namespace fms::pwflat;

using fms::sequence::list;
using fms::sequence::apply;
using fms::sequence::sum;

template<class X = double>
int scratch()
{

    return 0;
}
int scratch_double = scratch<double>();

int test_bootstrap_pv()
{
	auto i = fms::instrument::sequence(list({ 0., 1., 2. }), list({ 0.01, 0.02, 0.03 }));
	auto f = forward(list({ 1.5, 2.5 }), list({ 0.05, 0.06 }));

	double p = pv(f, i);
	p = p;

	return 0;
}
int test_bootstrap_pv_ = test_bootstrap_pv();

int test_bootstrap_extend()
{
	constexpr double eps = std::numeric_limits<double>::epsilon();
	auto t = list<double>{};
	auto f = list<double>{};
	forward F(t,f);
	double _t;
	double _f;
	{
	//	auto cd0 = fms::instrument::sequence(list({ 0., -1. }), list({ 0.25, 1.01 }));
		auto u0 = list<double>({ 0., 0.25 });
		auto c0 = list<double>({ -1, 1.01 });
		auto [u,r] = extend(F, 0., 0., u0, c0);
		assert(u == 0.25);
		auto p = 1.01 * exp(-r * 0.25);
		assert(p == 1);
	}
	{
		auto cd0 = fms::instrument::sequence(list({ 0., 0.25 }), list({ -1., 1.01 }));
		list<double> u0 = cd0.time();
		list<double> c0 = cd0.cash();
		auto [u, r] = extend(F, 0., 0., u0, c0);
		assert(u == 0.25);
		auto p = 1.01 * exp(-r * 0.25);
		assert(p == 1);

		_t = u;
		_f = r;
	}
	t.push_back(_t);
	f.push_back(_f);
#pragma warning(push)
#pragma warning(disable: 4456)
	{
		forward F(t, f);
		auto cd1 = fms::instrument::sequence(list({ 0., 0.5 }), list({ -1., 1.05 }));
		auto [u, r] = extend(F, _t, 0., cd1.time(), cd1.cash());
		assert(u == 0.5);
		auto p = 1.05 * F.discount(0.25) * exp(-r*(0.5 - 0.25));
		assert(fabs(p - 1) <= eps);

		_t = u;
		_f = r;
	}
	t.push_back(_t);
	f.push_back(_f);
	{
		forward F(t, f);
		auto fra0 = fms::instrument::sequence(list({ 0.6, 1.0 }), list({ -1., 1.05 }));
		auto [u, r] = extend(F, _t, 0., fra0.time(), fra0.cash());
		assert(u == 1.0);
		auto p = -1 + 1.05 * exp(-r * (1.0 - 0.6));
		assert(fabs(p) <= eps);

		_t = u;
		_f = r;
	}
	t.push_back(_t);
	f.push_back(_f);
	{
		forward F(t, f);
		auto swap0 = fms::instrument::sequence(list({ 0., 1., 2. }), list({ -1., 0.5, 1.05 }));
		auto [u, r] = extend(F, _t, 0., swap0.time(), swap0.cash());
		assert(u == 2.0);
		auto p = sum(swap0.cash(), apply([&F](auto t) { return F.discount(t); }, swap0.time()));
		assert(fabs(p) <= eps);

		_t = u;
		_f = r;
	}


	/*
	C r = 0.01;
	cd cd1(0.25, r);
	//...
	fra fra1(.25, 1, r);
	//...
	swap swap1(2, 0.5, r);
	forward f;
	f = bootstrap(f, cd1);
	*/
	return 0;
#pragma warning(pop)
}
int test_bootstrap_extend_ = test_bootstrap_extend();

int main()
{
	return 0;
}
