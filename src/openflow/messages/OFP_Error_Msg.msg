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
}};

packet Open_Flow_Message;

packet OFP_Error_Msg extends Open_Flow_Message
{
    uint16_t type;
    uint16_t code;
    //uint8_t data[64]; //Variable-length data.  Interpreted based on the type and code. 
                    // OFPET_FLOW_MOD_FAILED: The data field contains at least 64 bytes of the failed request.
}
