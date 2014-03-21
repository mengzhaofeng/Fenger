//============================================================================
// Name        : Fenger.cpp
// Author      : feng
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <boost/optional.hpp>



int main(void) {
	puts("Hello World!!!");
	boost::optional<double> m_opt(5);
	printf("value = %f\n", m_opt.get());

	return EXIT_SUCCESS;
}
