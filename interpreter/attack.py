"""

This file defines classes for the three kinds of attacks ammitted by the attack specification language.
Every class includes a method that returns an XML block related to the attack execution.

Authors:
Alessandro Pischedda	alessandro.pischedda@gmail.com
Marco Tiloca		marco.tiloca84@gmail.com

"""

class PhysicalAttack:

	time = "" # attack occurrence time
	nodes = "" # list of involved nodes
	stmts = [] # list of actions

	# t - time , n - nodes, s - statements
	def __init__(self, t, n, s):
		self.time = t
		self.nodes = n
		self.stmts = list(s)

	def __str__(self):
		xml = "\n<Attack>\n\t<start_time>"+self.time+"</start_time>"

		xml = xml+"\n\t<node>"+self.nodes+"</node>"

		for stmt in self.stmts:
			xml = xml +"\n"+str(stmt)

		xml = xml+"\n</Attack>\n"

		return xml


class ConditionalAttack:

	time = ""  # attack first occurrence time
	nodes = "" # list of involved nodes
	stmts = [] # list of actions
	var_dict = {} # dictionary of variables <name, XML string>
	packetFilter = "" # packet filter

	# t - time , n - nodes, v - variables, s - statements, f - packet filter
	def __init__(self, t, n, v, s, f):
		self.time = t
		self.nodes = n
		self.stmts = list(s)
		self.var_dict = dict(v)
		self.stmts = list(s)
		self.packetFilter = f

	def __str__(self):
		xml = "\n<Attack>\n\t<start_time>"+self.time+"</start_time>"
		
		xml = xml+"\n\t<node>"+self.nodes+"</node>"

		for key in self.var_dict.keys():
			xml = xml + "\n\t<var><name>"+str(key)+"</name>"+str(self.var_dict[key])+"</var>"

		xml = xml + "\n\t<filter>" + self.packetFilter + "</filter>\n"
			
		for stmt in self.stmts:
			xml = xml + "\n"+str(stmt)

		xml = xml+"\n</Attack>\n"

		return xml


class UnconditionalAttack:

	time = "" # attack first occurrence time
	stmts = [] # list of actions
	var_dict = {} # dictionary of variables <name, XML string>
	frequency = "" # attack repetition frequency

	# t - time , f - frequency , v - variables, s - statements
	def __init__(self, t, f, v, s):
		self.time = t
		self.stmts = list(s)
		self.var_dict = dict(v)
		self.frequency = f

	def __str__(self):
		xml = "\n<Attack>\n\t<start_time>"+self.time+"</start_time>"

		xml = xml + "\n\t<frequency>"+self.frequency+"</frequency>"

		for key in self.var_dict.keys():
			xml = xml+"\n\t<var><name>"+str(key)+"</name>"+str(self.var_dict[key])+"</var>"

		for stmt in self.stmts:
			xml = xml +"\n"+str(stmt)

		xml = xml+"\n</Attack>\n"

		return xml
