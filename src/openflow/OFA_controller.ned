//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package inet.openflow;


//Communication with OpenFlow switch;
//Sending Packet-Out messages;
//Sending Flow Modification messages;

simple OFA_controller
{
    parameters:
        string address = default("");
        int port = default(1000);
        @display("i=block/app");
        double serviceTime @unit("s") = default(0s);
        double statsInterval @unit ("s") = default(5s);
        double echoInterval @unit ("s") = default(500s);
        
    gates:
        input tcpIn @labels(TCPCommand/up);
        output tcpOut @labels(TCPCommand/down);
}
