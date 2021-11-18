//----------------------------------------------------------------------------
// Name        : ae1.v
// Purpose     : Single-bit Arithmetic Element Module
// Description :
//               This Verilog module defines a 1-bit arithmetic element in
//               terms of structural modeling.
//
// Language    : Verilog
// Requires    : Libraries      : N/A
//               Custom Designs : mux21.v
//                                nandn.v
// Copyright   : MIT 2021 John Greenwell
//----------------------------------------------------------------------------

module ae1
(
    input m,
    input [1:0] s,
    input b,
    output y
);

wire s1_nand_b;
wire s0_nand_b;
wire mux_in1;

mux21 #(1) mux_m (
    .sel(m),
    .d0(1'b0),
    .d1(mux_in1),
    .out(y)
);

nandn #(2) nand1
(
    .in({~s[1], b}),
    .out(s1_nand_b)
);

nandn #(2) nand2
(
    .in({~s[0], ~b}),
    .out(s0_nand_b)
);

nandn #(2) nand3
(
    .in({s1_nand_b, s0_nand_b}),
    .out(mux_in1)
);


endmodule