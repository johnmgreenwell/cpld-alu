//----------------------------------------------------------------------------
// Name        : mux21.v
// Purpose     : Multiplexer 2-to-1 Module
// Description :
//               This Verilog module defines a 2-to-1 multiplexer of bus
//               width N.
//
// Language    : Verilog
// Requires    : Libraries      : N/A
//               Custom Designs : N/A
// Copyright   : MIT 2021 John Greenwell
//----------------------------------------------------------------------------

module mux21
#(
    parameter N = 8
)
(
    input  sel,
    input  [N-1:0] d0,
    input  [N-1:0] d1,
    output [N-1:0] out
);

assign out = sel ? d1 : d0;

endmodule