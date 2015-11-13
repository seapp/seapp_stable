/**
 * @file	Destroy.cc
 * @author	Francesco Racciatti <racciatti.francesco@gmail.com>
 * @version	0.0.4
 * @date	2015 may 13
 */


#include "Destroy.h"
#include "LocalFilter.h"


Destroy::Destroy (cModule* targetNode) : ActionBase(action_t::DESTROY) {
	
	EV_INFO << "Destroy::Destroy invoked" << endl;
	this->targetNode = targetNode;
		
	//TODO send info to Logger
	
}


Destroy::~Destroy() {

	EV_INFO << "Destroy::~Destroy invoked" << endl;
	
	//TODO send info to Logger
	
}


void Destroy::execute () const {

	int nodeID = targetNode->getId();

	LocalFilter* localFilter = check_and_cast <LocalFilter*> ( targetNode -> getSubmodule("localFilter") );
	
	if( localFilter->isDestroyed == false ){
		
		localFilter->isDestroyed = true;
		
		string msg("Destroy::execute has destroyed the node " + nodeID);
		EV_INFO << msg << endl;
		
		// TODO send info to logger
		
		// TODO cancel further events
	
	}
	else{
	
		string msg("Destroy::execute can't destroy the node " + nodeID);
		msg.append(", it's already destroyed");
		EV_INFO << msg << endl;

		// TODO send info to logger		
	}

		
}
