/**
 * @file	GlobalFilter.h
 * @author	Francesco Racciatti <racciatti.francesco@gmail.com>
 * @version	0.0.1
 * @date	2015 apr 14
 *
 * @brief	TODO
 *
 * @details	TODO
 */


#ifndef GLOBALFILTER_H
#define GLOBALFILTER_H


#include <omnetpp.h>
#include <vector>

//#include "UnconditionalAttacks.h"
#include "AttackEntry.h"

using namespace std;


class GlobalFilter : public cSimpleModule{

	private:
		vector<AttackEntry*> unconditionalAttacks;

	private:	
		void initializeAttacks();

	protected:
		virtual void initialize();
		virtual void handleMessage(cMessage* msg);
		virtual void handlePutMessage(const cMessage* msg);
		virtual void finishSpecific();
	
	
	public:
		GlobalFilter();
		virtual ~GlobalFilter();
		
	

};

#endif
