Binary Arithmetic-Logic Unit (ALU) Simulator
This is a C++ console application that simulates a simple Arithmetic-Logic Unit (ALU) from the ground up. It performs m,n-bit binary arithmetic operations on string-based binary inputs, demonstrating the fundamental logic used in CPU hardware.

Features
The calculator supports six primary operations:
Addition (+)
Subtraction (-)
Multiplication (*)
Division (/)
Modulo/Remainder (%)
Exponentiation (^)

Core Concepts Demonstrated
This project was built from first principles and showcases several key computer science concepts:

1. Logic Gate Simulation: The core adder is built by simulating XOR, AND, and OR gates (get_bitwise_sum, get_carry).
2. Full-Adder Logic: These gates are combined to create a full-adder, which is then chained into an n-bit ripple-carry adder (get_final_sum) to add binary numbers of any length.
3. Two's Complement: Subtraction (get_subtraction) is implemented by first finding the two's complement of the subtrahend and then adding it to the minuend, reusing the core adder.
4. Shift-and-Add Multiplication: The multiply function implements the classic "shift and add" algorithm, which forms the basis of binary multiplication in hardware.
5. Restoring Division: The division function implements the Restoring Division algorithm (Shift-and-Subtract). It iterates through the dividend bit-by-bit, maintaining a partial remainder and utilizing the subtraction unit to determine quotient bits.
6. Exponentiation by Repeated Multiplication: The power function demonstrates a simple algorithm by converting the binary exponent to decimal and performing repeated multiplication.

Technologies Used:
C++
Visual Studio (Solution file .sln included)

How to Run
Clone the repository.
Open the BinaryArithmetics.sln file in Visual Studio.
Build and run the project (F5).
Follow the prompts to enter two binary numbers and an operator (+, -, *, /, %, ^).
