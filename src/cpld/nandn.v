//----------------------------------------------------------------------------
// Name        : nandn.v
// Purpose     : Generic NAND Module
// Description :
//               This Verilog module defines a generic NAND gate.
//
// Language    : Verilog
// Requires    : Libraries      : N/A
//               Custom Designs : N/A
// Copyright   : MIT 2021 John Greenwell
//----------------------------------------------------------------------------

module nandn
#(
    parameter N = 2
)
(
    input [N-1:0] in,
    output out
);

assign out = ~&in;

endmodule