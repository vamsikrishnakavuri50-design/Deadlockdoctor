# DeadlockDoctor - System Architecture

## 1. Architecture Overview

DeadlockDoctor follows a modular architecture for implementing
Banker's Algorithm based deadlock avoidance.

The system accepts process and resource information from the user,
stores the information in the BankerState structure, and passes the
state to the Banker algorithm module.

The Banker module calculates the Need matrix, checks system safety,
and processes resource requests.

The final result indicates whether the system is SAFE or UNSAFE and
whether a requested resource allocation can be GRANTED or DENIED.

---

## 2. Major Components

### main.c - Control and Input Module

The main module controls the overall execution flow of DeadlockDoctor.

Responsibilities:

- Accept number of processes.
- Accept number of resources.
- Accept Available resources.
- Accept Maximum matrix.
- Accept Allocation matrix.
- Validate input values.
- Calculate the Need matrix.
- Perform the initial safety check.
- Accept resource requests.
- Display final results.

---

### banker.c - Core Banker Algorithm Module

The Banker module contains the core deadlock avoidance logic.

It provides the following functions:

- calculate_need()
- check_safety()
- request_resources()
- display_state()
- display_safe_sequence()

The module implements both the Banker Safety Algorithm and the
Banker's Resource Request Algorithm.

---

### banker.h - Data Structure and Interface

The banker.h header defines the BankerState structure and the
function interfaces used by the project.

BankerState contains:

- processes
- resources
- available
- maximum
- allocation
- need
- safe_sequence

The Need matrix is calculated using:

    Need = Maximum - Allocation

---

### manager.c - Reserved Management Module

The manager.c source file is currently included in the project
structure as a reserved module for future process and resource
management functionality.

The current implementation does not contain active management logic.
The primary process and resource input handling is currently performed
by main.c.

### display.c - Reserved Display Module

The display.c source file is currently included in the project
structure as a reserved presentation module.

The current implementation does not contain active display logic.
The functions display_state() and display_safe_sequence() are
currently implemented in banker.c.

### tests/ - Automated Testing Module

The tests directory contains the automated Banker algorithm test
suite.

Files:

- test_banker.c
- run_tests.sh

The test suite validates safe states, unsafe states, valid resource
requests, invalid requests, insufficient resources, and rollback
behavior.

---

## 3. System Workflow

The system follows this execution flow:

User Input
    |
    v
main.c
    |
    v
BankerState
    |
    v
calculate_need()
    |
    v
check_safety()
    |
    +---- SAFE ----> Safe Sequence
    |
    +---- UNSAFE --> System Rejected

For a resource request:

Resource Request
    |
    v
Request <= Need ?
    |
    +---- NO ----> DENY
    |
    v
Request <= Available ?
    |
    +---- NO ----> CANNOT BE GRANTED NOW
    |
    v
Temporary Allocation
    |
    v
Safety Algorithm
    |
    +---- SAFE ----> GRANT
    |
    +---- UNSAFE --> ROLLBACK
---

## 4. Final System Outputs

The system displays:

- Available resources.
- Maximum matrix.
- Allocation matrix.
- Need matrix.
- Initial system safety status.
- Safe sequence.
- Resource request.
- Request decision.
- State after request.
- Final system safety status.

Possible request results include:

- REQUEST GRANTED
- REQUEST DENIED
- REQUEST CANNOT BE GRANTED NOW

---

## 5. Testing Architecture

The automated testing layer is separated from the main interactive
program.

The test execution flow is:

test_banker.c
    |
    v
Banker algorithm functions
    |
    v
Test cases
    |
    v
PASS / FAIL

The current automated test suite contains seven test cases:

1. Safe initial state.
2. Unsafe initial state.
3. Valid request.
4. Request exceeding Need.
5. Request exceeding Available.
6. Unsafe request and rollback.
7. Invalid process request.

The test suite is executed using:

    ./tests/run_tests.sh
