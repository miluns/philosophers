*This project has been created as part of the 42 curriculum by mstawski.*

# philosophers

The **philosophers** project is a command‑line program that simulates a concurrent environment to solve the classic dining philosophers problem. The execution process relies on multiple threads and a strictly limited set of shared resources, making the task an algorithmic and structural challenge centered around thread synchronization and resource management.

## Description

The project explores how complex concurrent behavior can be managed while avoiding common synchronization pitfalls such as deadlocks and data races. By requiring the program to carefully control thread lifecycles and protect shared memory spaces (forks), the project emphasizes control‑flow design, precise timing, and thoughtful resource allocation.

**Core Functionality**

The program:
* Accepts a series of integer arguments defining the simulation rules.
* Validates and parses input, ensuring correctness and safety.
* Initializes mutexes to represent shared forks between adjacent philosophers.
* Constructs and manages concurrent threads representing individual philosophers.
* Outputs the state changes of each philosopher in a precise chronological order.

The simulated actions include:
* **Eating**: requires successfully acquiring two adjacent forks (mutex locks).
* **Sleeping**: a fixed duration of inactivity following a meal.
* **Thinking**: the default state when waiting for shared resources to become available.
* **Dying**: triggered if a philosopher exceeds the maximum allowed time without eating.

These constraints require a carefully structured approach to produce a stable execution that ensures continuous resource rotation and prevents thread starvation.

**Project Characteristics**

The project emphasizes:
* Deterministic control over multi-threaded execution and state tracking.
* Efficient logical structuring of mutex locks to prevent deadlocks.
* Clear separation of concerns within the concurrent codebase.
* Consistent behavior across execution edge cases, including CPU scheduling delays and precision timing routines.

## Instructions

**Build and usage**

```bash
# Clone the repository
git clone git@github.com:mstawski/philosophers.git
cd philosophers/philo

# Compile the program
make

# Run the program with required parameters:
# ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]

# Example execution:
./philo 5 800 200 200
```

## Resources

**References & Documentation:**
* Wikipedia: Dining Philosophers Problem - Overview of the classic problem and theoretical solutions.
* POSIX Threads (pthreads) Documentation - Guide on how to create, manage, and synchronize threads in C.
* Mutexes in C - Understanding how to use pthread_mutex_init, pthread_mutex_lock, and pthread_mutex_unlock to protect shared resources.

**AI Usage:**
Large Language Models (like ChatGPT/Gemini) were used during the research phase of this project to better understand the concept of thread deadlocks and to conceptualize the logic for avoiding data races. AI was not used to write the core simulation code or the synchronization algorithms, which were implemented manually.
