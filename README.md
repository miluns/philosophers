*This project has been created as part of the 42 curriculum by mstawski.*

# Philosophers

## Description

The **Philosophers** project is an implementation of the classic computer science problem: the Dining Philosophers. The primary goal of this project is to learn the basics of threading a process, understanding concurrency, and managing shared resources to prevent deadlocks and data races. 

In this simulation, a given number of philosophers sit at a round table. They alternate between three states: **eating**, **thinking**, and **sleeping**. 
* There is one fork placed between each pair of philosophers. 
* To eat, a philosopher must acquire two forks (the one on their left and the one on their right). 
* Since the forks are shared resources, the simulation must carefully manage how they are picked up and put down using mutexes to ensure no philosopher starves to death and the system does not deadlock.

## Instructions

### Compilation
The project includes a `Makefile` to compile the source code. To compile the program, navigate to the root of the repository and run:

```bash
make
