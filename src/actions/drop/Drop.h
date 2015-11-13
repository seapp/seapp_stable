/**
 * @file	Drop.h
 * @author	Francesco Racciatti <racciatti.francesco@gmail.com>
 * @version	0.0.2
 * @date	2015 apr 09
 *
 * @brief	TODO
 *
 * @details	TODO
 */


#ifndef DROP_H
#define DROP_H


#include "ActionBase.h"


class Drop : public ActionBase {

	private:
		

	public:
	
		/**
		 * @brief Constructor
		 */
		Drop();
		
		/**
		 * @brief Destructor.
		 */
		virtual ~Drop();

		/**
		 * @brief TODO
		 */
		void execute(cMessage** packet) const;
};

#endif
