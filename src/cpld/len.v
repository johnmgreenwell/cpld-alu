//----------------------------------------------------------------------------
// Name        : len.v
// Purpose     : N-bit Arithmetic Logic Array Module
// Description :
//               This Verilog module defines a generic logic element array
//               in terms of structural modeling.
//
// Language    : Verilog
// Requires    : Libraries      : N/A
//               Custom Designs : le1.v
//                                mux21.v
//                                nandn.v
// Copyright   : MIT 2021 John Greenwell
//----------------------------------------------------------------------------

module len
#(
    parameter N = 8
)
(
    input  m,
    input  [1:0] s,
    input  [N-1:0] a,
    input  [N-1:0] b,
    output [N-1:0] x
);

genvar i;
generate
    for (i=0; i<N; i=i+1) begin : ae_generator
        le1 le1_i
        (
            .m(m),
            .s(s),
            .a(a[i]),
            .b(b[i]),
            .x(x[i])
        );
    end
endgenerate


endmodule