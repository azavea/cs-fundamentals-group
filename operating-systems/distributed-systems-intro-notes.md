## Resource

**Subject:** Operating Systems \
**Resource:** [Operating Systems: Three Easy Pieces](https://pages.cs.wisc.edu/~remzi/OSTEP/)

## Weekly Reading

[Persistence: Distributed Systems Intro](https://pages.cs.wisc.edu/~remzi/OSTEP/dist-intro.pdf)

### Notes

**Backgound Notes**

**Discussion Notes**

#### Dec 16, 2022
- Interuptions in communications exist? / bit flipping is weird
- Datagram = piece of data of fixed size (can be interchanged) + checksum + ? + address (to/from)
- It sounds like distributed systems don't share address space like a multi-threaded process would...but also they do share some data?
	- they have their own machine/memory but also working together as part of larger system
- What kindof data does a multi-threaded machine send back and forth?
	- 1 system with multi-threading: operating on same heap 
	- Distributed system: there's shared virtual memory (somewhere) that everyone is operating on
    - ^ So what kind of data gets sent between the i/o api in process is different than api within distributed system
- what's the purpose of message buffer? Is it the "to-go container" or the "order ticket as food goes out"?

