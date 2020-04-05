# CS441/541 Synchronization Project

## Author(s):

TODO


## Date:

TODO


## Description:

TODO


## How to build the software

TODO


## How to use the software

TODO


## How the software was tested

TODO


## Known bugs and problem areas

TODO

## Special section: Before coding

1) 
  a) If a car A arrives from the North followed by a car B arriving from the South, and both A and B
  	 intend to go straight, B will wait for A to go even though they could both proceed at the same time.

  b) The deadlock problem occurs when two or more cars reach the intersection at the same time.
  	 Th will then end up waiting for each other to go and no one will make progress.

2) 
  a) The bridge could be full on the north side while a car is waiting to get on the bridge
  	Worst case: more cars are waiting on the cars waiting to cross the bridge

  b) The cars could be stuck on the bridge waiting for for the intersections to be clear
  	Worst case: the bridge fills up while waiting

  c) An intersection could fill up while waiting to get on the bridge
  	Worst case: both intersctions are filled up and no progress gets made on either side

  d) There might be some desire to give those on the bridge priority since it can only hold
  	 N number of cars at any one time which could cause starvation in the intersections
  	Worst case: The cars in the intersection don't get to go because the cars from the bridge 
  				take priority