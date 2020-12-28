# Boids  

This is my implementation of a Boids-Simulation.  
I am using [raylib](https://github.com/raysan5/raylib) as the graphics framework, and [raygui](https://github.com/raysan5/raygui) as imgui.

*From [Wikipedia](https://en.wikipedia.org/wiki/Boids):*  
**Boids** is an artificial life program, developed by Craig Reynolds in 1986, which simulates the flocking behaviour of birds.  
  
As with most artificial life simulations, Boids is an example of emergent behavior; that is, the complexity of Boids arises from the interaction of individual agents (the boids, in this case) adhering to a set of simple rules. The rules applied in the simplest Boids world are as follows:  

* **Separation**: steer to avoid crowding local flockmates  
* **Alignment**: steer towards the average heading of local flockmates  
* **Cohesion**: steer to move towards the average position (center of mass) of local flockmates  
  
## Building  
  
**Windows:**  
Edit `build-windows.bat`, and Ensure that `VC_INIT` points to your local installation of Visual Studio's C++ build tools.  
Run `build-windows.bat` from a command prompt.  
`build-windows.bat -d` will create a debug build.  
`build-windows.bat -c` will perform a clean build.  
