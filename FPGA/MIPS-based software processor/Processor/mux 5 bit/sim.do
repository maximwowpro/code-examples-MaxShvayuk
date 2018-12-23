# Delete old compilation results
if { [file exists "work"] } {
    vdel -all
}

# Create new modelsim working library
vlib work

# Compile all the Verilog sources in current folder into working library
vlog  mux_5_bit.v mux_5_bit_tb.v

# Open testbench module for simulation
vsim -novopt work.mux_5_bit_tb

# Add all testbench signals to waveform diagram
add wave sim:/mux_5_bit_tb/*

# Run simulation
run -all
