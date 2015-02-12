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
	
---
## 2/3/15

### Major Issues in OS Design

- Performance
- Reliability
- Persistence: how can we make data last beyond program execution?
- Accounting: how to keep track of resource usage
- Distribution
- Scaling: how do we keep OS efficient and reliable as the offered load increases
- Security

### Architecture Refresher

- Single-CPU chip computer
- Single-threaded
- Multithreaded
- Multi/many-core

[!insert picture from slides]

### Memory Hierarchy

CPU (word transfer)$$$\to$$$ cache (block transfer)$$$\to$$$ main memory (page transfer)$$$\to$$$ disk

- As you go right, you:
	- Decrease cost/bit
	- Increase capacity
	- Increase access time
	- Increase size of transfer unit
	- Decrease frequency of access
	
### Hardware Caches

- Motivated by the mismatch b/w processor and memory speed
- Closer to the processor than main memory
- Smaller and faster than main memory
- Act as "attraction memory": contains value of main memory (temporal locality)
- Transfer between caches and main memory is performed in units called cache blocks/lines
- Spatial locality
- Associative caches trade shorter lookup for collisions
- Write-throughs/write-backs
- Write-backs don't go to memory
- Cache lines become *dirty* when you have to write through the entire line back to memory
- Replacement algorithm: direct or LRU
- Each core in a CPU has its own L1 cache
- **Snooping Caches:** snoop for activity in a cache line, sees what information it can access
	- Invalidates writes, grabs reads(?)

### Multi-CPU-chip Multiprocessors

- Simple scheme (SMP): more than one CPU on the same bus
- Memory is shared among CPUs - cache coherence between LLCs
- Problems with locality
- Thread migration vs. page migration
- Page replication
- Affinity scheduling

### Fetch-Decode-Execute

- Computer is a large, general-purpose calculator
- Fetches instructions, decodes them, and executes them

### Processor Modes

- System mode is privileged mode
- User mode is unprivileged
- Certain instructions can only be executed in system mode
- Special registers holds which mode the CPU is in
- OS is in charge of changing modes

#### Simple Protection Scheme

- Addresses < 100 are reserved for OS use
- Mode register provided
	- 0 = SYS = system mode
	- 1 = USR = CPU is executing in user mode
- Hardware does this check
	- On every fetch, if the mode bit is USR and the address is less than 100, do not execute in OS mode
	
---

## Signals

- Asynchronous interprocess communication

		sighandler_t signal(int signum, sighandler_t handler
- Called using a wrapper function
- Example of indirection

---

2/6/15

## Stack Frame

- Built into the hardware
- Program counter is pushed on the stack whenever a function is called
- base pointer points to the old bp when you pop it
- This gives you a *dynamic chain* of calls
- Stack frame = activation record

# Cor$$$\mathbb{DAMN YOU ALISON}$$$outines

- swap context uses ucontext
- These are used to modify user threads
- First time you create a thread, create 2
	- One for main and a new thread
- OS only tkaes control of the machine because of an interrupt or a system call

---
## 2/9/15

### F-D-E with Exceptions

- 60 is the well-known entry point for mem violation
- 64 is entry point for mode register violation

### Traps

- Traps force PC to a known address and sets mode to system mode
- Unlike exceptions, trps carry some arguments to the OS
- Foundation of the *system call*
- To get back to user mode, most machines have a *return from exception* instruction
	- sets PC to PC'
	- sets mode bit to user mode
- Traps and excpetions use the same mechanism

### Interrupts

- How can we force CPU back into system mode if the user program is off computing something/
	- Solution: Interrupts
- Interupt is an external event that causes the CPU to jump to a known address
- Link and interrupt to a periodic clock
- Modify FDE loop to check an external line set periodically by the clock
- Keyboard presses are interrupts (?)
- Problem arises when the interrupt is received while the process is handling some process that cannot be interrupted (i.e. data structures will be destroyed)

### Entry Points

- What are the "entry points" for our example machine?
	- 60: memory access violation
	- 64: entry point for mode register 
	- 68: user initiated trap
	- 72: 

### Program I/O (PIO)
	
### Direct Memory Acces (DMA)

- PIO is a direct check against status register, then send or receive
- DMA must set up base count, check status

### Booting