/**
 * @file	ActionBase.h
 * @author	Francesco Racciatti <racciatti.francesco@gmail.com>
 * @version	0.99
 * @date	2015 jun 1
 *
 * @brief	ActionBase class provides the representation of a generic action that can be performed during an attack.
 *
 * @details	TODO
 */
 

#ifndef ACTIONBASE_H
#define ACTIONBASE_H

#include <omnetpp.h>

#include "INETDefs.h"

#include <string>
#include <cstdint>

#define NONE_LAYER 1000

using namespace std;


// TODO check if it is possible to put NONE into ActionName (and modify Action.cc)
//#define NONE 100

/** @brief Type of the action */
enum class action_t : uint8_t{
	DESTROY = 0,
	MOVE,
	DROP,
	CLONE,
	CHANGE,
	SEND,
	PUT,
	RETRIEVE,
	EXPRESSION,
	CREATE,	
	FAKEREAD
};


// TODO check if Action is an abstract class
class ActionBase {

	private:
		action_t actionType;
		string packetName;
		
	protected:
		int involvedLayer;
	
	protected:
		/**
		 * @brief	Constructor
		 * @param	action_t type of the action
		 */
		ActionBase(const action_t actionType);
		
	public:
		/** @brief Destructor */
		~ActionBase();
		
		/** @brief Get the type of the action */
		action_t getActionType() const;
	
		virtual int getInvolvedLayer() const;
		
		virtual void setPacketName(const string packetName);
		virtual string getPacketName() const;
};

/**
 * @brief utilities functions
 */
string to_string(const action_t type);
action_t to_action_t(const string type);

#endif
