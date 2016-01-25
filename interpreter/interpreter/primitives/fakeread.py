"""
Fakeread class models the 'fakeread' primitive. It tampers the sensors 
readings.

The sintax of the primitive is:
fakeread(nodeId, time, sensorId, function)
 + node Id is the Id of the target node
 + time is the occurrence time
 + sensorId is the target sensor of the target node
 + function is the reference to a mathematical function previously defined 
 
NB: nodeId and occurrence time are not stored in this object.

Authors:
 + Francesco Racciatti	<racciatti.francesco@gmail.com>
"""


from utilities import wrong_argc


class Fakeread:
    """
    fakeread(nodeId, time, sensorId, function)
    nodeId and time are not stored in this object
    """
    argv = []
    argc = 2	
    name = "Fakeread"
    
    def __init__(self, args):
        # Slit args only on the first ':'
        self.argv = args.split(":", 1)
    
    def __str__(self):
        if self.argc != len(self.argv):
            error_arguments(self.name, self.argc, len(self.argv))
        
        params = "sensor_id" + ":" + self.argv[0] + ":" + "function" + ":" + self.argv[1]
        xml = "\n\t\t\t<action>"
        xml += "\n\t\t\t\t<name>Fakeread</name>"
        xml += "\n\t\t\t\t<parameters>" + params + "</parameters>"
        xml += "\n\t\t\t</action>"
        
        return xml
