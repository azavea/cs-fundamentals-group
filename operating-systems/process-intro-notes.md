## Resource

**Subject:** Operating Systems \
**Resource:** [Operating Systems: Three Easy Pieces](https://pages.cs.wisc.edu/~remzi/OSTEP/)

## Weekly Reading

[Virtualization: Process Intro](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-intro.pdf)

### Notes

**Backgound context on CPU**

CPU is comprised of:
-   **CU** (Control Unit). Regulates input and output = fetches and retrieves the instructions from main memory and later decodes them.
-   **ALU** (Artithmetic Logic Unit). Briefly touched on in nand2tetris resources. Processing, mathematic, logical operations etc.
-   **Registers**. "An extremely fast memory location. The data and instructions that are currenlty being processed during the fetch-execute cycle are stored there, for quick access by the processor." From link [here](https://www.freecodecamp.org/news/what-is-cpu-meaning-definition-and-what-cpu-stands-for/)

CPU fetches (disk --> RAM), decodes, executes, and stores. 

[Supplemental reading on CPU & memory](https://homepage.cs.uri.edu/faculty/wolfe/book/Readings/Reading04.htm)

What does "whether a CPU is available" mean: a CPU can typically perform just one action at a time. It executes one instruction at a time and it does this with with the help of physical cores. (core = CPU, a computer can have multiple cores)

**Discussion Notes**
- Noticing "API" coming up a lot....API is an abstraction that we use to describe things talking to eachother, so makes sense its a term to use outside the context of http reqeuests but that's new!
- Mechanisms vs Policies
	- mechanism are the how and policies are the which
     - an os does not exist without it policies
    - process starts because the policy and the mechanism decide it so
- Policies cont'd
	- Division between blocked and ready is up to the program, but it can't be kicked off 
	- Can't move between scheduled and deschedulde without the policy
    - Destory API - have to be able to interupt the process
	- so API triggered by mechanism and responds with a policy to initiate the process
- malloc makes an appearance! Good to know some basic C before reading this
- In summary/a little bit of future discussion on threads:
    1. program code loaded and memory allocated
    2. allocates memory by creating stack at initialization - static
    3. allocated separate memory for programs heap (can be reallocated if needed) - dynamic

## Homework Questions

[Homework Program README.md](https://github.com/remzi-arpacidusseau/ostep-homework/tree/master/cpu-intro)

### Notes

1. QUESTION: Run process-run.py with the following flags: -l 5:100,5:100.
What should the CPU utilization be (e.g., the percent of time the CPU is in use?) Why do you know this? Use the -c and -p flags to
see if you were right.
    - ANSWER: Exepected lots of CPU and we were right! (A little unsure how to understand these parameters and what they mean)
2. Now run with these flags: ./process-run.py -l 4:100,1:0. These flags specify one process with 4 instructions (all to use the CPU), and one that simply issues an I/O and waits for it to be done. How long does it take to complete both processes? Use -c and -p
to find out if you were right.
    - ANSWER: we got it right! / learning that an i/o takes time 5 to respond so CPU's run + need to call i/o through CPU be so should be CPU + i/o (i/o=5 + 2)
3. Switch the order of the processes: -l 1:0,4:100. What happens now? Does switching the order matter? Why? (As always, use -c and -p to see if you were right)
    - ANSWER: oh wow, we were wrong. We thought it would be 29 (it could've been if we passed in RUN_LATER!) but we completely forgot about concurrency - because the i/o ran first the blocking state on one process allowed the CPU to be available for process two
4. We’ll now explore some of the other flags. One important flag is -S, which determines how the system reacts when a process issues an I/O. With the flag set to SWITCH ON END, the system will NOT switch to another process while one is doing I/O, instead waiting until the process is completely finished. What happens when you run the following two processes (-l 1:0,4:100 -c -S SWITCH ON END), one doing I/O and the other doing CPU work?
    - ANSWER: Ha ha! 11! Can't fool us now! We know what we're doing now and concurrency is not involved in this one because it's blocking (scenario where the policy defines the process to wait until finish)
5. Now, run the same processes, but with the switching behavior set to switch to another process whenever one is WAITING for I/O (-l 1:0,4:100 -c -S SWITCH ON IO). What happens now? Use -c and -p to confirm that you are right.
    - ANSWER: Another one right! actually concurrent now
6. One other important behavior is what to do when an I/O completes. With -I IO RUN LATER, when an I/O completes, the process that issued it is not necessarily run right away; rather, whatever was running at the time keeps running. What happens when you run this combination of processes? (Run ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH ON IO -I IO RUN LATER -c -p) Are system resources being effectively utilized?
    - ANSWER: We flew too close to the sun. Got this one wrong thinking that the i/o processes *would* be efficient not realizing that even though the CPU process and first i/o seemed to finish at the same time, the CPU is still running and needs to complete the rest of its instructions across processes before the i/o can proceed (thanks to the RUN_LATER flag).
7. Now run the same processes, but with -I IO RUN IMMEDIATE set, which immediately runs the process that issued the I/O. How does this behavior differ? Why might running a process that just completed an I/O again be a good idea?
    - ANSWER: We now know that this answer is the one we *thought* #6 was going to run as, since the i/o will run immediately—this efficiently uses process time. 
