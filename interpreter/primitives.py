"""

This file defines classes for the primitives provided by the attack specification language.
Every class includes a method that returns an XML block related to a primitive execution.

Authors:
Alessandro Pischedda	alessandro.pischedda@gmail.com
Marco Tiloca		marco.tiloca84@gmail.com

"""

import sys

# Wrong number of arguments
def error_arguments(name, ex_number, g_number):
	sys.exit("Error: "+name+"() takes exactly "+str(ex_number)+" arguments ( "+str(g_number)+ " given )")

# <F.R.>
def wrong_argc(name, g_argc):	
	if name == "fakeread":
		sys.exit("ERROR: basing on the distortion function used, fakeread takes exactly 5 or 7 arguments, " + g_argc + "given")
	#others


""" clone(srcPacketName, dstPacketName) """	
class Clone:

	name = "Clone"
	argv = []
	argc = 2 # Expected number of arguments

	def __init__(self, args):
		self.argv = args.split(':')

	def __str__(self):
		if self.argc != len(self.argv):
			error_arguments(self.name, self.argc, len(self.argv))

		xml = "\t<action>\n\t\t<name>Clone</name>          \n\t\t<parameters>packetName:"+self.argv[0]+":newPacketName:"+self.argv[1]+"</parameters>                        \n\t</action>"

		return xml


""" send(packetName, delay) """		
class Send:

	name = "Send"
	argv = []
	argc = 2

	def __init__(self, args):
		self.argv = args.split(":")

	def __str__(self):
		if self.argc != len(self.argv):
			error_arguments(self.name, self.argc, len(self.argv))
		
		xml = "\t<action>\n\t\t<name>Send</name>\n\t\t<parameters>packetName:"+self.argv[0]+":delay:"+self.argv[1]+"</parameters>\n\t</action>"

		return xml


""" drop(packetName) """
class Drop:

	name = "Drop"
	argv = []
	argc = 1

	def __init__(self, args):
		self.argv = args.split(":")

	def __str__(self):
		if self.argc != len(self.argv):
			error_arguments(self.name, self.argc, len(self.argv))
		
		xml = "\t<action>\n\t\t<name>Drop</name>\n\t\t<parameters>packetName:"+self.argv[0]+"</parameters>\n\t</action>"

		return xml


""" move(x, y, z) --- Node(s) and occurrence time are not stored in this object """
class Move:

	argv = []
	argc = 3	
	name = "Move"

	def __init__(self, args):
		self.argv = args.split(":")

	def __str__(self):
		if self.argc != len(self.argv):
			error_arguments(self.name, self.argc, len(self.argv))
		
		coordinates = self.argv[0]+":"+self.argv[1]+":"+self.argv[2]
		xml = "\t<action>\n\t\t<name>Move</name>\n\t\t<parameters>"+coordinates+"</parameters>\n\t</action>"

		return xml


""" destroy() --- Node(s) and occurrence time are not stored in this object """
class Destroy:

	def __str__(self):
		
		xml = "\t<action>\n\t\t<name>Destroy</name>\n\t</action>"

		return xml

# <F.R.>
""" fakeread() --- Node(s) and occurrence time are not stored in this object """
class Fakeread:
	
	argv = []
	name = "Fakeread"

	argc4 = 4 # sensorID, noise, alpha, beta
	argc5 = 5 # sensorID, noise, alpha, beta, gamma
	argc6 = 6 # sensorID, noise, aplha, deltaH, deltaL, gamma
	argc7 = 7 # sensorID, noise, alpha, beta, tau, phi, gamma
	argc4noises = ['con']
	argc5noises = ['sen', 'sat', 'fix' ,'min', 'max', 'avg', 'inf', 'sup', 'med', 'sgn', 'rnd', 'lin']
	argc6noises = ['shp', 'sym']
	argc7noises = ['sin', 'sqr', 'saw', 'tri']

	def __init__(self, args):
		self.argv = args.split(":")

	def __str__(self):

		# check the number of arguments
		if (len(self.argv) == self.argc4) and (self.argv[1] in self.argc4noises):
			sensorID = self.argv[0]
			noise = self.argv[1]
			alpha = self.argv[2]
			beta = self.argv[3]
			
			params = sensorID + ":" + noise + ":" + alpha + ":" + beta
			xml = "\t<action>\n\t\t<name>Fakeread</name>\n\t\t<parameters>"+params+"</parameters>\n\t</action>"

			return xml
		
		elif (len(self.argv) == self.argc5) and (self.argv[1] in self.argc5noises):
			sensorID = self.argv[0]
			noise = self.argv[1]
			alpha = self.argv[2]
			beta = self.argv[3]
			gamma = self.argv[4]

			params = sensorID + ":" + noise + ":" + alpha + ":" + beta + ":" + gamma
			xml = "\t<action>\n\t\t<name>Fakeread</name>\n\t\t<parameters>"+params+"</parameters>\n\t</action>"

			return xml
			
		elif (len(self.argv) == self.argc6) and (self.argv[1] in self.argc6noises):
			sensorID = self.argv[0]
			noise = self.argv[1]
			alpha = self.argv[2]
			gamma = self.argv[3]
			deltaH = self.argv[4]
			deltaL = self.argv[5]

			params = sensorID + ":" + noise + ":" + alpha + ":" + gamma + ":" + deltaH + ":" + deltaL
			xml = "\t<action>\n\t\t<name>Fakeread</name>\n\t\t<parameters>"+params+"</parameters>\n\t</action>"

			return xml

		elif (len(self.argv) == self.argc7) and (self.argv[1] in self.argc7noises):		
			sensorID = self.argv[0]
			noise = self.argv[1]
			alpha = self.argv[2]
			beta = self.argv[3]
			tau = self.argv[4]
			phi = self.argv[5]
			gamma = self.argv[6]

			params = sensorID + ":" + noise + ":" + alpha + ":" + beta + ":" + tau + ":" + phi + ":" + gamma
			xml = "\t<action>\n\t\t<name>Fakeread</name>\n\t\t<parameters>"+params+"</parameters>\n\t</action>"

			return xml


		else:
			wrong_argc(self.name, len(self.argv))


""" change(packet, field, newContent)

	The field format is layer.field 
	
	The layer can be APP, MAC, and ROUTING or NET
	Possible field names are related to the particular layer
"""
class Change:
	
	argv = []
	argc = 3
	name = "Change"

	def __init__(self, args):
		self.argv = args.split(":")

	def __str__(self):
		if self.argc != len(self.argv):
			error_arguments(self.name, self.argc, len(self.argv))
			
		field = self.argv[1].replace('"', "")
		
		xml = "\t<action>\n\t\t<name>Change</name>\n\t\t<parameters>packetName:"+self.argv[0]+":field_name:"+field+":value:"+self.argv[2]+"</parameters>\n\t</action>"""

		return xml


""" retrieve(packet, field , variable) 

	The field format is layer.field 
	
	The layer can be APP, MAC, and ROUTING or NET
	Possible field names are related to the particular layer
	The third parameter must be a variable

"""
class Retrieve:
	
	argv = []
	argc = 3
	name = "Retrieve"

	def __init__(self, args):
		self.argv = args.split(":")

	def __str__(self):
		if self.argc != len(self.argv):
			error_arguments(self.name, self.argc, len(self.argv))

		field = self.argv[1].replace('"', "")
		
		xml = "\t<action>\n\t\t<name>Retrieve</name>\n\t\t<parameters>packetName:"+self.argv[0]+":field_name:"+field+":varName:"+self.argv[2]+"</parameters>\n\t</action>"

		return xml


""" put(packet, dstNodes, direction, updateStat, delay) 

	# dstNodes is a list of node IDs, separated by the char '|'

"""
class Put:
	
	argv = []
	argc = 5
	name = "Put"

	def __init__(self, args):
		self.argv = args.split(":")

	def __str__(self):
		if self.argc != len(self.argv):
			error_arguments(self.name, self.argc, len(self.argv))
		
		xml = "\t<action>\n\t\t<name>Put</name>\n\t\t<parameters>packetName:"+self.argv[0]+":nodes:"+self.argv[1]+":direction:"+self.argv[2]+":throughWC:"+self.argv[3]+":delay:"+self.argv[4]+"</parameters>\n\t</action>"

		return xml


""" create(packet, layer1.type, value1, layer2.type, value2, ...)"""
class Create:

	argv = []
	argc = 7 # at most
	name = "Create"

	def __init__(self, args):
		self.argv = args.split(":")

	def __str__(self):
		if (len(self.argv) < 3):
			error_arguments(self.name, self.argc, len(self.argv))
		
		xml = "\t<action>\n\t\t<name>Create</name>\n\t\t<parameters>packetName:"+self.argv[0]
		
		i = 1 # Skip the first argument, i.e. the packet name
		while (i < len(self.argv)):
			 field = self.argv[i].replace('"',"") # Remove '"' from string arguments
			 xml = xml + ":" + field
			 i = i + 1
		
		xml = xml + "</parameters>\n\t</action>"

		return xml


""" Handle the expression """
class Expression:

	expr = ""

	def __init__(self, expression):
		self.expr = expression

	def __str__(self):
		xml = "\t<action>\n\t\t<name>Expression</name>"
		xml = xml + self.expr
		xml = xml + "\n\t</action>"
		return xml
