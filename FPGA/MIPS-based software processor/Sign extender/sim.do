# Delete old compilation results
if { [file exists "work"] } {
    vdel -all
}

# Create new modelsim working library
vlib work

# Compile all the Verilog sources in current folder into working library
vlog  sign_extender.v sign_extender_tb.v

# Open testbench module for simulation
vsim -novopt work.sign_extender_tb

# Add all testbench signals to waveform diagram
add wave sim:/sign_extender_tb/*

# Run simulation
run -all
