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

cplusplus {{
    #include "openflow.h"
    #include "Open_Flow_Message_m.h"
    typedef ofp_flow_stats *FlowStatsPtr;
}};

packet Open_Flow_Message;
struct ofp_header;
struct oxm_basic_match;
struct ofp_action_output;
struct ofp_flow_stats;
class noncobject FlowStatsPtr;

packet OFP_Flow_Stats_Reply extends Open_Flow_Message
{
	int datapath_Id;
	FlowStatsPtr flowStatsArray[];
}
