// xll_bootstrap.cpp - Excel add-in for bootstrapping piecewise constant forward curves.
#include "xll_bootstrap.h"

using namespace xll;

AddIn xai_bootstrap(
	Document(L"xll_bootstrap")
	.Category(L"xll_bootstrap")
	.Documentation(
		L"Excel add-in for bootstrapping piecewise constant forward curves."
	)
);
