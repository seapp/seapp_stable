/**
 * @file	ConditionalAttack.cc
 * @author	Francesco Racciatti <racciatti.francesco@gmail.com>
 * @version	0.0.4
 * @date	2015 apr 12
 */


#include "ConditionalAttack.h"
#include "seapputils.h"

#include "Drop.h"
#include "Clone.h"
#include "Change.h"
#include "Send.h"
#include "Put.h"
#include "Retrieve.h"
#include "SEAPPExpression.h"
#include "Create.h"


ConditionalAttack :: ConditionalAttack() : AttackBase(attack_t::CONDITIONAL){

	minimumInvolvedLayer = NONE_LAYER;

	EV << "ConditionalAttack::ConditionalAttack invoked" << endl;

}


ConditionalAttack :: ~ConditionalAttack(){

	EV << "ConditionalAttack::~ConditionalAttack invoked" << endl;

}


void ConditionalAttack :: addAction(ActionBase* action){

	actions.push_back(action);
	
	int actionLayer = action->getInvolvedLayer();
		
	if( minimumInvolvedLayer > actionLayer ){
		minimumInvolvedLayer = actionLayer;
	}

}


void ConditionalAttack::setPacketFilter(string monolithicPacketFilter) {
	
	vector<string> splittedPacketFilter;	
	tokenize(splittedPacketFilter, monolithicPacketFilter, ':');
	
	// logical operators are stored in inverse order when parsed
	for(size_t i = splittedPacketFilter.size()-1; i >= 0; i--){
		if( (splittedPacketFilter[i] == "OR") || (splittedPacketFilter[i] == "AND") ){
			packetFilterLogicalOperators.push_back(splittedPacketFilter[i]);
		}
		else{
			break;
		}
	}
	
	// store triplets that are make by the entries <field:comparison_operator:value>
	for(size_t i = 0; i < (splittedPacketFilter.size()-packetFilterLogicalOperators.size()); i+=3){
		int j = (int) i/3; 
		packetFilterTriplets.push_back( vector<string> () );
		packetFilterTriplets[j].push_back(splittedPacketFilter[i]);
		packetFilterTriplets[j].push_back(splittedPacketFilter[i+1]);
		packetFilterTriplets[j].push_back(splittedPacketFilter[i+2]);
	}

	//EV << "----------------------------------- triplets size --------------" << packetFilterTriplets.size();
	//EV << "----------------------------------- logicaloperators size --------------" << packetFilterLogicalOperators.size();
}


/*
vector<string> ConditionalAttack :: getPacketFilter() const{

	return packetFilter;
	
}
*/

bool ConditionalAttack :: isMatchingPacketFilter(cPacket* packet) const{

	// check if the packet was already filtered before
	if (packet->par("isFiltered").boolValue()) {
		EV << "ConditionalAttack::isMatchingPacketFilter found isFilter false, the packet was already filtered before" << endl;
		return false;	
	}

	// postpone the attack after encapsulation
	if (getPacketLayer(packet) > minimumInvolvedLayer) {
		EV << "ConditionalAttack::isMatchingPacketFilter postpone attack after decapsulation" << endl;
		return false;
	}
		
	cPacket* encapsulatedPacket;
	cClassDescriptor* descriptor;
	
	vector<string> splittedFields;
	// TODO to change in protocolName
	string layerName;
	
	string fieldName;
	string comparisonOperator;
	vector<string> splittedValues;
	
	int layer;
	
	// retrieve the right encapsulated packet for each condition (relative to the specified layer)
	// and fill the conditions vector
	
	vector<bool> isMatching;
	for (size_t i = 0; i<packetFilterTriplets.size(); i++) {
	
		// parse the 'field' entry that is composed by the couple <layer_name.field_name>
		splittedFields.clear();
		tokenize(splittedFields, packetFilterTriplets[i][0], '.');
		layerName = splittedFields[0];
		//layer = layertoi(layerName);
		fieldName = splittedFields[1];

		comparisonOperator = packetFilterTriplets[i][1];

		tokenize(splittedValues, packetFilterTriplets[i][2], '|');
		
		// retrieve the encapsulated packet which belongs to the involved Layer
		encapsulatedPacket = packet;
		while(getPacketLayer(encapsulatedPacket) > layertoi(layerName)){
			encapsulatedPacket = encapsulatedPacket->getEncapsulatedPacket();
			// the packet cannot be filtered at current time
			if(encapsulatedPacket==nullptr){
				return false;
			}
		}
		
		// retrieve a descriptor to the packet to be filtered
		descriptor = cClassDescriptor::getDescriptorFor(encapsulatedPacket);
		int fieldIndex = descriptor->findField(encapsulatedPacket, fieldName.c_str());
		
		if(fieldIndex == -1){
			isMatching.push_back(false);
		}
		else{
			bool comparisonResult = false;
			for(size_t j = 0; j < splittedValues.size(); j++){
				string fieldValue = descriptor->getFieldAsString(encapsulatedPacket, fieldIndex, 0);
				comparisonResult = evaluate( atoi(fieldValue.c_str()), atoi(splittedValues[j].c_str()), comparisonOperator );
				if(comparisonResult == true){
					break;
				}
			}
			isMatching.push_back(comparisonResult);
		}
		
	}
	
	if(packetFilterLogicalOperators.size() == 0){
		return isMatching[0];
	}
	else{
		for(size_t j = 0; j < packetFilterLogicalOperators.size(); j++){
		
			if(j != packetFilterLogicalOperators.size()-1){
				if( packetFilterLogicalOperators[j] == "OR"){
					if(isMatching[j]==true)
						return true;
				}
				else{
					isMatching[j+1] = isMatching[j+1] && isMatching[j];
				}		
			}
			else{
				if( packetFilterLogicalOperators[j] == "OR"){
					if( (isMatching[j] == true) || (isMatching[j+1] == true) ){
						return true;
					}
				}
				else{
					isMatching[j+1] = isMatching[j+1] && isMatching[j];
					return isMatching[j+1];
				}
			}
		}
		// TODO remove
		return false;
	}	
}


// TODO change packet in msg!!!
void ConditionalAttack::execute(cMessage** packet, vector<cMessage*> &generatedPackets, vector<double> &delays, double &delay){

	EV << "ConditionalAttack::execute invoked" << endl;

	map<string,int> packetTable;
	packetTable["original"] = -1;
	
	cMessage* generatedPacket = nullptr;
	
	cMessage** targetPacket = nullptr;
	
	string packetName;
	int packetPosition;
	int fieldIndex;
	
	// set isFiltered parameter (it exists and its value is false) to avoid multiple execution of the attack by the same node on different layer 
	setParameterRecursively(*packet, "isFiltered", true);
	
	// execute all actions composing the attack
	for (size_t i = 0; i < actions.size(); i++) {
		
		generatedPacket = nullptr;
	
		switch (actions[i]->getActionType()) {
	
			case action_t::DROP: {
				Drop* drop = (Drop*) actions[i];
				packetName = drop->getPacketName();
				packetPosition = packetTable[packetName];
				
				// process the original intercepted packet
				if (packetPosition == -1) {
					targetPacket = packet;
				}
				// process another existing packet
				else {
					targetPacket = &generatedPackets[packetPosition];
				}
				drop->execute(targetPacket);
				break;
			}
			
			case action_t::CLONE: {
				Clone* clone = (Clone*) actions[i];
			
				// retrieve the names of the clone packet and the original packet
				string clonePacketName = clone->getClonePacketName();
				packetName = clone->getPacketName();
				packetPosition = packetTable[packetName];

				// process the original intercepted packet
				if (packetPosition == -1) {
					targetPacket = packet;
				}
				// process another existing packet
				else {
					targetPacket = &generatedPackets[packetPosition];
				}
				
				clone->execute(&generatedPacket, *targetPacket);
				
				// add the new packet to the generatedPackets
				generatedPackets.push_back(((cMessage*)(generatedPacket)));

				// add a zero delivery delay to the new packet
				delays.push_back(0.0);

				// update the packetTable map
				packetTable[clonePacketName] = generatedPackets.size()-1;
				
				break;

			}
			
			
			case action_t::CHANGE: {
				Change* change = (Change*) actions[i];			
				
				packetName = change->getPacketName();
				packetPosition = packetTable[packetName];
				
				bool isRandomValue;
				string valueName;
				string value;

				valueName = change->getValue();
				isRandomValue = (valueName == "RANDOM");		
				
				// process the original intercepted packet
				if (packetPosition == -1) {
					targetPacket = packet;
				}
				// process another existing packet
				else {
					targetPacket = &generatedPackets[packetPosition];
				}
				
				if (isRandomValue) {
					double randomValue;
					double maxValue;
					double minValue;
					
					minValue = double( *(variableTable["MIN"]) );
					maxValue = double( *(variableTable["MAX"]) );
					
					randomValue = minValue + ( dblrand() * (maxValue - minValue) );
					
					value = to_string(randomValue); 
				}
				else {
					value = variableTable[valueName]->getValue();
				}
				
				change->execute(targetPacket, value);
				break;
			}
			
			
			case action_t::SEND: {
				Send* send = (Send*) actions[i];

				packetName = send->getPacketName();
				packetPosition = packetTable[packetName];

				// in case of original packet retrieve only the delay
				if (packetPosition == -1){
					delay = send->getSendDelay();
				}
				// process another existing packet
				else{
					targetPacket = &generatedPackets[packetPosition];
					send->execute(*targetPacket);
					delays[packetPosition] = send->getSendDelay();
				}
				break;			
			}
	
			case action_t::PUT: {
				Put* put = (Put*) actions[i];
			
				packetName = put->getPacketName();
				packetPosition = packetTable[packetName];

				// process the original intercepted packet
				if (packetPosition == -1){
					targetPacket = packet;
				}
				// process another existing packet
				else {
					targetPacket = &generatedPackets[packetPosition];
				}
				
				generatedPacket = put->execute(*targetPacket);
				generatedPackets.push_back(generatedPacket);
				delays.push_back(0.0);
				
				break;
			}
	
			case action_t::RETRIEVE: {
				Variable* variable;
				string variableName;
				Retrieve* retrieve = (Retrieve*) actions[i];

				packetName = retrieve->getPacketName();
				packetPosition = packetTable[packetName];
				
				// process the original intercepted packet
				if (packetPosition == -1) {
					targetPacket = packet;
				}
				// process another existing packet
				else{
					targetPacket = &generatedPackets[packetPosition];
				}
				
				variable = retrieve->execute(*targetPacket);
				
				// delete the old value and update the variable table
				variableName.assign(retrieve->getVariableName());
				delete variableTable[variableName];
				variableTable[variableName] = variable;
				
				break;
			}
			
			case action_t::EXPRESSION: {
				SEAPPExpression* expression = (SEAPPExpression*) actions[i];
				expression->execute(&variableTable, &variableStack);
				break;
			}
			
			case action_t::CREATE: {
			
				cPacket* createdPacket = nullptr;
				Create* create = (Create*) actions[i];
				
				string createdPacketName = create->getPacketName();
					
				create->execute(&createdPacket);
	
				generatedPackets.push_back(((cMessage*)(createdPacket)));
				delays.push_back(0.0);
				packetTable[createdPacketName] = generatedPackets.size()-1;
				
				break;
			}
	
		}
		
	}

}





















