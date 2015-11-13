/**
 * @file	Move.cc
 * @author	Francesco Racciatti <racciatti.francesco@gmail.com>
 * @version	0.0.4
 * @date	2015 may 13
 */

#include "Move.h"
#include "MobilityBase.h"

Move::Move (cModule* targetNode, Coord targetPosition) : ActionBase(action_t::MOVE) {

	EV_INFO << "Move::Move invoked" << endl;

	this -> targetPosition = targetPosition;
	this -> targetNode = targetNode;
		
	//TODO send info to Logger	
}


Move::~Move() {
	
	EV_INFO << "Move::~Move invoked" << endl;

	//TODO send info to Logger

}


void Move::execute() const {
	
	int nodeID = targetNode -> getId();
	cModule* mobilityGenericSubmodule = targetNode -> getSubmodule("mobility");

	if (mobilityGenericSubmodule == nullptr) {
	
		// the node hasn't the mobility submodule
		string msg("Move::execute didn't find the mobility submodule of node " + nodeID);
		EV_INFO << msg << endl;
		
		if(ev.isGUI()) {
			targetNode -> getDisplayString().setTagArg("p", 0, (long)targetPosition.x);
			targetNode -> getDisplayString().setTagArg("p", 1, (long)targetPosition.y);

			msg.clear();
			msg.append("Move::execute has updated only the visual representation of node " + nodeID);
			EV_INFO << msg << endl;
		}
		
		//TODO send info to Logger
		
	}
	
	else {	
	
		MobilityBase* mobilitySubmodule = check_and_cast <MobilityBase*> (mobilityGenericSubmodule);
		// move the node to target position, translate its constraint area and update the visual representation
		mobilitySubmodule -> transferToTargetPosition( targetPosition );
		
		string msg("Move::execute moved the node " + nodeID);
		msg.append(" to " + targetPosition.info());
		EV_INFO << msg << endl;
		
		//TODO send info to Logger
	}
}



