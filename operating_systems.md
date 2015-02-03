# Operating Systems
## Liviu Iftode
## Spring 2015

---
---

Food Pyramid
## 1/20/14

# Course Overview

### Goals:
- Understand how OS works
- Emphasis on design
- Learn how OS concepts are implemented in real operating systems (MIT xv6)

### Topics

- Computer Architecture overview
- OS structure
- Interrupt and System Call Handling
- Processes, threads, and synchronization
- CPU Scheduling
- Memory management and virtual memory
- File systems and I/O management

---
## 1/22/15

## What is an Operating System?
- Operating system is a software layer between the hardware and the application program.users: easy to use (hides complexity) and safe (prevents and handles errors)
- Acts as *resource manager* that allows programs/users to share the hardware resources in a protected way: fair and efficient

### Function

- Receives requests from the application: system calls
- Satisfies the requests: may issue commands to hardware
- Handles event (hardware interrupts): may upcall the application
- OS complexity: synchronous calls + asynchronous events
- OS is always running in the background
- The operating system is **not** an *interpreter*
	- If there is no system call or interrupt, the compiled application sits directly on the hardware

### Mechanism and Policy

- **Mechanisms:** data structures and operations that implement on abstraction
- **Policies:** the procedures that guide the selection of a certain course of action from among alternatives
- Traditional OS is **rigid:** mechanism is bound with policy

## System Abstraction: Processes

- A process is a system abstraction: illusion of being the only job in the system
	- create, kill processes, inter-process communication
	- Mechanism: creation, destruction, suspension, context switch, signaling operations
	Policy: Who can use processes?

## Memory Abstraction: Virtual memory

- Virtual memory is a memory abstraction:
	- Illusion of large contiguous memory, often more memory than physically available
- Mutual memory is also implemented in hardware

## History

- OS didn't exist in the beginning
	- Program binaries were loaded with switches
- CPUs were much fater than card readers and printers
- Disks were much faster as well
- Pipelined operations
- This was called **SPOOLING**, Simultaneous Peripheral Operation On-Line

### Time-Sharing vs. Real-Time

- **Time-sharing**: no demand on meeting certain deadlines.
- **Realtime:**
	- **Hard real-time**: medical imaging systems, industrial control systems
		- Catastrophic failure if system misses a deadline
		- Challenge lies in how to meet deadlines with minimal resource waste
	- **Soft real-time system:** multimedia applications
		- May be annoying but not catastrophic if a few deadlines are missed
		- **Challenge 1:** how to meet most deadlines with minimal resource waste
		- **Challenge 2:** how to load-shed if become overloaded

### Parallel OS

- Run some applications by running in parallel on many pressures
- Main goal is performance

## Distributed OS

- Clustering


## Embedded OS

- Pervasive computing
	- Cell phones and PDAs
- Characteristics:
	- Constrained resources: slow CPU, small memories, no disk
	- What's new about this? Isn't this just like the old computers?

## Virtual Machines and Hypervisors

- Popular in the 60's and 70's, vanished in the 80's and 90's
- Partition a physical machine into a number of virtual machines

---
## 1/29/15

# Caches

- Reading data from disk is hella slow
- Caches are used to quickly retrieve information from the hard disk
- Located close to the CPU
- Many layers of caches
- Fixed cost to transfer data

### Locality

- **Temporal**: caches stores what you used recently
- **Spatial**: caches store what's near what you used 

- No OS involved in anything involved with the cache; all hardware
- **Cache Pollution**: when other guys come into the cache (**context switching**?)???????????????
- Because memory cannot fit in cache, you will have many misses
- Caches are physical memory and have physical addresses
- However, your array is mapped in virtual memory and is definitely not mapped linearly

# Threads

### Kernel-level Threads (KLT)

- OS handles threads
- Each thread has a unique id

### User-level Threads (ULT)

- One operating system process
- If one thread is blocked, the entire process is blocked
- Cannot use more than one CPU

### Cooperative vs. Preemptive Threads

- Preemptive threads are in most OS (even Windows 95)
- Kernel can suspend a thread if it takes too long and context-switch to another thread

# Coroutines

- Ancestor to threads
- Each coroutine has its own thread
- Cannot see other coroutine's stacks
- C does not support coroutines but some languages (Python?) do
- Must be cooperative
	- Must yield to each other, otherwise one coroutine could be running forever
- Threads are run by a global scheduler, coroutines are not
	- Coroutines have to know EXPLICITLY who they're yielding to
- Coroutine stack is a byte array
- How do we implement yield?
	- swap_context(src, scheduler)
	- Scheduler can round-robin