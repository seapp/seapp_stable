package inet.examples.seapp.simpleTopo;

import inet.nodes.inet.StandardHost;
import inet.nodes.ethernet.EtherSwitch;
import inet.networklayer.autorouting.ipv4.IPv4NetworkConfigurator;
import inet.util.ThruputMeteringChannel;
import inet.globalfilter.GlobalFilter;
import inet.exmachina.ExMachina;

network Scenario
{
	parameters:
		string attackConfigurationFile = default("none");
	@display("bgb=600,300");
	types:
        channel ethernetline extends ThruputMeteringChannel
        {
            delay = 1us;
            datarate = 100Mbps;
            thruputDisplayFormat = "u";
        }
	submodules:
        configurator: IPv4NetworkConfigurator {
            parameters:
                @display("p=40,40");
        }
        globalFilter: GlobalFilter {
			@display("p=350,50;");
		};
        client1: StandardHost {
            @display("p=200,100;i=device/laptop");
        }
		client2: StandardHost {
            @display("p=200,200;i=device/laptop");
        }
        server: StandardHost {
			@display("p=500,150;i=device/server");
        }
    	switch: EtherSwitch {
			parameters:
           		@display("p=350,150");
    	}
        exmachina: ExMachina {
           parameters:
                @display("p=1800, 700");
        }
        
	connections allowunconnected:
		switch.ethg++  <--> ethernetline <--> client1.ethg++;
		switch.ethg++  <--> ethernetline <--> client2.ethg++;
		switch.ethg++  <--> ethernetline <--> server.ethg++;
		
		globalFilter.nodes++ <--> client1.global_filter;
		globalFilter.nodes++ <--> client2.global_filter;
		globalFilter.nodes++ <--> server.global_filter;
        		
}
