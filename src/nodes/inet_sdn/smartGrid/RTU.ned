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

package inet.nodes.inet_sdn.smartGrid;

import inet.nodes.inet.StandardHost;
import inet.applications.inet_sdn.smartGrid.RTUApp;
import inet.applications.inet_sdn.smartGrid.IED;
import inet.transport.ITCP;

module RTU extends StandardHost {
    parameters:
        @display("i=device/pc2");
        int IEDs = default (2);
    submodules:
        ied[IEDs]: IED {
            @display("p=400,100,r,80");
        }
        rtu: RTUApp;
        tcp: <tcpType> like ITCP {}
        
    connections allowunconnected:
        // TCP-based    
        tcp.appOut++ --> localFilter.app_tcp_inf$i++;
		tcp.appIn++ <-- localFilter.app_tcp_inf$o++;
		rtu.tcpIn <-- localFilter.app_tcp_sup$o++;
		rtu.tcpOut --> localFilter.app_tcp_sup$i++;
		
        tcp.ipOut --> localFilter.tcp_net_sup$i++;
		tcp.ipIn <-- localFilter.tcp_net_sup$o++;
		networkLayer.transportOut++ --> localFilter.tcp_net_inf$i++;
		networkLayer.transportIn++ <-- localFilter.tcp_net_inf$o++;
}

