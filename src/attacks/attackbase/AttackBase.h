/**
 * @file	AttackBase.h
 * @author	Francesco Racciatti <racciatti.francesco@gmail.com>
 * @version	0.0.4
 * @date	2015 apr 27
 *
 * @brief	AttackBase class provides the representation of a generic attack. An attack is a sequence of actions.
 *
 * @details	TODO
 */
 

#ifndef ATTACKBASE_H
#define ATTACKBASE_H


#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <stack>

#include "ActionBase.h"
#include "Variable.h"


using namespace std;


/**
 * @brief Type of action
 */
enum class attack_t : uint8_t{
	PHYSICAL = 0,
	CONDITIONAL,
	UNCONDITIONAL
};


class AttackBase {

	private:
		/** @brief Type of attack */
		attack_t attackType;
		
	protected:
		/** @brief Sequence of actions to execute during the attack */
		vector<ActionBase*> actions;	
		
		/** @brief TODO */
		map<string, Variable*> variableTable;

		/** @brief TODO */
		stack<Variable> variableStack;

	public:

		/** @brief Constructor */
		AttackBase(const attack_t attackType);
		
		/** @brief Destructor */
		virtual ~AttackBase();		
	
		virtual void addAction(ActionBase* action);
	
		/** @brief Add variable table */
		void initializeVariableTable(const map<string,Variable*> variableTable);

};


/**
 * @brief TODO
 */
string to_string(const attack_t type);
attack_t to_attack_type(const string type); 

#endif
