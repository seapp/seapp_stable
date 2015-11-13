/**
 * @file	seapputils.h
 * @author	Francesco Racciatti <racciatti.francesco@gmail.com>
 * @version	0.0.1
 * @date	2015 mar 01
 *
 * @brief	This file provides utility functions used by INET modules related to attacks evaluation.
 */
 
#ifndef SEAPPUTILS_H
#define SEAPPUTILS_H

#include <iostream>

#include <vector>
#include <string>
#include <omnetpp.h>

using namespace std;


void tokenize(vector<string>& tokens, const string str, const char delim);

cPacket* getDeepestEncapsulatedPacket(cPacket* packet);

int getPacketLayer(cPacket* packet);

int layertoi(const string layer);


void setParameterRecursively (cMessage* msg, const string parameterName, const bool parameterValue);


/*
 * @brief	Makes an hard copy of the packet packetToCopy. 
 *
 * @detail	Makes an hard copy of the packetToCopy by creating a perfect copy of the (outer) packet and of all its encapsulated packets.
 *
 * @param 	packetToCopy it's the packet to be copied
 * @return	the pointer to the (new) copied packet, or nullptr if problems occur
 */
cPacket* hardCopy(cPacket* packetToCopy);





/**
* Compare two elements by means of a specified operator.
 * Comapared elements must support such operators.
 *
 *  @param field1	is the first parameter
 *  @param field2	is the second parameter
 *  @param oper		is the comparison operator (supported : =, !=,
 */
template<class T>
bool evaluate( T f1, T f2, const string comp_operator) {

	if(comp_operator.compare("==") && comp_operator.compare("!=") && comp_operator.compare(">=") && comp_operator.compare("<=") && comp_operator.compare(">") && comp_operator.compare("<")) {

		EV<<"Operator not supported."<<endl;
		return false;

	}


	if(comp_operator == "==") 	
		return f1 == f2;

	if(comp_operator == "!=")
		return f1 != f2;

	if(comp_operator == ">")
		return f1 > f2;
			
	if(comp_operator == "<") 
		return f1 < f2 ;
		
	if(comp_operator == ">=" || comp_operator == "=>")
		return f1 >= f2;

	if(comp_operator == "<=" || comp_operator == "=<")
		return f1 <= f2;

}



#endif
