//----------------------------------------------------------------------------
// Name        : le1.v
// Purpose     : Single-bit Logic Element Module
// Description :
//               This Verilog module defines a 1-bit logic element in terms
//               of structural modeling.
//
// Language    : Verilog
// Requires    : Libraries      : N/A
//               Custom Designs : mux21.v,
//                                nandn.v
// Copyright   : MIT 2021 John Greenwell
//----------------------------------------------------------------------------

module le1
(
    input m,
    input [1:0] s,
    input a,
    input b,
    output x
);

wire s1_nand_s0_nand_a;
wire s0_nand_a_nand_b;
wire s1_nand_s0_nand_b;
wire a_nand_s1;
wire mux_in0;

mux21 #(1) mux_m (
    .sel(m),
    .d0(mux_in0),
    .d1(a),
    .out(x)
);

nandn #(2) nand1
(
    .in({a, s[1]}),
    .out(a_nand_s1)
);

nandn #(3) nand2
(
    .in({~s[1], ~s[0], ~a}),
    .out(s1_nand_s0_nand_a)
);

nandn #(3) nand3
(
    .in({s[0], a, b}),
    .out(s0_nand_a_nand_b)
);

nandn #(3) nand4
(
    .in({s[1], s[0], b}),
    .out(s1_nand_s0_nand_b)
);

nandn #(4) nand5
(
    .in({s1_nand_s0_nand_a, s0_nand_a_nand_b,
         s1_nand_s0_nand_b, a_nand_s1}),
    .out(mux_in0)
);


endmodule