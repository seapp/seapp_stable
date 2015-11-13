/**
 * @file	ConditionalAttack.h
 * @author	Francesco Racciatti <racciatti.francesco@gmail.com>
 * @version	0.0.3
 * @date	2015 mar 18
 *
 * @brief	Conditional class represents a conditional attack, which is carried out by LocalFilter sub-modules.
 *
 * @details	TODO
 */
 

#ifndef CONDITIONALATTACK_H
#define CONDITIONALATTACK_H


#include "AttackBase.h"


using namespace std;


class ConditionalAttack : public AttackBase {

	private:
		/**
		 * @brief 	packetFilter is made by a set of triplets <field:comparisonOperator:value> colon separated
		 *			and logical operators colon separated placed at the bottom.
		 * @detail	The general packetFilter pattern is:
		 * 			field0:comparisonOperator0:value0:field1:comparisonOperator1:value1:...:fieldN:comparisonOperatorN:valueN:
		 *				logicalOperator0:logicalOperator1:...:logicalOperatorN-1
		 */	
		// TODO remove because obsolete
		vector<string> packetFilter;
		
		/** 
		 *	@brief minimumInvolvedLayer is the minimum ISO/OSI layer involved in the conditional attack 
		 */
		int minimumInvolvedLayer;
		
		/**
		 * @brief	triplets <field:comparison_operator:values>
		 */
		vector< vector<string> > packetFilterTriplets;
		vector<string> packetFilterLogicalOperators;

	public:

		/** 
		 * @brief	Constructor
		 */
		ConditionalAttack();
		
		/** 
		 * @brief	Destructor
		 */
		virtual ~ConditionalAttack();
		
		/** 
		 * @brief 	Add an action to the conditional attack.
		 * @detail	The action is added to the AttackBase object's action attribute.
		 */
		virtual void addAction(ActionBase* action);

		/** 
		 * @brief 	Set the packetFilter attribute
		 * @detail	It is invoked by a Parser object that passes to it a string that is the packet filter. 
		 *			It splits the string according to the separator chars ':' and sets the packetFilter attribute.
		 *	@param	monolithicPacketFilter is the monolithic packet filter string (i.e. the packet filter unsplitted)
		 */
		void setPacketFilter(string monolithicPacketFilter);

		/**
		 * @brief	Returns the packet filter
		 */
		//string getPacketFilter() const;

		/**	
		 * @brief	Check if the packet matches the packet filter. 
		 * @detail	If the packet matches the packet filter the method returns true, otherwise returns false
		 * @param	packet is the packet to compare with the packetFilter
		 */
		bool isMatchingPacketFilter(cPacket* packet) const;

		/**
		 * @brief	TODO
		 */
		void execute(cMessage** packet, vector<cMessage*> &generatedPackets, vector<double> &delays, double &delay);
	
};

#endif
