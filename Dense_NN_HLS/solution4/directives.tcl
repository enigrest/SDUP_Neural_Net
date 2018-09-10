############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
set_directive_resource -core RAM_2P_BRAM "testCell" img->pixel
set_directive_interface -mode s_axilite "testCell" c->input
set_directive_interface -mode s_axilite "testCell" c->weight
set_directive_interface -mode s_axilite "testCell" c->output
set_directive_interface -mode s_axilite "testCell" c->bias
set_directive_interface -mode s_axilite "testCell" img->pixel
set_directive_interface -mode s_axilite "testCell" target
set_directive_interface -mode s_axilite "testCell"
set_directive_unroll "testCell/loop"
