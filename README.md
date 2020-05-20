# CS441/541 Synchronization Project

## Author(s):

Zach Dummer


## Date:

04/11/2020


## Description:

This program is a simulation of a four way intersection, which uses threading and syncronization
to eliminate deadlock and make traffic as effective as possible.


## How to build the software

Navigate to the directory with the makefile
Type "make"
hit Enter


## How to use the software

Type "./stoplight" followed by 2 arguments
- <integer>(greater than zero) : The time the program should run for
- <integer>(greater than zero) : The number of cars in the simulation


## How the software was tested

To test this software I started with only one or 2 cars running for a small amount of time and gradually went
larger and large to make sure there was no deadlock.


## Known bugs and problem areas

There are no know bugs at his time.

If you find a bug please raise the issue @ https://bitbucket.org/zdummer/cs441-intersection/src/master/

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

## Special section: After coding

1) My solution to this problem was to make a mutex for the individual sections of the intersection
    which can only have one car in them at a time. I also added a semaphore for each approaching direction to ensure that the first car to get to the line from a certain direction would be the first car to go. If there was already a car there they would wait in line. Lastly I made sure to add a mutx to only allow 3 cars to enter the intersection at a time.

2) 
  a) I avoided deadlock by have each car only make progress one subsection at a time rather than waiting
      for the entire lane to be clear to make their way through the intersection, as well as allowing
      only 3 cars in the intersection at a time to make sure there would always be a space to move.

  b) I prevented accidents by requiring each car to acquire the mutex before entering the next section as well as getting to the next section before releasing the mutex

  c) I improved taffic flow by allowing cars to enter the intersection even if the intersection isn't clear

  d) The first car to get to the line aquires a mutex to make sure it goes through the intersection first.

  e) Any car has an equal chance of getting into the next area

  f) Nothing has priotity so nothing gets starved out