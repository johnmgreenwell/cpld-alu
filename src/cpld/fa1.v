//----------------------------------------------------------------------------
// Name        : fa1.v
// Purpose     : Single-bit Full Adder Module
// Description :
//               This Verilog module defines a 1-bit full adder in terms of
//               structural modeling.
//
// Language    : Verilog
// Requires    : Libraries      : N/A
//               Custom Designs : nandn.v
//                                xorn.v
// Copyright   : MIT 2021 John Greenwell
//----------------------------------------------------------------------------

module fa1
(
    input a,
    input b,
    input ci,
    output s,
    output co
);

wire a_nand_b;
wire a_xor_b;
wire a_xor_b_nand_c;

xorn #(2) xor1
(
    .in({a, b}),
    .out(a_xor_b)
);

xorn #(2) xor2
(
    .in({a_xor_b, ci}),
    .out(s)
);

nandn #(2) nand1
(
    .in({a_xor_b, ci}),
    .out(a_xor_b_nand_c)
);

nandn #(2) nand2
(
    .in({a, b}),
    .out(a_nand_b)
);

nandn #(2) nand3
(
    .in({a_nand_b, a_xor_b_nand_c}),
    .out(co)
);


endmodule