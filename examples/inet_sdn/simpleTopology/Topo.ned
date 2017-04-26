//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

package inet.examples.inet_sdn.simpleTopology;

import inet.networklayer.autorouting.ipv4.FlatNetworkConfigurator;
import inet.util.ThruputMeteringChannel;
import inet.globalfilter.GlobalFilter;
import inet.openflow.nodes.*;
import inet.nodes.inet.StandardHost;
import inet.exmachina.ExMachina;

network Topo
{
	parameters:		
		string attackConfigurationFile = default("none");
		
	@display("bgb=600,450");
	types:
        channel ethernetline extends ThruputMeteringChannel {
            //delay = 1us;
            //datarate = 1Gbps;
            datarate = 100Mbps;
        }
	submodules:
		globalFilter: GlobalFilter {
			@display("p=1800,200");
		}

        exmachina: ExMachina {
           parameters:
                @display("p=1800, 400");
        }
		configurator: FlatNetworkConfigurator {
            parameters:
                @display("p=1800, 600");
        }
        client: StandardHost {
            @display("p=30,300;i=device/laptop");
        }
        server: StandardHost {
            @display("p=570,300;i=device/server");
        }
        
        // OpenFlow switches
        s1: Open_Flow_Switch_SEA  {
            @display("p=300,300");
        }
        // SDN controller
        controller: Open_Flow_Controller_SEA {
            @display("p=300,41");
        }
        
	connections allowunconnected:
	    s1.ethg++ <--> ethernetline <--> client.ethg++;
	    s1.ethg++ <--> ethernetline <--> server.ethg++;
	
	    s1.gate_controller++ <-->  ethernetline <--> controller.ethg++;
	
		globalFilter.nodes++ <--> { @display("ls=,0");} <--> s1.global_filter;							        
		globalFilter.nodes++ <--> { @display("ls=,0");} <--> controller.global_filter;
		
		globalFilter.nodes++ <--> { @display("ls=,0");} <--> client.global_filter;
		globalFilter.nodes++ <--> { @display("ls=,0");} <--> server.global_filter;
}


