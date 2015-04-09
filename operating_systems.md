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
- OS only takes control of the machine because of an interrupt or a system call

---
## 2/9/15

### F-D-E with Exceptions

- 60 is the well-known entry point for mem violation
- 64 is entry point for mode register violation

### Traps

- Traps force PC to a known address and sets mode to system mode
- Unlike exceptions, traps carry some arguments to the OS
- Foundation of the *system call*
- To get back to user mode, most machines have a *return from exception* instruction
	- sets PC to PC'
	- sets mode bit to user mode
- Traps and exceptions use the same mechanism

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

---

## 2/12/15

## OS Architecture

- Refers to the segment register and the offset register as a *pair*
- There is a **thread/interrupt gate**, size 2 words, which access a segment register table(?)
- The selector is an index into a segment descriptor, described as **0900**
- In your address space, your stack frame (in xv6) is a fixed width,our heap starst after that and grows as necessary
- Given two processes *p1* and *p2*, and their respective address spaces in physical memory, there is a block of memory at the end of physical memory reserved for I/O
	- this is not actually physical memory
- Program 0 in address space is the *kernel*
	- This consists of the kernel code, above the kernal data
- Every time you have a system call you have to change the address space to the one where the handler resides
	- Every time it does this, the processor has to translate from virtual to physical space, which is costly
- To avoid this, we duplicate the kernal code/data into each process table, to avoid reloading information into the caches (pollution)
- Think of the kernel as a multithreaded program, with a different thread for each process
- The kernel stack of any process is in every process

---

## 2/19/15

## Interrupts

	main () {
	.
	.
	.
	initializeIDT();
	
	for (;;) {
		schedule();
	}

	divide_by_zero_handler() {
		push ds;
		push es;
		push d;
		call c_handler_divider()
		allooooiio
	}
	
	trap_handle() {
		push things;
		call c_trap_handler
		pop things;
		iret; // interrupt return 
	}
	
	c_trap_handler(a) {
		int *a;
		switchc(*(a + TRAP_ID_OFF))
			0: div_by_zero_handler
			1: illegal_arg_handler()
	}
	
	catch_divzero()(
	j
	}
	
	initialize(IDT) {
		
	}	
	
	vector0() {
		push 0
		call handler();
		
	}
	vector 1()
	push 1;
	l h
	
- Processor encounters many impossible conditions in its pipeline, and it jumps to particular interrupts
- Difference between exceptions encountered in the code and interrupts encountered from external devices

---

## 2/24/15

## Process

- System abstraction - the set of resources required for executing a program
	- Execution context
	- Address space
	- Linker
	- File handles, comm endpoints, etc.
- Historically, all of the above lumped into a single abstraction
- More recently, split into several abstractions
	- Threads, address spaces, protection domain
- OS process management
	- Supports creation of processes and interprocess communication
- Code for system calls are in the *kernel*
	- This is because of privileges restricted to kernel space
- **Process:** an abstraction to handle programs
- created by the OS
	- e.g. your shell
	
#### OS Process Management

- Supports creation of process and interprocess communication (IPC)
- Allocates resources to processes according to specific policies
- Interleaves the execution of multiple processes to increase system utilization

## Threads

- Thread of execution: stack + registers (including PC)
- Informally: where an execution stream is currently at in the program and the method invocation chain that brought the exectution stream to the current place

### Multi-Threading

- Each thread is described by a *thread-control block* (TCB)
- Typically contains
	- Thread ID
	Space for saving registers
	Pointer to thread-specific data not on stack
- Threads share process address space
	- *No memory protection*
	- Can write into each other's stack
	
---

### Recitation

#### Traps

- Modify eip in trap frame.

### How to Implement Signal Call

- Use `grep` in source code dir for something like uptime or halt
	- katsac code: sys_uptime
	- YOU MUST PUT THE NAME OF THE SHIT YOU WANT TO DO IN THE .H FILES TO FUCKING USE THEM.
	- Anytime you add a thing to xv6 commands make sure you add the name of it to the right files
- System calls don't get args passed to the stack they get put in the registers.
- Use `arg int`to get everything make sure you can print out the arguments.

---
## 3/10/15
=]

---
## 4/2/15

# Memory Management Subsystem

- Requirements for memory management:
	- Consistency
	- Relocation
	- Allowed processes to share memory

## Memory Partitioning

- Static: process must be loaded into partition of equal or greater size -> Internal Fragmentation
- Dynamic: each process loaded into partition of exact size -> External Fragmentation

### 2 Ways of Managing Memory

- **Paging**: memory divided into equal-sized frames. All process pages loaded into non-necessarily contiguous frames
- Modern OS pages are 4096 bytes, 4KB
- Addressing modes and issues are resolved with the **page table**
- **Segmentation:** memory placed into variable blocks
- All machines today are 64-bit machines
	- That means they can address $$$2^{64}$$$
		- That is 1 Giga Gigabytes!!
	- However, realistically, we only have 4-16GB of physical memory available to us.
	- How does we fit 64-bit programs onto such a smaller amount of memory?
	- OS uses **virtual memory** to abstractly squeeze 64 bits of virtual memory onto physical memory

## Virtual Memory

- Usually implemented with paging, sometimes segmentation
- **Demand paging**: loading pages into physical memory only when needed
- **Principle of locality of references:** memory references within a process tend to cluster
- As a result, only a few pieces of a process will be needed over a short period of time
- As a result, only a few pieces of a process will be needed over a period of time
- Possible to make intelligent guesses about which pieces will be needed
- Each page is a *cacheable* unit of virtual memory

### Hardware Translation

- Translation from virtual to physical can be done in software
- However, hardware support is needed to ensure protection and perform translation faster
- Simplest solution with two registers: base and size

### Segmentation Hardware

- Segments are of variable size
- Translation done through a set of (base, size, state) tuples - segment table indexed by segment number
- **Segment Table:** stores mapping of segment # + offset to physical address
- **State:** valid/invalid, access permissions, reference, modified bits (dirty bit)
	- Dirty bit is used when flushing page from physical memory
	- If segment has not been modified, don't have to write back to disk (saves time)

### Paging Hardware

- Fixed size
- Physical memory corresponds to a page called **page frame**
- Translation done through a page table indexed by page number
- Since each page has 4096, or $$$2^{12}$$$ mappable addresses, the lower 12 bits in VM are used to map the offset within a page
- The rest of the 52 bits are available mappings for any page
- **State:** valid/invalid, access permission, reference, modified bits
- Validity of a state denotes whether or not the contents of that page have been evicted to disk
- Paging is transparent [opaque?] to the programmer

### Paging

- Each page table entry contains a **present bit** to indicate whether the page is in main memory or not.
	- If it is in main memory, the entry contains the frame number of the corresponding page in main memory
	- If it is not in main memory, the entry may contain the address of that page on disk
	- First entry of page table stored in control register 3 **cr3** 
	
![Page frame](file:///Users/patrickwu/Documents/Classwork/Operating Systems/Page Frame.svg =150x "Title")
	
### Translation Lookaside Buffers

- Translation on every memory access must be *fast*
- What to do? Caching
	- Why does caching work? Temporal locality
- Translation lookaside buffer is a cache of virtual to physical mappings
- What if TLB misses?
	- Evict existing entry if none are free
		- Replacement policy ranges from pseudo-LRU to random
	- Bring in missing entry from PT

### Sharing Pages

- If we share the same code among different users, it is sufficient to keep one copy in main memory
- Shared code must be reentrant (not self-modifying)
- Something something cows (copy-on-write)

### Multilevel Page Tables

- Organize page tables into a multilevel hierarchy
	- When two levels are used, the page number is split into two numbers $$$p_1$$$ and $$$p_2$$$

### VM Mapping

- Goal is to assign active virtual pages to different cache-pages
- Mapping is optimal if it avoids conflict misses
- Mapping assigns two or more active pages to the same cache-page can induce cache conflict misses

---
## 4/7/15

### How to Deal with VM > PM

### Demand Paging

- To start a process, the OS first loads the whole address space
- As process references memory, bring in as necessary

### Page Fault

- What happens when process references a page marked as invalid in the page table?
	- Triggers hardware **page fault** exception
- Restart instruction of that execution (requires hardware support)

#### Cost of Page Fault Exception

- Exceptions, checking page table handler, finding free memory frame all take about 200-600$$$\mathrm{\mu}$$$s
- Disk seek and read ~10ms
- Memory access ~100ns
- Page dault degrades performance by ~$$$10^5$$$!
	- Too many page faults results in crashes
- We want no more than 10% page degradation

## Fetch Policy

- **Demand paging**: Brings pages into main memory when needed
- **Prepaging:** Brings in more pages than needed

## Page Replacement

- What if there's no frame left on a page fault
	- Free a frame currently being used (victim page)
 	- Write it to disk
	- Change page table
	- Read desired page into freed frame
	
### Replacement Policy

- Deals with selection of a page in memory to be replaced
- Not all pages can be selected for replacement
	- Some are 'pinned' to physical memory
	- These frames are locked
		- E.g. the pages containing page fault handler, device drivers, etc.
- Decision for the set of pages to be considered for replacement is related to the **resident set management strategy:**
	- How many page frames to be allocated to each process?
- No matter what the set of pages considered for replacement
- **Optimal Policy:** selects for replacement page for which the time to next reference is long
	- Produces fewest page replacements
	- 3 kinds that try to optimize policy:
		1. LRU
		2. FIFO
		3. Clock policy
- Optimal policy entails knowing what pages are used in the future (which is impossible)
- Although LRU is conceptually simple, it is difficult to implement in hardware, because timestamps are difficult to use in hardware
- FIFO can be treated as a circular buffer, with a pointer to the beginning of the buffer
	- Not effective because it doesn't recognize frequency of references
	
### Clock Policy: 

- Combines the depth of LRU with the simplicity of design of FIFO
- the set of frames candidate for replacement is considered as a circular buffer
- When a page is replaced, a victim pointer is set to point to the next frame in the buffer
- A dirty bit for each frame is set to 1 whenever:
	- A page is first loaded into the frame
	- The corresponding page is referenced
- When it is time to replace a page, the first frame encountered with the used bit set to 0 is replaced.
	- During the search for replacement, each dirty bit is reset to 0
	
## Page Buffering

- Pages to be replaced are kept in main memory for a while to guard against poorly performing replcement algorithms such as FIFO
- Two lists of pointers: each entry points to a frame selected for replacement
	1. Free page list
	2. Modified page list
- At each page fault, two lists are first examined to see if the needed page is still in main memory

### Cleaning Policy

- When should modified page be written out to disk?
- **Demand cleaning:** written out only when its frame has been selected for replacement
- **Precleaning:** modified pages are written before their frame are needed so that they can be written out in batches

## Multi-Programming Environment


### Thrashing

- Thrasing occurs when the # of processors exceed the CPU utilization capacity
	- $$$\sum$$$ size of working sets > total memory size

### Support for Multiple Processes

- More than one address space should be loaded in memory
- A register points to current page table
- Look at TLB
- Caches
	- Physical addresses: no problem
	- Virtual addresses: ____
- OS must decided how many page frames to allocate to a process

### Resident Set Size

- **Fixed-Allocation Policy:** allocates a fixed number of frames that remains constant over time
	- Determined at load time, based on type of application
- **Variable-Allocation Policy:** # of frames allocated to a process may vary over time
	- OS has to constantly monitor applications to see if they are memory-hungry
	
### Replacement Scope

#### Fixed Allocation + Local Scope

- Each process is allocated a fixed number of pages
- difficult to determine ahead of time a good # of frames to allocate
	- Too low = high page fault rate
	- Too high = low multiprocessor
	
####  Variable Allocation + Global Scope

- Simple to implement -- adopted by many OS (like Unix SVr4)
- Global list of free frames
	- Wen a process issues a page fault, a free frame (from the list is allocated to it
	- Becomes difficult 
	- Alleviated by page buffer
	
#### Variable Allocation + Local scope

- Best suited for ideal implementation