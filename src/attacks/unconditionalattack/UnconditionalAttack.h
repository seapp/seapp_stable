/**
 * @file	UnconditionalAttack.h
 * @author	Francesco Racciatti <racciatti.francesco@gmail.com>
 * @version	0.0.1
 * @date	2015 apr 15
 *
 * @brief	TODO
 *
 * @details	TODO
 */
 

#ifndef UNCONDITIONALATTACK_H
#define UNCONDITIONALATTACK_H


#include "AttackBase.h"


using namespace std;


class UnconditionalAttack : public AttackBase {

	private:
		double frequency;

	public:
		/** 
		 * @brief	Constructor
		 */
		UnconditionalAttack();
		
		/** 
		 * @brief	Destructor
		 */
		virtual ~UnconditionalAttack();
		
		/** 
		 * @brief 	sets frequency attribute
		 */
		void setFrequency(double frequency);

		/** 
		 * @brief 	returns the frequency attribute
		 */
		double getFrequency() const;

		/** 
		 * @brief 	Add an action to the unconditional attack
		 * @detail	The action is added in the base class's attribute action
		 */
		virtual void addAction(ActionBase* action);

		/** 
		 * @brief 	executes the unconditional attacks
		 */
		void execute(vector<cMessage*> &putMessages);

};

#endif
