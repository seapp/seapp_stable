#!/usr/bin/env python

"""

This python script takes one description file as input, and produces an XML attack specification file as output.

Attacks are described in the input file by means of the attack specification language.

Authors:
Alessandro Pischedda	alessandro.pischedda@gmail.com
Marco Tiloca			marco.tiloca84@gmail.com
Francesco Racciatti		racciatti.francesco@gmail.com	
"""

import sys
import os
import re
import readline
from subprocess import call
import ply.yacc as yacc
from ASLexer import *
from primitives import *
from attack import *


# Initialize the command line parser
try:
    from argparse import ArgumentParser, RawDescriptionHelpFormatter
except ImportError:
    print "Library argparse missing"
    sys.exit(-1)


# DATA STRUCTURES

level = 0  # This is to assure correct XML indentation
global_symbol_table = {} # All declared global IDs and their type (i.e. LIST)
symbol_table = {} # All declared local IDs and their type (i.e. VAR, PACKET) (global symbols cannot be overriden)

actions = [] # List of actions composing an attack
variables = {} # Dictionary of variables used within an attack. Entry format is <name, XML string>, and the latter includes value and type
lists = {} # Dictionary of node lists. Entry format is <list_name, list of nodes>, with the node list as a string (nodes are separated by '|')
listDestroy = {} # Dictionary of 'destroy' actions. Entry format is <time, list_nodes>, with the node list as a string (nodes are separated by ':')
listMove = {} # Dictionary of 'move' actions <time, <position, list_nodes>>, with the node list as a string (nodes are separated by ':')

# <F.R.>
listFakereadArgc4 = {} # dictionary of 'fakeread' (4 args) actions
listFakereadArgc5 = {} # dictionary of 'fakeread' (5 args) actions
listFakereadArgc6 = {} # dictionary of 'fakeread' (6 args) actions
listFakereadArgc7 = {} # dictionary of 'fakeread' (7 args) actions

packetFilter = "" # Packet filter boolean expression
packetFilterOperator = "AND" # Boolean operator used in the packet filter expression ('AND' by default)

physical_att = [] # List of physical attacks
conditional_att = [] # List of conditional attacks
unconditional_att = [] # List of unconditional attacks

reserved_name = ["RANDOM"]

layer_names = ["APP", "NET", "TRA", "MAC", "UDP", "controlInfo", "sending"]

# UTILITIES

def print_error(error_msg, error_lineno):
		error_msg = error_msg+" - Line "+str(error_lineno)
		print error_msg
		raise SyntaxError

# check if the input file exist and it is a valid file
def check_input(filename):

	if not os.path.exists(filename):
        	print str(filename)+" not exists."
        	sys.exit(-1)

	if not os.path.isfile(filename):
		print str(filename)+" is a directory."
		sys.exit(-1)


# check if the output file :
#  already exists
#  is a valid file and not a directory
def check_output(filename):

	while(1):
		if os.path.exists(filename):

			if not os.path.isfile(filename):
				filename = raw_input(str(filename)+" is, probably, a directory. Type a new name : ")
				continue

			while(1):
				answer = raw_input(str(filename)+" already exists, do you want to overwrite it ?[y/n] : ")
				if str(answer) == "y" or str(answer) == "n":
					break
				
				print "Option "+str(answer)+" not valid"
			
			if str(answer) == "y":
				break
			else :
				filename = raw_input("Type a new file name : ")
					
		# ok the file doesn't exists	
		else:
			break

	return filename
		


# Parse command line arguments and options
def options():

    epilog = "All arguments and options are mandatory"

    # The RawDescriptionHelpFormatter is required to show the epilog
    parser = ArgumentParser(epilog=epilog, formatter_class=RawDescriptionHelpFormatter,version="%prog 0.9")
    
    parser.add_argument("-o", "--output",
                      default="",
                      metavar="\"OUTPUT\"",
                      help="Name of the xml output file")
    parser.add_argument("input",
                      metavar="\"INPUT\"",
                      default="",
                      help="Name of the attack specification file to be processed")

    args = parser.parse_args()

    # Convert the list of options to a dictionary
    opts = args.__dict__

    if opts['input'] is "":
        parser.error("Input file is missing.")

	# set as default the input name with .xml extension
    if opts['output'] is "":
        # it doesn't replace .asl with .xml in one way 
        # because we can have as input even a not .asl file
        opts['output'] = opts['input'].replace(".asl", "")
        opts['output']+=".xml"

	print "Output "+opts['output']

    return opts


# Clear data structures
def clear_data_structure():

	packetFilter = ""
	packetFilterOperator = "AND" # Back to its default value
	
	del actions[:]
	variables.clear()
	symbol_table.clear()

# check if the user has specified an existing layer name
# field is "layer.field" so we need to extract the layer name
def check_layer_name(field):
	
	hygienize = field.replace("\"", "")
	layer_name =	(hygienize.split("."))[0]

	if layer_name in layer_names:
		return True
	return False


# Parsing rules

precedence = (
	('left','PLUS','MINUS'),
	('left','TIMES','DIVIDE'),
	('left', 'EXP'),
	('right','UMINUS', 'EQUALS'),
)


def p_program(p):
	'program : global_entries'

	
def p_global_entries(p):
	"""global_entries : attack
			  | list_statement
			  | global_entries global_entries"""


# List definition
def p_statement_list(p):
	'list_statement : LIST ID EQUALS LCBRACKET listMembers RCBRACKET'
	
	# Check that the list identifier is not in used
	if (str(p[2]) in global_symbol_table.keys() or str(p[2]) in symbol_table.keys()):
		print_error("\tError : ID '"+str(p[2])+"' is already declared ", str(p.lineno(2)))
	
	else :
		# Add the list identifier to the global symbol table
		global_symbol_table[str(p[2])] = 'LIST'
		lists[str(p[2])] = p[5]


#
# ATTACK SECTION
#

# An attack is either: i) a single move/destroy/fakeread invocation; ii) a conditional attack block; or iii) an unconditional attack block
def p_attack(p):
	"""attack : physical_statement
		  | conditional_attack
		  | unconditional_attack"""


def p_conditional_attack(p):
	'conditional_attack : FROM number NODES IN ID DO LCBRACKET filter_codeblock RCBRACKET'
	
	# The specified list has not been declared
	if str(p[5]) not in lists.keys():
	      print_error("\tError : list '"+str(p[5])+"' is not declared", str(p.lineno(5)))
	
	node_list = lists[p[5]].replace("|", ":")
	
	# Build the attack and add it to the right attack list
        att = ConditionalAttack(p[2], node_list, variables, actions, packetFilter)
	conditional_att.append(att)
	
	# Clear data structures for the next attack
	clear_data_structure()	
	level = 0


def p_unconditional_attack(p):
	'unconditional_attack : FROM number EVERY number DO LCBRACKET codeblock RCBRACKET'

        # Build the attack and add it to the right attack list
        att = UnconditionalAttack(p[2], p[4], variables, actions)
	unconditional_att.append(att)
	
	# Clear data structures for the next attack
	clear_data_structure()
	level = 0

#
# END ATTACK SECTION
#


def p_time(p):
	"""number : INTEGER
                  | REAL"""

	p[0] = str(p[1])

	
def p_filter_codeblock(p):
	'filter_codeblock : filter_code codeblock'

	
def p_codeblock(p):
	'codeblock : statements'

# Possible statements are: i) logical primitives; ii) variable declaration/definition; iii) packet declaration
def p_statements(p):
	"""statements : statement
		      | logical_statement
		      | statements statements"""

		      
# Variable definition
def p_statement_varinit(p):
	'statement : VAR ID EQUALS init'

	# check if the name is a reserved one (like RANDOM)
	# Check if this identifier has been already declared for this attack
	if str(p[2]) in reserved_name:
		print_error("\tError : '"+str(p[2])+"' is a reserved name and can't be overwrite", str(p.lineno(2)))
		
	elif str(p[2]) in symbol_table.keys():
		print_error("\tError : '"+str(p[2])+"' is already declared", str(p.lineno(2)))
	else :
		# Add the identifier to the symbol and variable table
		symbol_table[str(p[2])] = 'VAR' 
		variables[str(p[2])] = str(p[4])


# Variable declaration (with no definition)
def p_statement_vardef(p):
	'statement : VAR ID'
	
	# check if the name is a reserved one (like RANDOM)
	# Check if this identifier has been already declared for this attack
	if str(p[2]) in reserved_name:
		print_error("\tError : '"+str(p[2])+"' is a reserved name and can't be overwrite", str(p.lineno(2)) )

	elif str(p[2]) in symbol_table.keys():
		print_error("\tError : '"+str(p[2])+"' is already declared", str(p.lineno(2)) )
	else :
		# Add the identifier to the symbol and variable table (with type = 'NONE')
		symbol_table[str(p[2])] = 'VAR' 
		variables[str(p[2])] = "<value></value><type>NONE</type>"


def p_init_string(p):
	'init : STRING'

	# Remove quotes
	value = str(p[1]).replace("\"", "")
	p[0] = "<value>"+value+"</value><type>STRING</type>"


def p_init_real(p):
        """init : REAL
		| INTEGER 
	"""
	
	p[0] = "<value>"+str(p[1])+"</value><type>NUMBER</type>"

	
# Packet declaration
def p_statement_packetdef(p):
	'statement : PACKET ID'

	packet_name = str(p[2])	
	lineno = str( p.lineno(1) )

	if packet_name == 'original':
		print_error("\tError : '"+packet_name+"' is a reserved name and can't be overwrite", lineno )

	# Check if this identifier has been already declared for this attack
	if packet_name in symbol_table.keys():
		print_error("\tError : '"+packet_name+"' is already declared", lineno)
		
	else :
		# Add the identifier to the symbol table
		if packet_name != 'original':
			symbol_table[ packet_name ] = 'PACKET' 

# Check if the provided argument is a packet and it has been previously declared
def packet_check(argument, lineno):
	if argument not in symbol_table.keys() or symbol_table[argument] != 'PACKET':
		print_error("\tError : undefined packet '"+str(argument)+"'", str(lineno))


# Primitive invocations

# destroy (int nodeID, double occurrence_time)
def p_statement_destroy(p):
	'physical_statement : DESTROY LPAREN INTEGER COMMA arg_number RPAREN'

	# 'destroy' invocations are grouped according to their occurrence time
	if not p[5] in listDestroy.keys():
	      listDestroy[p[5]] = "" + str(p[3])
	else:
	      listDestroy[p[5]] = listDestroy[p[5]] + ":" + str(p[3])

# move (int nodeID, double occurrence_time, double coord_x, double coord_y, double coord_z)
def p_statement_move(p):
	'physical_statement : MOVE LPAREN INTEGER COMMA arg_number COMMA arg_number COMMA arg_number COMMA arg_number RPAREN'
	
	# 'move' invocations are grouped according to their occurrence time. They are also further sub-grouped according to specified coordinates
	moveArgs = "" + str(p[7]) + ":" + str(p[9]) + ":" +str(p[11])
	
	if not p[5] in listMove.keys():
	      listMove[p[5]] = {}
	      
	if not moveArgs in listMove[p[5]].keys():
	      listMove[p[5]][moveArgs] = "" + str(p[3])
	
	else:
	      listMove[p[5]][moveArgs] = listMove[p[5]][moveArgs] + ":" + str(p[3])

# <F.R.>
"""	fakeread is an overloaded function """
def p_statement_fakeread(p):
	"""physical_statement : FAKEREAD LPAREN INTEGER COMMA arg_number COMMA INTEGER COMMA CON COMMA arg_signed_number COMMA arg_signed_number RPAREN
	| FAKEREAD LPAREN INTEGER COMMA arg_number COMMA INTEGER COMMA FIX COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number RPAREN
	| FAKEREAD LPAREN INTEGER COMMA arg_number COMMA INTEGER COMMA SEN COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number RPAREN
	| FAKEREAD LPAREN INTEGER COMMA arg_number COMMA INTEGER COMMA SAT COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number RPAREN
	| FAKEREAD LPAREN INTEGER COMMA arg_number COMMA INTEGER COMMA MIN COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number RPAREN
	| FAKEREAD LPAREN INTEGER COMMA arg_number COMMA INTEGER COMMA MAX COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number RPAREN
	| FAKEREAD LPAREN INTEGER COMMA arg_number COMMA INTEGER COMMA AVG COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number RPAREN
	| FAKEREAD LPAREN INTEGER COMMA arg_number COMMA INTEGER COMMA INF COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number RPAREN
	| FAKEREAD LPAREN INTEGER COMMA arg_number COMMA INTEGER COMMA SUP COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number RPAREN
	| FAKEREAD LPAREN INTEGER COMMA arg_number COMMA INTEGER COMMA MED COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number RPAREN
	| FAKEREAD LPAREN INTEGER COMMA arg_number COMMA INTEGER COMMA SGN COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number RPAREN
	| FAKEREAD LPAREN INTEGER COMMA arg_number COMMA INTEGER COMMA RND COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number RPAREN
	| FAKEREAD LPAREN INTEGER COMMA arg_number COMMA INTEGER COMMA LIN COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number RPAREN
	| FAKEREAD LPAREN INTEGER COMMA arg_number COMMA INTEGER COMMA SYM COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number RPAREN
	| FAKEREAD LPAREN INTEGER COMMA arg_number COMMA INTEGER COMMA SHP COMMA arg_signed_number COMMA arg_signed_number COMMA arg_number COMMA arg_number RPAREN
	| FAKEREAD LPAREN INTEGER COMMA arg_number COMMA INTEGER COMMA SIN COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number RPAREN
	| FAKEREAD LPAREN INTEGER COMMA arg_number COMMA INTEGER COMMA SQR COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number RPAREN
	|  FAKEREAD LPAREN INTEGER COMMA arg_number COMMA INTEGER COMMA SAW COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number RPAREN
	| FAKEREAD LPAREN INTEGER COMMA arg_number COMMA INTEGER COMMA TRI COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number COMMA arg_signed_number RPAREN"""

	if p[9] in Fakeread.argc4noises:
		fakereadArgs = "" + str(p[7]) + ":" + str(p[9]) + ":" + str(p[11]) + ":" + str(p[13])
		if not p[5] in listFakereadArgc4.keys():
			listFakereadArgc4[p[5]] = {}
		if not fakereadArgs in listFakereadArgc4[p[5]].keys():
			listFakereadArgc4[p[5]][fakereadArgs] = "" + str(p[3])
		else:
			listFakereadArgc4[p[5]][fakereadArgs] = listFakereadArgc4[p[5]][fakereadArgs] + ":" + str(p[3])
	
	if p[9] in Fakeread.argc5noises:
		fakereadArgs = "" + str(p[7]) + ":" + str(p[9]) + ":" + str(p[11]) + ":" + str(p[13]) + ":" + str(p[15])
		if not p[5] in listFakereadArgc5.keys():
			listFakereadArgc5[p[5]] = {}
		if not fakereadArgs in listFakereadArgc5[p[5]].keys():
			listFakereadArgc5[p[5]][fakereadArgs] = "" + str(p[3])
		else:
			listFakereadArgc5[p[5]][fakereadArgs] = listFakereadArgc5[p[5]][fakereadArgs] + ":" + str(p[3])

	if p[9] in Fakeread.argc6noises:
		fakereadArgs = "" + str(p[7]) + ":" + str(p[9]) + ":" +str(p[11]) + ":" + str(p[13]) + ":" + str(p[15]) + ":" + str(p[17])
		if not p[5] in listFakereadArgc6.keys():
			listFakereadArgc6[p[5]] = {}
		if not fakereadArgs in listFakereadArgc6[p[5]].keys():
			listFakereadArgc6[p[5]][fakereadArgs] = "" + str(p[3])
		else:
			listFakereadArgc6[p[5]][fakereadArgs] = listFakereadArgc6[p[5]][fakereadArgs] + ":" + str(p[3])

	if p[9] in Fakeread.argc7noises:
		fakereadArgs = "" + str(p[7]) + ":" + str(p[9]) + ":" +str(p[11]) + ":" + str(p[13]) + ":" + str(p[15]) + ":" + str(p[17]) + ":" + str(p[19])
		if not p[5] in listFakereadArgc7.keys():
			listFakereadArgc7[p[5]] = {}
		if not fakereadArgs in listFakereadArgc7[p[5]].keys():
			listFakereadArgc7[p[5]][fakereadArgs] = "" + str(p[3])
		else:
			listFakereadArgc7[p[5]][fakereadArgs] = listFakereadArgc7[p[5]][fakereadArgs] + ":" + str(p[3])

# drop (packet p)
def p_statement_drop(p):
	'logical_statement : DROP LPAREN arg_id RPAREN'	

	if p[3] != 'original':
	      packet_check(p[3], p.lineno(1))
	  
	action = Drop(str(p[3]))
	actions.append(action)

# send (packet p, double delay)
def p_statement_send(p):
	'logical_statement : SEND LPAREN arg_id COMMA arg_number RPAREN'
	
	if p[3] != 'original':
	      packet_check(p[3], p.lineno(1))
	
	args = str(p[3]) + ":" + str(p[5])
	action = Send(args)
	actions.append(action)
	
# clone (srcPacket p1, dstPacket p2)
def p_statement_clone(p):
	'logical_statement : CLONE LPAREN arg_id COMMA arg_id RPAREN'
	
	if p[3] != 'original':
	      packet_check(p[3], p.lineno(1))
	packet_check(p[5], p.lineno(1))
	
	args = str(p[3]) + ":" + str(p[5])
	action = Clone(args)
	actions.append(action)

# create (packet p, string layer1.type, type_t content1, string layer2.type, type_t content2, ...)
def p_statement_create(p):
	'logical_statement : CREATE LPAREN arg_id COMMA args_create RPAREN'
	
	packet_check(p[3], p.lineno(1))
	
	# the check for the layer name is done in arg_create part 

	args = str(p[3]) + ":" + str(p[5])
	  
	action = Create(args)
	actions.append(action)

# change (packet p, string layer.field, type_t content)
def p_statement_change(p):
	'logical_statement : CHANGE LPAREN arg_id COMMA STRING COMMA arg_multiType RPAREN'
    

	# Check the third argument
	if p[3] != 'original':
		packet_check(p[3], p.lineno(1))


	# The third argument (content) can be a multiType (NUMBER, STRING, ID) 
	# STRING and NUMBER cases : if isn't in the variable table we must add an entry in it. 
	# ID ca se:  if wasn't declared return an error
	if p[7] not in reserved_name and p[7] not in symbol_table.keys():

		re_pattern = r"^[0-9]"
		pattern = re.compile(re_pattern)

		# STRING
		if p[7][0] == "\"" and p[7][-1] == "\"":
			symbol_table[p[7]] = 'VAR'
			variables[p[7]] = "<value>"+p[7][1:-1]+"</value><type>STRING</type>"
		# NUMBER
		elif re.match(pattern, p[7]):
			symbol_table[p[7]] = 'VAR'
			variables[p[7]] = "<value>"+p[7]+"</value><type>NUMBER</type>"
		# ID
		else :
			print_error("\tError : '" + p[7] + "' undefined variable identifier", str(p.lineno(1)) )

	# if isn't inizialized return an error
	# Get the first character of the variable value. In case it is '<', the variable has not been initialized
	if p[7] not in reserved_name:

		value = variables[p[7]][7]
     
		# Such a variable has been previously defined but not initialized
		if value == "<":
			print_error("\tError : '" + p[7] + "' variable must be initialized", str(p.lineno(1)) )
      
	if check_layer_name(p[5]) is False:
		print_error("\tError : Layer name unknown, use APP/NET/MAC instead", str(p.lineno(1)))

	args = str(p[3]) + ":" + str(p[5]) + ":" + str(p[7])
	action = Change(args)
	actions.append(action)

# retrieve (packet p, string layer.field, ID content)
def p_statement_retrieve(p):
	'logical_statement : RETRIEVE LPAREN arg_id COMMA STRING COMMA arg_id RPAREN'
      
	if p[3] != 'original':
		packet_check(p[3], p.lineno(1))
		
	# Check the third argument. It must be an already declared variable
	# and you can't use a reserved name like RANDOM
      
 	if p[7] in reserved_name:
		print_error("\tError : '" + p[7] + "' is a reserved name and can't be overwrite", str(p.lineno(1)) )
      
	# This variable has not been previously declared
	if p[7] not in symbol_table.keys():
		print_error("\tError : '" + p[7] + "' undefined variable identifier", str(p.lineno(1)) )
      
	# A packet with the same name has been already declared. This is not permitted
	if p[7] in symbol_table.keys() and symbol_table[p[7]] != 'VAR':
		print_error("\tError : ID overloading is not allowed", str(p.lineno(1)) )
      
	if check_layer_name(p[5]) is False:
		print_error("\tError : Layer name unknown, use APP/NET/MAC instead", str(p.lineno(1)))

	args = str(p[3]) + ":" + str(p[5]) + ":" + str(p[7])
	action = Retrieve(args)
	actions.append(action)

# put (packet p, list dstNodes, direction dir, bool updateStat, double delay)
def p_statement_put(p):
      'logical_statement : PUT LPAREN arg_id COMMA arg_id COMMA arg_direction COMMA arg_boolean COMMA arg_number RPAREN'
      
      if p[3] != 'original':
	    packet_check(p[3], p.lineno(1))
	  
      # Check that the second argument refers to a declared list
      if p[5] not in lists.keys():
	    print_error("\tError : list '" + p[5] + "' is not declared", str(p.lineno(1)) )

      # Replace the second argument with the list content
      p[5] = str(lists[str(p[5])])
      args = str(p[3]) + ":" + str(p[5]) + ":" + str(p[7]) + ":" + str(p[9]) + ":" + str(p[11])

      action = Put(args)
      actions.append(action)

#
# FILTER SECTION (conditional attacks only)
#

# Filter definition
def p_filter(p):
	'filter_code : FILTER LPAREN filter_content RPAREN'
	
	global packetFilter
	global packetFilterOperator
	packetFilter = p[3].replace("\"","") # remove quotes
	#packetFilter = packetFilter + packetFilterOperator


def p_filter_content_mono(p):
	'filter_content : filter_elem'
	p[0] = p[1] # in case of a single condition, the AND operator is appended by default

# <F.R.>
def p_filter_content_generic(p):
	'filter_content : filter_elem logic_operator filter_content'
	
	p[0] = p[1] + ":" + p[3] + ":" + p[2]# at the moment, using only either AND or OR is admitted. The right one is appended at the end

# handle the condiction contained between two paren
def p_filter_content_paren(p):
	'filter_content : LPAREN filter_content RPAREN'
	
	p[0] = p[2]


def p_filter_elem(p):
	'filter_elem : operand comp_operator operand'
	
	p[0] = str(p[1]) + ":" + str(p[2]) + ":" + str(p[3])


def p_right_operand(p):
	"""operand : ID
			 | STRING
			 | INTEGER
			 | REAL
			 | SELF
	"""
	p[0] = str(p[1])


def p_comp_operator(p):
	"""comp_operator : EQUAL
			 | DIFFERENT
			 | GRTHAN
			 | LESSTHAN
			 | GREQTHAN
			 | LEQTHAN
	"""
	
	p[0] = str(p[1])


def p_logic_operator(p):
	"""logic_operator : AND
			  | OR
	"""
	
	global packetFilterOperator
	packetFilterOperator = str(p[1]).upper()
	p[0] = str(p[1]).upper()
	

#
# END FILTER SECTION
#


#
# ARGUMENT SECTION
#

# Members of a list (Integer values only)
def p_listMembers(p):
	'listMembers : listMembers COMMA listMembers'
	p[0] = str(p[1]) + "|" + str(p[3])

def p_listMember(p):
	'listMembers : INTEGER'
	p[0] = str(p[1])
	
# Argument is a number (REAL or INTEGER)
def p_arg_number(p):
	"""arg_number : REAL
		      | INTEGER
	"""
	
	p[0] =  str(p[1])

# <F.R.>
# Argument is a signed number (REAL or SIGNED_REAL or INTEGER or SIGNED_INTEGER)
def p_arg_signed_number(p):
	"""arg_signed_number : REAL
		| SIGNED_REAL
		| INTEGER
		| SIGNED_INTEGER
	"""

	p[0] = str(p[1])

# Argument can be either a STRING, REAL, INTEGER value or an ID
def p_arg_multiType(p):
	"""arg_multiType : REAL
			 | INTEGER
			 | STRING
			 | ID
	"""
	
	p[0] =  str(p[1])

# Argument is a boolean constant
def p_arg_boolean(p):
	"""arg_boolean : TRUE
		       | FALSE
	"""

	p[0] =  str(p[1]).lower()

# Argument is either TX or RX
def p_arg_direction(p):
	"""arg_direction : TX
					 | RX
	"""

	p[0] =  str(p[1])

# Argument is a generic identifier
def p_arg_id(p):
	"""arg_id : ID
			  | ORIGINAL
	"""
        
	# Check if the ID is present in the global symbol dictionary (i.e. it refers to a list)
	if str(p[1]) in global_symbol_table.keys():
		if global_symbol_table[str(p[1])] == 'LIST':
		    #p[0] = str(lists[str(p[1])])
		    p[0] = str(p[1])
	
	# Check if the ID is present in the local symbol dictionary
	elif str(p[1]) in symbol_table.keys():
		p[0] =  str(p[1])
	
	# This may be a string/number constant or an undefined variable identifier
	else:
		p[0] =  str(p[1])

# List of arguments for the create() primitive (variable number)
def p_args_create(p):
	'args_create : args_create COMMA args_create'
	
	p[0] = str(p[1]) + ":" + str(p[3])

# Pair of arguments for the create() primitive (layer.field , value)
def p_argsPair_create(p):
	'args_create : STRING COMMA arg_multiType'
	
	if check_layer_name(p[1]) is False:
		print_error("\tError : Layer name unknown, use APP/NET/MAC instead", str(p.lineno(1)))

	p[0] = str(p[1]) + ":" + str(p[3])

#
# END ARGUMENT SECTION
#


#
# EXPRESSION SECTION
#

# This expression involves an assignment
def p_statement_assign(p):
        """statement : ID EQUALS expression 
		     | ID PLUSEQ expression
		     | ID MINUSEQ expression
		     | ID TIMESEQ expression
		     | ID DIVIDEQ expression
		     | ID MODULEQ expression
	"""

	# check if the ID is already declared and if it is a variable
	if str(p[1]) not in symbol_table.keys():
		print_error("Error : '"+str(p[1])+"' is not declared", str(p.lineno(1)) )
	else:
		if symbol_table[str(p[1])] != 'VAR':
			print_error("Error : '"+str(p[1])+"' is not a variable", str(p.lineno(1)) )	


	expression = str(p[3])+"\n\t\t<item>"+str(p[2])+"</item>\n\t\t<item>"+p[1]+"</item>"
	action = Expression(expression)
	actions.append(action)


# Simple arithmetic operation
def p_expression_binop(p):
        """
        expression : expression PLUS expression
                  | expression MINUS expression
                  | expression TIMES expression
                  | expression DIVIDE expression
		  | expression MODULE expression
                  | expression EXP expression
        """

        p[0] = p[1]+p[3]+"\n\t\t<item>"+str(p[2])+"</item>"


def p_expression_uminus(p):
        'expression : MINUS expression %prec UMINUS'
        p[0] = -p[2]


def p_expression_group(p):
        'expression : LPAREN expression RPAREN'
        p[0] = p[2]


# String parsing
def p_expression_string(p):
        'expression : STRING '

	# if it is not in the variable table, then add it
	if str(p[1]) not in variables.keys():
		value = p[1].replace("\"","")
		variables[str(p[1])] = "<value>"+str(value)+"</value><type>STRING</type>"
	
	p[0] =  "\n\t\t<item>"+str(p[1])+"</item>"


# Number parsing
def p_expression_number(p):
        """expression : INTEGER 
			| REAL
	"""

	# if it is not in the variable table, then add it
	if str(p[1]) not in variables.keys():
		variables[str(p[1])] = "<value>"+str(p[1])+"</value><type>NUMBER</type>"

	p[0] =  "\n\t\t<item>"+str(p[1])+"</item>"	


# Identifier parsing
def p_expression_id(p):
	'expression : ID '

	# check if the ID is already declared and if it is a variable
	if str(p[1]) not in symbol_table.keys():
		print_error("Error : '"+str(p[1])+"' is not declared", str(p.lineno(1)) )
	else:
		if symbol_table[str(p[1])] != 'VAR':
			print_error("Error : '"+str(p[1])+"' is not a variable", str(p.lineno(1)) )
		else:
			p[0] =  "\n\t\t<item>"+str(p[1])+"</item>"
	

#
# END EXPRESSION SECTION
#


#
# ERROR SECTION
#

def p_physical_attack_error(p):
	'attack : FROM error DO LCBRACKET codeblock RCBRACKET'
	print "Error : wrong attack declaration - Line " + str(p.lineno(2))


def p_statement_vardef_error(p):
	"""statement : VAR ID EQUALS error
		     | VAR error
	"""
	print "\nError : something missing in the variable declaration - Line " + str(p.lineno(2))


# List of arguments seprated by ','
def p_argslist(p):
	'args : args COMMA args'
	
	p[0] = str(p[1]) + ":" + str(p[3])


# Argument is the keyword "original" (used for intercepted packets)
def p_args_original(p):
	'args : ORIGINAL'
	
	p[0] = "original"


# Argument is either a number, a string, "TX", "RX", "SELF", or a generic identifier
def p_args_simple(p):
        """args : REAL
		| INTEGER
		| STRING
		| TX
		| RX
		| SELF
		| ID
	"""

	p[0] =  str(p[1])


# Argument is a boolean constant
def p_args_simple_boolean(p):
        """args : TRUE
		| FALSE
	"""

	p[0] =  str(p[1]).lower()


def p_physical_funcall_error(p):
	"""physical_statement : DESTROY LPAREN error RPAREN
			      	| MOVE LPAREN error RPAREN
					| FAKEREAD LPAREN error RPAREN
	"""
	
	print "Syntax error in " + p[1] + "() argument declaration - Line " + str(p.lineno(3))


def p_logical_funcall_error(p):
	"""logical_statement : DROP LPAREN error RPAREN
			     | CHANGE LPAREN error RPAREN
			     | RETRIEVE LPAREN error RPAREN
			     | CLONE LPAREN error RPAREN
			     | CREATE LPAREN error RPAREN
			     | SEND LPAREN error RPAREN
			     | PUT LPAREN error RPAREN
	"""

	print "Syntax error in " + p[1] + "() argument declaration - Line " + str(p.lineno(1))


# Invocation of an undefined phisical primitive
def p_undefined_physical_funcall_error(p):
	'physical_statement : error LPAREN args RPAREN'
	
	print "Syntax error: undefined primitive - Line " + str(p.lineno(1))
	
	
# Invocation of an undefined logical primitive
def p_undefined_logical_funcall_error(p):
	'logical_statement : error LPAREN args RPAREN'
	
	print "Syntax error: undefined primitive - Line " + str(p.lineno(1))


# Generic error handler
def p_error(p):
	tok = lexer.token()
	print "Syntax error - Line "+str(tok.lineno)+" "+str(tok)

        
#
# END ERROR SECTION
#


# Write attack statements to the XML output file
def write_file(out_name):

	# Open the output file
	out_file = open(out_name,"w")
	
	# Write the XML preamble
	out_file.write("<?xml version=\"1.0\"?>\n")
	out_file.write("<configuration>\n")

	# Physical attack section
	if (len(listDestroy) or len(listMove) or len(listFakereadArgc4) or len(listFakereadArgc5) or len(listFakereadArgc6) or len(listFakereadArgc7)) :

	      out_file.write("\n<Physical>\n")

	      # Build compact 'destroy' blocks
	      if (len(listDestroy)):
		  action = Destroy()
		  actions.append(action) # Actually it is only one action, with no parameters
	      
		  for key in listDestroy:
			att = PhysicalAttack(key, listDestroy[key], actions)
			physical_att.append(att)
			
		  listDestroy.clear()
		  del actions[:]
		
	      # Build compact 'move' blocks
	      if (len(listMove)):
		  for key1 in listMove: # key1 is the occurrence time
			for key2 in listMove[key1]: #key2 includes the new coordinates as 'x:y:z'
			      action = Move(key2)
			      actions.append(action) # Actually it is only one action with new coordinates as argument
			      
			      att = PhysicalAttack(key1, listMove[key1][key2], actions)
			      physical_att.append(att)
			      del actions[:]
			
		  listMove.clear()

		 # Build compact 'fakeread' blocks
	      if (len(listFakereadArgc4)):
		  for key1 in listFakereadArgc4: # key1 is the occurrence time
			for key2 in listFakereadArgc4[key1]: #key2 includes the parameters 'sensorID:alpha:beta'
			      action = Fakeread(key2)
			      actions.append(action) 
			      
			      att = PhysicalAttack(key1, listFakereadArgc4[key1][key2], actions)
			      physical_att.append(att)
			      del actions[:]
					
		  listFakereadArgc4.clear()

		 # Build compact 'fakeread' blocks
	      if (len(listFakereadArgc5)):
		  for key1 in listFakereadArgc5: # key1 is the occurrence time
			for key2 in listFakereadArgc5[key1]: #key2 includes the parameters 'sensorID:alpha:beta:gamma'
			      action = Fakeread(key2)
			      actions.append(action) 
			      
			      att = PhysicalAttack(key1, listFakereadArgc5[key1][key2], actions)
			      physical_att.append(att)
			      del actions[:]
					
		  listFakereadArgc5.clear()
		  
		  # Build compact 'fakeread' blocks
	      if (len(listFakereadArgc6)):
		  for key1 in listFakereadArgc6: # key1 is the occurrence time
			for key2 in listFakereadArgc6[key1]: #key2 includes the parameters 'sensorID:alpha:gamma:deltaH:deltaL'
			      action = Fakeread(key2)
			      actions.append(action) 
			      
			      att = PhysicalAttack(key1, listFakereadArgc6[key1][key2], actions)
			      physical_att.append(att)
			      del actions[:]
					
		  listFakereadArgc6.clear()

          # Build compact 'fakeread' blocks
	      if (len(listFakereadArgc7)):
		  for key1 in listFakereadArgc7: # key1 is the occurrence time
			for key2 in listFakereadArgc7[key1]: #key2 includes the parameters 'sensorID:alpha:beta:tau:phi:gamma'
			      action = Fakeread(key2)
			      actions.append(action) 
			      
			      att = PhysicalAttack(key1, listFakereadArgc7[key1][key2], actions)
			      physical_att.append(att)
			      del actions[:]
					
		  listFakereadArgc7.clear()

	      # Write an XML block for each physical attack
	      for attack in physical_att:
		      out_file.write(str(attack))

	      out_file.write("\n</Physical>\n\n")

	# Conditional attack section
	if len(conditional_att):
		out_file.write("<Conditional>\n")
		
		# Write an XML block for each conditional attack
		for attack in conditional_att:
			out_file.write(str(attack))
	
		out_file.write("\n</Conditional>\n")

	# Unconditional attack section
	if len(unconditional_att):
		out_file.write("\n<Unconditional>\n")
		
		# Write an XML block for each unconditional attack
		for attack in unconditional_att:
			out_file.write(str(attack))

		out_file.write("\n</Unconditional>\n")	
	
	# Write the XML epilogue
	out_file.write("\n</configuration>\n")
	
	# Clear the global symbol table
	global_symbol_table.clear()
	
	# Close the output file
	out_file.close()


# Initialize yacc
yacc.yacc(debug=0, start='program')


if __name__ == '__main__':

	# Retrieve command line arguments and options
	opts = options()
	
	check_input(opts["input"])
	opts["output"] = check_output(opts["output"])


	# Retrieve the content of the attack specification file
	src_file = open(opts["input"], "r")
	file_content = src_file.read()
	src_file.close()
        
	# Parse the attack specification file
	yacc.parse(file_content)

	# Produce the output XML file
	write_file(opts["output"])
	
	# File cleaning
	call("rm *.pyc", shell=True)
