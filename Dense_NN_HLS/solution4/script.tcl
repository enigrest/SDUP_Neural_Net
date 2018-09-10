############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
open_project Dense_NN_light
set_top testCell
add_files Dense_NN/testCell.c
add_files -tb Dense_NN_light/testCell_test.c
add_files -tb Dense_NN_light/util/screen.c
add_files -tb Dense_NN_light/util/mnist-utils.c
add_files -tb Dense_NN_light/util/mnist-stats.c
add_files -tb Dense_NN_light/1lnn.c
open_solution "solution4"
set_part {xc7z020clg484-1} -tool vivado
create_clock -period 10 -name default
source "./Dense_NN_light/solution4/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog
