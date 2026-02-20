// xll_bootstrap.cpp - bootstrap functions
// TODO: Implment \FI.CURVE.BOOTSTRAP(instruments, prices) 
/*
handle<curve::pwflat> WINAPI xll_fi_bootstrap(_FP12* pi, _FP12* pp) { ...
	ensure(size(*pi) == size(*pp));
	int n = size(*pi);
	std::vector<instrument::base<>*> is(n);
	for (int i = 0; i < n; ++i) {
		is[i] = ??? // instrument::base<>*.
	}
	curve::bootstrap(n, is.data(), pp->array);
}
*/
