# Binary Arithmetic-Logic Unit (ALU) Simulator

This is a C++ console application that simulates a simple Arithmetic-Logic Unit (ALU) from the ground up. It performs n-bit binary arithmetic operations on string-based binary inputs, demonstrating the fundamental logic used in CPU hardware.

## Features

The calculator supports four primary operations:
* **Addition (`+`)**
* **Subtraction (`-`)**
* **Multiplication (`*`)**
* **Exponentiation (`^`)**

## Core Concepts Demonstrated

This project was built from first principles and showcases several key computer science concepts:

* **Logic Gate Simulation:** The core adder is built by simulating `XOR`, `AND`, and `OR` gates (`get_bitwise_sum`, `get_carry`).
* **Full-Adder Logic:** These gates are combined to create a full-adder, which is then chained into an **n-bit ripple-carry adder** (`get_final_sum`) to add binary numbers of any length.
* **Two's Complement:** Subtraction (`get_subtraction`) is implemented by first finding the two's complement of the subtrahend and then adding it to the minuend, reusing the core adder.
* **Shift-and-Add Multiplication:** The `multiply` function implements the classic "shift and add" algorithm, which forms the basis of binary multiplication in hardware.
* **Exponentiation by Repeated Multiplication:** The `power` function demonstrates a simple algorithm by converting the binary exponent to decimal and performing repeated multiplication.

## Technologies Used

* **C++**
* **Visual Studio** (Solution file `.sln` included)

## How to Run

1.  Clone the repository.
2.  Open the `BinaryArithmetics.sln` file in Visual Studio.
3.  Build and run the project (F5).
4.  Follow the prompts to enter two binary numbers and an operator (`+`, `-`, `*`, `^`).
