# sample-make

A possible directory organization, complete with simple hello-world.
This example uses recursive Makefiles, and (at this point) leaves the objects next to the source.
Still, it shows the idea of using libraries to decouple us from vendor implementations

To build the comm demo:

    ``$ make``

This should create src/scheduler and src/udp_client

To run the comm demo:

In a terminal:

    ``$ src/scheduler``

Asterix's should start to appear every second. If you type into the terminal
your input should be echoed.

In a second terminal:

    ``$ src/udp_client``

This should connect to the other terminal. Now if you type into the terminal
you should also see your input echoed back.




