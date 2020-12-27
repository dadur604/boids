# Boids  

This is my implementation of a Boids-Simulation.  
I am using [raylib](https://github.com/raysan5/raylib) as the graphics framework.

*From Wikipedia:*  
**Boids** is an artificial life program, developed by Craig Reynolds in 1986, which simulates the flocking behaviour of birds.  
  
As with most artificial life simulations, Boids is an example of emergent behavior; that is, the complexity of Boids arises from the interaction of individual agents (the boids, in this case) adhering to a set of simple rules. The rules applied in the simplest Boids world are as follows:  

* **Separation**: steer to avoid crowding local flockmates  
* **Alignment**: steer towards the average heading of local flockmates  
* **Cohesion**: steer to move towards the average position (center of mass) of local flockmates  
