# Delete old compilation results
if { [file exists "work"] } {
    vdel -all
}

# Create new modelsim working library
vlib work

# Compile all the Verilog sources in current folder into working library
vlog  register_file.v register_file_tb.v

# Open testbench module for simulation
vsim -novopt work.register_file_tb

# Add all testbench signals to waveform diagram
add wave sim:/register_file_tb/*

# Run simulation
run -all
