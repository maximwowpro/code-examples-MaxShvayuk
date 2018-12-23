# Delete old compilation results
if { [file exists "work"] } {
    vdel -all
}

# Create new modelsim working library
vlib work

# Compile all the Verilog sources in current folder into working library
vlog  gpio_pin.v gpio_port.v gpio_module_tb.v tri_state.v gpio_module.v

# Open testbench module for simulation
vsim -novopt work.gpio_module_tb

# Add all testbench signals to waveform diagram
add wave sim:/gpio_module_tb/*

# Run simulation
run -all
