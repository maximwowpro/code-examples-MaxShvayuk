# Delete old compilation results
if { [file exists "work"] } {
    vdel -all
}

# Create new modelsim working library
vlib work

# Compile all the Verilog sources in current folder into working library
vlog  barrel_shifter.v barrel_shifter_tb.v

# Open testbench module for simulation
vsim -novopt work.barrel_shifter_tb

# Add all testbench signals to waveform diagram
add wave sim:/barrel_shifter_tb/*

# Run simulation
run -all
