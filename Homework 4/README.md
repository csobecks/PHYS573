## Homework 4

The generator I have created is a combined generator that uses the LCG Modulo 2^64, 64-bit Xorshift, and MLCG with m>>2^32,m Prime methods. The period of this generator has the period of the lowest generator. In this case this would be the MLCG with m>>2^32,m Prime generator, with a period of m-1. For the numbers I'm using, this comes out to be 2^42 - 22. 

The physics application of my random number generator is