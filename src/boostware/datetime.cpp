/*
 * datetime.cpp
 *
 *  Created on: 2014Äê3ÔÂ28ÈÕ
 *      Author: john
 */

#include "datetime.h"
#include <boost/timer.hpp>
#include <boost/progress.hpp>
//#include <boost/thread.hpp>
//#include <boost/date_time/gregorian/gregorian.hpp>
//#include <windows.h>


date_time::date_time() {
	// TODO Auto-generated constructor stub

}

date_time::~date_time() {
	// TODO Auto-generated destructor stub
}

void date_time::test_timer() {
	boost::timer t;

	std::cout << "maxtimespan = " << t.elapsed_max()/3600 << "h" << std::endl;
	std::cout << "mintimespin = " << t.elapsed_min() << "s" << std::endl;

	std::cout << "time elapsed = " << t.elapsed() << "s" << std::endl;
}

void date_time::test_progress_timer() {
	boost::progress_timer t;

	std::cout << "now time elapsed: " << t.elapsed() << "s" << std::endl;
}


void date_time::test_progress_display() {
//	boost::progress_display pd(100);
//	for(int i=0; i<100; i++){
//		//::sleep(500);
//		++pd;
//	}

}

void date_time::test_gregorian() {
//	using namespace boost::gregorian;
//	date d1(2014,3,28);
//	date d2 = from_string("2014-03-28");

}
