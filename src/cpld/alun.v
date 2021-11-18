//----------------------------------------------------------------------------
// Name        : alun.v
// Purpose     : N-bit Arithmetic Logic Unit (ALU) Module
// Description :
//               This Verilog module defines a generic arithmetic logic
//               unit (ALU) in terms of structural modeling.
//
//               Given input along with the command signals {m, s1, s0}, the
//               ALU will perform the following operations:
//
//               m,s1,s0  |  Output f
//               ---------|----------------
//                0 0 0   |  complement(a)
//                0 0 1   |  a AND b
//                0 1 0   |  identity(a)
//                0 1 1   |  a OR b
//                1 0 0   |  decrement(a)
//                1 0 1   |  a + b
//                1 1 0   |  a - b
//                1 1 1   |  increment(a)
//
// Language    : Verilog
// Requires    : Libraries      : N/A
//               Custom Designs : len.v,
//                                aen.v,
//                                fa1.v,
//                                nandn.v,
//                                xorn.v,
//                                mux21.v
// Copyright   : MIT 2021 John Greenwell
//----------------------------------------------------------------------------

module alun
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

wire cin_logic;
wire [N-1:0] ci_co;
wire [N-1:0] ae_array;
wire [N-1:0] le_array;

nandn #(2) cin_logic_gate (
    .in({m, s[1]}),
    .out(cin_logic)
);

xorn #(2) cout_logic_gate (
    .in({c, ci_co[N-2]}),
    .out(v)
);

aen #(N) ae_array_module (
    .m(m),
    .s(s),
    .b(b),
    .y(ae_array)
);

len #(N) le_array_module (
    .m(m),
    .s(s),
    .a(a),
    .b(b),
    .x(le_array)
);

fa1 fa1_N
(
    .a(le_array[N-1]),
    .b(ae_array[N-1]),
    .ci(ci_co[N-2]),
    .s(f[N-1]),
    .co(c)
);

genvar i;
generate
    for (i=N-2; i>0; i=i-1) begin : fa_generator
        fa1 fa1_i
        (
            .a(le_array[i]),
            .b(ae_array[i]),
            .ci(ci_co[i-1]),
            .s(f[i]),
            .co(ci_co[i])
        );
    end
endgenerate

fa1 fa1_0
(
    .a(le_array[0]),
    .b(ae_array[0]),
    .ci(~cin_logic),
    .s(f[0]),
    .co(ci_co[0])
);


endmodule