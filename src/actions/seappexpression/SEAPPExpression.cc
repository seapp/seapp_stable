/**
 * @file	Expression.cc
 * @author	Francesco Racciatti <racciatti.francesco@gmail.com>
 */


#include "SEAPPExpression.h"

bool SEAPPExpression::isAssignmentOperator(const string op)
{
	if ( (op == "=") || (op == "+=") || (op == "-=") || (op == "*=") || (op == "/=") || (op == "%=") ) {
		return true;
	}
	
	return false;
}


SEAPPExpression::SEAPPExpression(const vector<string> expressionItems) : ActionBase(action_t::EXPRESSION)
{
	this->expressionItems = expressionItems;
	involvedLayer = NONE_LAYER;	

	leftOperand = new Variable();
	rightOperand = new Variable();
}


SEAPPExpression::~SEAPPExpression()
{  
	delete leftOperand;
	delete rightOperand;
}


void SEAPPExpression::execute(map<string, Variable*> *variableTable, stack<Variable*> *variableStack)
{
  	map<string, Variable*>::iterator resIt = variableTable->find("RESULT"); //<A.S>
	   	  				    
    for (size_t i = 0; i < expressionItems.size(); i++) {
        map<string, Variable*>::iterator iter = variableTable->find(expressionItems[i]);
        // push the found operand into the stack
		if (iter != variableTable->end()) {
			variableStack->push((iter->second));
	    }

	    // found an operator
		else {
			string op = expressionItems[i];
			// is an assignment operator
			if (isAssignmentOperator(op)) {
			    i++;
				string where = expressionItems[i];

				// find the other operand
				map<string, Variable*>::iterator jter = variableTable->find(where);
              
				if ( op == "=")
					*(jter->second) = *variableStack->top();	   
				else if ( op == "+=")
					*(jter->second) += *variableStack->top();	
				else if ( op == "-=")
					*(jter->second) -= *variableStack->top();	
				else if ( op == "*=")
					*(jter->second) *= *variableStack->top();	
				else if ( op == "/=")  
					*(jter->second) /= *variableStack->top();	
				else if ( op == "%=")
					*(jter->second) %= *variableStack->top();	

               	variableStack->top() = nullptr;
               	variableStack->pop();           
			}
			// is not an assignment operator
			else {	
				*rightOperand = *(variableStack->top());
				variableStack->top() = nullptr;
                variableStack->pop();
				    
				*leftOperand = *(variableStack->top());
				variableStack->top() = nullptr;
				variableStack->pop();

				if ( op == "+") {
					Variable *temp = (*leftOperand + *rightOperand);
					*(resIt->second) = *temp;
					temp = nullptr;
					delete temp;
                }
                else if ( op == "-") {
                	Variable *temp = (*leftOperand - *rightOperand);
					*(resIt->second) = *temp;
					temp = nullptr;
					delete temp;
                }	
				else if ( op == "*") {
 					Variable *temp = (*leftOperand * *rightOperand);
					*(resIt->second) = *temp;
					temp = nullptr;
					delete temp;                    
				}
				else if ( op == "/") {
					Variable *temp = (*leftOperand / *rightOperand);
					*(resIt->second) = *temp;
					temp = nullptr;
					delete temp;                    
				}
				else if ( op == "%") {
 					Variable *temp = (*leftOperand % *rightOperand);
					*(resIt->second) = *temp;
					temp = nullptr;
					delete temp;
				}

				variableStack->push((resIt->second));
                
            }
                
       }
	}    
}



