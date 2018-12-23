# Delete old compilation results
if { [file exists "work"] } {
    vdel -all
}

# Create new modelsim working library
vlib work

# Compile all the Verilog sources in current folder into working library
vlog  data_memory.v data_memory_tb.v

# Open testbench module for simulation
vsim -novopt work.data_memory_tb__

# Add all testbench signals to waveform diagram
add wave sim:/data_memory_tb__/*

# Run simulation
run -all
