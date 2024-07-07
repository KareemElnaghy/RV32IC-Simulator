# RV32IC Simulator Project

## Group Members
- **Kareem Elnaghy**
- **Malek Mahmoud**
- **Mazin Bersy**

## Introduction
Welcome to the RV32IC Simulator project. This project implements an Instruction Set Simulator (ISS) for the RISC-V RV32IC Base Integer Instruction Set with support for instruction compression. The simulator is designed to read machine code files, decode instructions, execute them, and print the results. This project aims to provide a practical understanding of CPU instruction execution and RISC-V architecture.

## Objectives
- **Instruction Decoding:** Decode RV32I machine code instructions.
- **Instruction Execution:** Execute decoded instructions, modifying registers or memory as required.
- **Console Output:** Print decoded instructions and execution results through the ECALL instruction to the console.
- **Support for Compressed Instructions:** Optionally support RV32IC compressed instructions.

## Components
- **Programming Language:** C++.
- **Input Files:** Machine code file (as binary files), optional data section file, test cases generated using RARS.
- **Command Line Interface:** Simulator is invoked from the command line.

## How to Build and Use the Simulator
1. **Clone the Repository:**
   ```bash
   git clone https://github.com/KareemElnaghy/RV32IC-Simulator.git
   cd rv32ic-simulator
2. **Build the Simulator:**
   ```bash
   g++ -o rvsim main.cpp Register.cpp
3. **Run the Program using the following format:**
   ```bash  
   rvsim <machine_code_file_name> [data_section_file_name]

## Simulator Design
1. **Main Module:**
    This module is responsible for the entire simulation process. It initializes the      system, manages the execution flow, handles the file input for both machine code      and the optional data section, controls the simulation loop which fetches and         executes the instructions based on the program counter.
2. **Register Module:**
    Defines the 'Register' class which simulates the behavior and properties of the RV32IC CPU register within the simulation. Each Register is initialised with its Application Binary Interface (ABI), such as "zero" for the first register. Required helper functions were developed.
3. **Instruction Handling:**
This component contains individual functions for decoding and executing various instruction types, ensuring the simulator can handle a broad spectrum of operations as defined in the RISC-V ISA:
- **R-type Instructions:** For register-register arithmetic and logical operations. Examples include ADD, SUB, AND, OR, XOR, etc.
- **I-type Instructions:** Utilize immediate values for arithmetic, logical, and load operations. These include ADDI, SLTI, ANDI, LW, etc.
- **S-type Instructions:** For store operations, allowing values from registers to be stored into memory locations specified by the address calculations. Examples include SW, SH, SB, etc.
- **B-type Instructions:** For conditional branches, which alter the program flow based on comparison results. Examples are BEQ, BNE, BLT, BGE, etc.
- **U-type Instructions:** For manipulating upper immediate values and setting the upper bits of a register. This includes instructions like LUI and AUIPC.
- **J-type Instructions:** For unconditional jumps that provide mechanisms for function calls and returns. Examples include JAL and JALR.
- The module also robustly handles system calls through the `ecall` function, which processes various requests such as program termination or console outputs based on values stored in specific registers.
- **Compressed Instructions:** Execution of compressed instructions is integrated using the same functions used for basic integer type instructions. This allows the simulator to handle both standard and compressed formats seamlessly, by expanding compressed instructions into their full-size counterparts before execution.

## Challenges

During the development of our RISC-V simulator, we faced several challenges that tested our implementation:

- **Program Counter Management:** Handling the program counter for jump instructions and compressed instructions presented complexities. Properly calculating jump targets and managing program flow with compressed formats required further attention to ensure accuracy.

- **Instruction Decoding:** We encountered difficulties in reading instruction words and half-words for compressed instructions at times. The issue stemmed from incorrect handling of store instructions leading to improperly decoded instructions.

- **Memory Operations Debugging:** Debugging the content being stored and accessed through memory using load and store instructions was particularly challenging. Ensuring that data was correctly written to and read from the expected memory addresses required extensive testing and verification.

- **Test Case Development:** Creating effective test cases that utilize the `.data` section posed a challenge due to the differences in addresses and memory sizes between our simulation environment and standard RISC-V simulators like RARS.

### Limitations

- **Incomplete Test Coverage:** Currently, we have not generated test cases that comprehensively test all implemented instructions. This is due to RARS, the primary assembler we used to generate instructions lacking features to assemble compressed instructions.

- **Issues with Compressed Instructions:** We have identified specific issues with some compressed instructions, particularly compressed jump and branch instructions. These problems appeared in test cases where the expected behavior does not align with the simulated outcomes, indicating potential inaccuracies in instruction decoding or execution logic.

- ## Contributions
- [Kareem Elnaghy](https://github.com/KareemElnaghy) 
- [Malek Mahmoud](https://github.com/malekrouk)
- [Mazin Bersy](https://github.com/mazinbersy) 
