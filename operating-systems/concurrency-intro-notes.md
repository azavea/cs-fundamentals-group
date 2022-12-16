## Resource

**Subject:** Operating Systems \
**Resource:** [Operating Systems: Three Easy Pieces](https://pages.cs.wisc.edu/~remzi/OSTEP/)

## Weekly Reading

[Concurrency: Threads Intro](https://pages.cs.wisc.edu/~remzi/OSTEP/threads-intro.pdf)

### Notes

**Backgound Notes**

Reading TL;DR:

thread = single running process EXCEPT they share the same address space and can access the same data
	- Memories of node: how does this relate to workers or child processes and which can share global variables?
a progam can be multi-threaded! 

state of a single thread similar to process:
	- program counter that tracks where the programs is fetching instructions from
	- private set of registers used for computation
	- thread control block (to save state, like when context switching between threads)

the address space diagram on page 2 is nice!!

why use theads at all?
- parallelism! instead of single-threaded program can use multiple cpu's (parallelization) and use a thread per cpu to make it faster
- avoid blocking program progress due ot slow i/o. CPU scheduler can switch to other threads to do something useful
	- why not use multiple processes instead of multiple threads? Because threads are processes that share address space! So make sense if sharing data

oh my threads! Like a function except it runs independently of the caller so depending on the OS scheduler it could just return...whenever!

race condition (or data race): the results depend on the timing execution of the code!!
- context switches that occur at untimely points in the execution = wrong result
- we expect detministic compution but the result is indeterminite

If multiple threads are executing code and it results in a race condition, the code is called "critical section". A critical section is code that has a shared variable ot resource that must only be executed by one thread ----> we want "mutual exclusion", iet if one thread is executing within the critical section, the others will be prevented from doing so

 :point_up: all in all atomic operations are important for this reason!

**Discussion Notes**

- There's less learning from scratch for us here and more "putting a face to name"
	- We've bumped into some of this terminology before in the context of our work but cool to see this at the programming/os level
		- ex: this came up in bha echo (diagnosing race condition)
		- not 2 processes trying to access the same data but that one data relied on an edit to another piece of data -- has implications beyond just "grabbing same slice of data"
		- ex: also in fieldscope which is almost entirely controlled by their data so makes sense that could cause issues there with race conditions
	- workers conceptually familiar also—how does it relate to the contexts we know them in? e.g. celery workers and node child processes?
		- celery workers example: a big analysis needs to happen so a worker takes a chunk of it to reduce one big non-performant action. Processes needed to be locked so that it doesn't start taking chunks out of other in-process data (familiar to atomoic transactions at the os level)
		- a deeper discussion dive into celery 
			- is the conductor for batch geocoding / processing
- how is mutual exclusion enforced?
	- sounds like there's some hardware support here

## Homework Questions

[Homework Program README.md](https://github.com/remzi-arpacidusseau/ostep-homework/tree/master/threads-intro)

### Notes

Ran out of time, skipped homework questions 
