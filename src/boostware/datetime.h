/*
 * datetime.h
 *
 *  Created on: 2014Äê3ÔÂ28ÈÕ
 *      Author: john
 */

#ifndef DATETIME_H_
#define DATETIME_H_
#include <boost/serialization/singleton.hpp>



using boost::serialization::singleton;

class date_time : public singleton<date_time>{
public:
	date_time();
	virtual ~date_time();


	void test_timer();
	void test_progress_timer();
	void test_progress_display();
	void test_gregorian();

};

#endif /* DATETIME_H_ */
