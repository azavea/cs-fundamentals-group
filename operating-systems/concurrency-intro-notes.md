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

## Homework Questions

[Homework Program README.md](https://github.com/remzi-arpacidusseau/ostep-homework/tree/master/threads-intro)

### Notes
