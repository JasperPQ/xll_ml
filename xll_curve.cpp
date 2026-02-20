// xll_curve.cpp - curve functions
#include "xll_fi.h"
#include "fms_curve_pwflat.h"

using namespace xll;
using namespace fms;

static AddIn xai_curve_pwflat_(
	Function(XLL_HANDLEX, L"xll_curve_pwflat_", L"\\" CATEGORY L".CURVE.PWFLAT")
	.Arguments({
		Arg(XLL_FP, L"t", L"is the vector of forward rate times."),
		Arg(XLL_FP, L"f", L"is the vector of forward rates."),
		})
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(L"Return a handle to a curve with forward rates f at times t.")
);
HANDLEX WINAPI xll_curve_pwflat_(_FP12* pt, _FP12* pf, double _f)
{
#pragma XLLEXPORT
	HANDLEX h = INVALID_HANDLEX;

	try {
		handle<curve::pwflat<>> h_(new curve::pwflat(span(*pt), span(*pf)));
		ensure(h_);
		h = h_.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (...) {
		XLL_ERROR(__FUNCTION__ ": unknown exception");
	}

	return h;
}

static AddIn xai_curve_pwflat(
	Function(XLL_FP, L"xll_curve_pwflat", CATEGORY L".CURVE.PWFLAT")
	.Arguments({
		Arg(XLL_HANDLEX, L"h", L"is a handle to a pwflat curve."),
		})
	.Category(CATEGORY)
	.FunctionHelp(L"Return a two row array of times and rates.")
);
_FP12* WINAPI xll_curve_pwflat(HANDLEX h)
{
#pragma XLLEXPORT
	static FPX tf;

	try {
		tf.resize(0, 0);
		handle<curve::pwflat<>> h_(h);
		ensure(h_);
		int n = (int)h_->size();
		tf.resize(2, n);
		std::copy_n(h_->time(), n, tf.array());
		std::copy_n(h_->rate(), n, tf.array() + n);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (...) {
		XLL_ERROR(__FUNCTION__ ": unknown exception");
	}

	return tf.get();
}

// TODO: Implement CURVE.PWFLAT.FORWARD, CURVE.PWFLAT.DISCOUNT, CURVE.PWFLAT.SPOT