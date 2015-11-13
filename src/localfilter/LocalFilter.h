/**
 * @file	LocalFilter.h
 * @author	Francesco Racciatti <racciatti.francesco@gmail.com>
 * @version	0.0.9
 * @date	2015 may 03
 *
 * @brief	TODO
 *
 * @details	TODO
 */


#ifndef LOCALFILTER_H
#define LOCALFILTER_H


#include <omnetpp.h>
#include <vector>
#include <map>
#include <cstdint>

#include "ConditionalAttack.h"


using namespace std;


class LocalFilter : public cSimpleModule{

	friend class Destroy;
	friend class Create;

	private:
		enum class command_t : uint8_t{
			DISCARD = 0,
			SELFMESSAGE,
			GLOBALFILTER,
			CONDITIONAL,
			NOATTACK	
		};
		
		bool isDestroyed;
		
		map<cGate*,cGate*> coupledGates;
		
		vector<ConditionalAttack*> enabledConditionalAttacks;

		int injectedBytes;
		
		// TODO REMOVE because useless
		map<string, int> targetPacketsClasses;

	private:	
		void forgeInterfaceTable();
		void initializeGates();
		void initializeAttacks();
		void forgeSendingData(cMessage* msg);
		command_t planOperation(cMessage* msg) const;

	protected:
		virtual void initialize(int stage);
		virtual void handleMessage(cMessage* msg);
		virtual int numInitStages() const { return 5;};
	
	public:
		LocalFilter();
		virtual ~LocalFilter();
		
};

#endif
