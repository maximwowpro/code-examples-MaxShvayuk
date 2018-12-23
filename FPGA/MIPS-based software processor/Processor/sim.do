# Delete old compilation results
if { [file exists "work"] } {
    vdel -all
}

# Create new modelsim working library
vlib work

# Compile all the Verilog sources in current folder into working library
vlog  _mips_control__alu_unit.v _mips_control__main_unit.v _mips_data_tract.v _mips_processor.v alu.v barrel_shifter.v data_memory.v instruction_memory.v mips_processor_tb.v mux_5_bit.v mux_32_bit.v program_counter.v register_file.v sign_extender.v 

# Open testbench module for simulation
vsim -novopt work.testbench

# Add all testbench signals to waveform diagram
add wave sim:/testbench/*
add wave sim:/testbench/processor/data_tract/register_file/matrix

# Run simulation
run -all
