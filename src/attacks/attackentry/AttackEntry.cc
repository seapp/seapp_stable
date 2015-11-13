/**
 * @file	AttackEntry.cc
 * @author	Francesco Racciatti <racciatti.francesco@gmail.com>
 * @version	0.0.1
 * @date	2015 mar 01
 */


#include "AttackEntry.h"


AttackEntry :: AttackEntry(AttackBase* attack, SimTime occurrenceTime){

	this->attack = attack;
	this->occurrenceTime = occurrenceTime;

}


AttackEntry :: ~AttackEntry(){

	// TODO
	// delete attack;

}


SimTime AttackEntry :: getOccurrenceTime() const{

	return occurrenceTime;

}


AttackBase* AttackEntry :: getAttack() const{

	return attack;

}
