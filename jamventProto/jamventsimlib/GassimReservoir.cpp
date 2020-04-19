

#include <assert.h>
#include <math.h>
#include "GassimReservoir.h"

GassimReservoir::GassimReservoir(const std::string &name, 
		double pressure, 
		double volume) : GassimNode(name, RESERVOIR) {
	setPressure(pressure);
	setVolume(volume);
}
void  GassimReservoir::setPo2(double pO2) {
	assert(pO2 <= 1.0);				// double check...
    assert (pO2 > 0);
	GassimNode::setPressure(pO2);
};

void GassimReservoir::step(double dt) {



	// # avoid dealing with both the pressure AND temperature chaning
	// #    I am assuming an adbadiac conditions, to avoid a having to
	// #      solve 2 ordanary differential equations...

	// # keep this simple for each device connected to us for now
	// #   assume a single source formula instead of parallel
	// #   sources from different pressures...

	// # for each connection figure out how much is entering or leaving in mols
    unsigned numValveOpen=0;
    double pDelta=0;
    double ppNewO2=0;
    for (auto citer : _connections) {
    	NodePtr_t c = citer.second;
        if (! c->open())
        	continue;
        numValveOpen += 1;
        // #
        // #              1                # calculate the new pressure..
        // # P      = (-----------)        #   this is only valid for a single
        // #               dt/RV           #   inlet at a time... no parallel inlets...
        // #             e
        double pDrop = c->getPressureDrop(nodeId());	// pressure drop relative to me...
        double R=c->resistance();
        double V=volume();
	    //tc=1-math.exp(-dt/(R*V));
	    pDelta = pDrop*(1 - exp(-dt / (R*V)));      //# this is not handling multiple circuits open.
        ppNewO2+=pDelta*(c->pO2());
    }

    assert(numValveOpen <= 1);      //# don't support parallel filling of the container yet...
    // # ttry working with partial pressures.
    double ppO2 = pressure() * pO2();
    ppO2 += ppNewO2;
    setPressure(pressure()+pDelta);
    setPo2(ppO2/pressure());
}
