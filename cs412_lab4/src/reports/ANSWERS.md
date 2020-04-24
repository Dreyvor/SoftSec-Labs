1) Why did you need to change `is_png_chunk_valid`?

	PNG format uses a kind of checksum called the CRC. We modified the function to avoid the reconstruction of the CRC by the fuzzer. In fact we are able to do that, but it will take more time. Thus we modified this function to tell the code that our inputs are always in a good format without the constraint of the CRC.

2) Why did we give you exactly TWO seeds for fuzzing?
		
	We have two ways to store images. The first one is the same way as lab 1 (i.e. output of checkerboard) that uses a colormap (i.e. store the two colors and then select one of them). The second one is the "classical" one (i.e encode each pixel with an RGBA value). The second takes more space to be stored. The reader can verified this structure using `file palette.png` and `file rgba.png`
	
3) Why did you have to use `afl-gcc` to compile the source (and not e.g. ordinary gcc)?
	
	The main goal is to take as many different paths as possible. Afl-gcc will instruments jumps in the binary to help the fuzzer. We don't to do blackbox fuzzing. This makes the fuzzer work more efficient.

4) How many crashes in total did AFL produce? How many unique crashes?
	
	It produces 42 unique crashes with about 2M crashes.

5) Why are hangs counted as bugs in AFL? Which type of attack can they be used for?

	Hangs suspends the execution of the program and make it terminate after an arbitrary or indefinitely long time. Usually this is not a normal behaviour, then this is considered as a bug. This can be used by an attacker to perform DOS attack.

6) Which interface of `libpngparser` remains untested by AFL (take a look at `pngparser.h`)?

	The `store_png` is not tested by `size.c`

7) In lab0x01 many students encountered a crash in `load_png` when the input file with the specified name didn't exist. Can AFL find that bug in this setup?

	No. The fuzzer is interested in build "buggy" input images and give them to the program. Its goal is not to build erroneous file names and try to crash the execution.

8) How long did you run AFL for? If you run it for twice as long, do you expect to find twice as many bugs? Why?

	I ran for about 10 minutes. If I run for twice long it won't find twice as many bugs because the bugs will be more complex than the ones already found. The paths will be more complex to find bugs.
