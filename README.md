# DeadlockDoctor

## Banker’s Algorithm Based Deadlock Avoidance System

DeadlockDoctor is an Operating Systems and Systems Programming project
that implements the Banker’s Algorithm for proactive deadlock avoidance.

The system evaluates the current allocation state of processes and
resources and grants a resource request only when the resulting system
state remains safe.

---

## 1. Problem Statement

In a multiprogramming operating system, multiple processes compete for
limited resources. Incorrect resource allocation can cause the system
to enter an unsafe state and may eventually lead to deadlock.

DeadlockDoctor provides a simulation-based solution using Banker’s
Algorithm to determine whether a system is in a safe state and whether
a resource request can be safely granted.

---

## 2. Objectives

The main objectives of DeadlockDoctor are:

1. Calculate the Need matrix from Maximum and Allocation matrices.
2. Determine whether the current system state is safe.
3. Generate a safe sequence when one exists.
4. Process resource requests from individual processes.
5. Grant requests only when the resulting state remains safe.
6. Deny requests that exceed Need or Available resources.
7. Roll back temporary allocations when a request produces an unsafe state.
8. Provide automated testing for the implemented Banker’s Algorithm.

---

## 3. Algorithm Used

DeadlockDoctor implements Banker’s Algorithm.

### Banker State

The system maintains:

- Available
- Maximum
- Allocation
- Need

The Need matrix is calculated using:

    Need = Maximum - Allocation

### Safety Algorithm

The safety algorithm:

1. Initializes Work with Available resources.
2. Finds a process whose Need is less than or equal to Work.
3. Simulates completion of that process.
4. Releases its allocated resources back to Work.
5. Adds the process to the safe sequence.
6. Repeats until all processes finish or no process can proceed.

If every process can finish, the system is SAFE.

Otherwise, the system is UNSAFE.

---

## 4. Resource Request Algorithm

For every resource request:

1. Check Request <= Need.
2. Check Request <= Available.
3. Temporarily allocate the requested resources.
4. Run the safety algorithm.
5. Grant the request if the resulting state is safe.
6. Roll back the temporary allocation if the resulting state is unsafe.

---

## 5. Project Structure

```text
deadlockdoctor/
│
├── Makefile
├── README.md
│
├── include/
│   ├── banker.h
│   ├── manager.h
│   └── display.h
│
├── src/
│   ├── main.c
│   ├── banker.c
│   ├── manager.c
│   └── display.c
│
├── tests/
│   ├── test_banker.c
│   ├── run_tests.sh
│   └── test_banker
│
└── scenarios/
