//----------------------------------------------------------------------------
// Name        : cpld_alu_top.v
// Purpose     : Simple ALU Test Design Project
// Description :
//               This Verilog top module file provides a testbench for a
//               generic simple ALU defined strcuturally using basic gates.
//
// Platform    : Altera MAX II Breakout Board
// Language    : Verilog
// Requires    : Libraries      : N/A
//               Custom Designs : alun.v
//                                len.v,
//                                aen.v,
//                                fa1.v,
//                                nandn.v,
//                                xorn.v,
//                                mux21.v
// Copyright   : MIT 2021 John Greenwell
//----------------------------------------------------------------------------

module cpld_alu_top
#(
    parameter N = 8
)
(
    input  m,
    input  [1:0] s,
    input  [N-1:0] a,
    input  [N-1:0] b,
    output [N-1:0] f,
    output v,
    output c
);

alun #(N) uut (
    .m(m),
    .s(s),
    .a(a),
    .b(b),
    .f(f),
    .v(v),
    .c(c)
);


endmodule