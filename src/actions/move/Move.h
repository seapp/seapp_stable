/**
 * @file	Destroy.h
 * @author	Francesco Racciatti <racciatti.francesco@gmail.com>
 * @version	0.0.3
 * @date	2015 feb 28
 *
 * @brief	Move class makes possible the misplace of a node.
 *
 * @details	TODO
 */



#ifndef MOVE_H
#define MOVE_H

#include "ActionBase.h"
#include "Coord.h"


class Move : public ActionBase{

	private:
		Coord targetPosition; 
		cModule* targetNode;
		
	public:
	
		/**
		 * @brief Constructor.
		 * 
		 * @param targetNode pointer to the target node module (which may contain the mobility sub-module)
		 * @param targetPosition target coordinates
		 */
		Move(cModule* targetNode, Coord targetPosition);
		
		/**
		 * @brief Destructor.
		 */
		virtual ~Move();

		/**
		 * @brief Forces the new position of the node.
		 */
		void execute() const;
		
};

#endif
