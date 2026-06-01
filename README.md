# Cache Simulator & Performance Visualizer

## Overview
This project is a configurable cache memory simulator written in C++. It models cache behavior under a user-defined configuration and access pattern, tracking key performance metrics such as cache hits, misses, and hit rate.

To enhance analysis, a Python script processes simulation output and generates an Excel report along with a bar charts for visual comparison of performance across runs.


## Features
- Configurable cache parameters:
  - Block size
  - Associativity
  - Access patterns
- Performance tracking:
  - Cache hits
  - Cache misses
  - Hit rate calculation
- CSV output for simulation results
- Python analysis with graph

## How It Works

1. The C++ simulator prompts the user for block size, associativity, and memory access pattern inputs.
2. The simulator runs under the parameters and calculates hit rate.
3. Results are written to 'cache_results.csv'.
4. The Python script reads the CSV file.
5. Data is converted into an Excel file with formatted tables.
6. A bar chart is generated showing cache hit rates per run.
