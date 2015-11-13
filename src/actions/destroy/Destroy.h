/**
 * @file	Destroy.h
 * @author	Francesco Racciatti <racciatti.francesco@gmail.com>
 * @version	0.0.4
 * @date	2015 may 13
 *
 * @brief	Destroy class extends ActionBase. Destroy class makes possible the destruction of a node.
 *
 * @details	Destroy class is instantiated by the Parser object in the LocalFilter::attacksInitialization method.
 *			The Parser object calls the Destroy constuctor and passes to it the reference to the isDestroyed bool member
 *			of the LocalFilter object.
 *			The Destroy constructor initialize the isDestroyed bool pointer member with this reference.
 *			The destruction of the node is carried out by the execute method, which sets the bool variable pointed 
 *			by the pointer isDestroyed.
 */


#ifndef DESTROY_H
#define DESTROY_H


#include "ActionBase.h"


class Destroy : public ActionBase {

	private:
		cModule* targetNode;

	public:
	
		/**
		 * @brief Constructor.
		 * @param [in] isDestroyed pointer to the bool variable isDestroyed of a LocalFilter object.
		 *
		 * @detail TODO Destroy constructor is called by the Parser object in the LocalFilter::attacksInitialization method.
		 * The Parser object passes to it the reference to the isDestroyed bool member of the LocalFilter object.
		 * The Destroy constructor initialize the isDestroyed bool pointer member with this reference.
		 */
		Destroy(cModule* targetNode);
		
		/**
		 * @brief Destructor.
		 */
		virtual ~Destroy();

		/**
		 * @brief Destroys the node.
		 * 
		 * @detail Destroys the node by setting the bool variable pointed by isDestroyed.
		 */
		void execute() const;
};

#endif
