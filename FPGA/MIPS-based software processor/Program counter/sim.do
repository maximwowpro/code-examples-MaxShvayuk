# Delete old compilation results
if { [file exists "work"] } {
    vdel -all
}

# Create new modelsim working library
vlib work

# Compile all the Verilog sources in current folder into working library
vlog  program_counter.v program_counter_tb.v

# Open testbench module for simulation
vsim -novopt work.program_counter_tb

# Add all testbench signals to waveform diagram
add wave sim:/program_counter_tb/*

# Run simulation
run -all
