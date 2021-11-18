//----------------------------------------------------------------------------
// Name        : aen.v
// Purpose     : N-bit Arithmetic Element Array Module
// Description :
//               This Verilog module defines a generic arithmetic element
//               array in terms of structural modeling.
//
// Language    : Verilog
// Requires    : Libraries      : N/A
//               Custom Designs : ae1.v
//                                mux21.v
//                                nandn.v
// Copyright   : MIT 2021 John Greenwell
//----------------------------------------------------------------------------

module aen
#(
    parameter N = 8
)
(
    input  m,
    input  [1:0] s,
    input  [N-1:0] b,
    output [N-1:0] y
);

genvar i;
generate
    for (i=0; i<N; i=i+1) begin : ae_generator
        ae1 ae1_i
        (
            .m(m),
            .s(s),
            .b(b[i]),
            .y(y[i])
        );
    end
endgenerate


endmodule