//
//  main.cpp
//  xcode-test01
//
//  Created by ralph bellofatto on 4/12/20.
//  Copyright © 2020 ralph bellofatto. All rights reserved.
//

#include <sys/time.h>
#include <time.h>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <strstream>
#include <istream>
#include <cmath>
#include <ostream>
#include <sstream>


//#include "StrTokenize.h"
//#include "fmtstr.h"
#include "JamventSimModel.h"

#ifndef TIME_UTC
#define TIME_UTC 0
#endif

using namespace std;


double getCurrTime() {
	struct timespec ts;
	//timespec_get(&ts, TIME_UTC);
    clock_gettime(CLOCK_REALTIME, &ts); // Works on Linux
	return(ts.tv_sec + ((double)ts.tv_nsec*1e-9));
}
/**
 * @brief wait for a specfied number of seconds
 *        using nanosleep
 * @details time to wait for.
 * 
 * @param tw time in seconds.
 */
void waitTime(double tw) {
	struct timespec timeReq;
	struct timespec rem;
	timeReq.tv_sec = (unsigned)tw;	// truncate the time  to get seconds.
	timeReq.tv_nsec = (unsigned)(tw*1e9);  // 10000 nano secionds (10 milliseconds)
	nanosleep(&timeReq, &rem);
}

int  main(int argc, const char * argv []) {
	bool passed = true;
	cout << "Testing testing JamventSimModel ..." << endl;
	double timeLimit  = 5;

	double timeStart = getCurrTime();
	double timePrev = getCurrTime();  // time in 
	double timeNow = getCurrTime();

	double timeEnd = timeStart+timeLimit;

	// note this is a test so it only runs for a short time and then stops...
	//  actual simulation on hardware would be a loop forever...

	// model test for real..
	JamventSimModel model;
	
	// note this test just makes sure the model itself does not crash.
	// but nothing yet is going on...
	//  should run for 20 seconds then exit
	while (timeNow < timeEnd) {
		// AJ.  here is where you would inject changes in input into the model...
		//      and also read out pressure...
		//      you don't need to sleep, instead, you can just spin, 
		//      but you will need a source of elapsed time...
		timeNow=getCurrTime();
		model.step(timeNow-timePrev);
		timePrev=timeNow;
		waitTime(0.01);		// wait 10 milliseconds...
	}

	// kind of nothing to fail here	
	cout << "Test : " << (passed ? "PASSED" : "FAILED") << endl;

	return (passed ? 0 : 1);
}

