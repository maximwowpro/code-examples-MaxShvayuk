# Delete old compilation results
if { [file exists "work"] } {
    vdel -all
}

# Create new modelsim working library
vlib work

# Compile all the Verilog sources in current folder into working library
vlog  alu.v alu_tb.v barrel_shifter.v

# Open testbench module for simulation
vsim -novopt work.alu_tb

# Add all testbench signals to waveform diagram
add wave sim:/alu_tb/*

# Run simulation
run -all
