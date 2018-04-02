# HW5 - Collision Demo

## About

This program uses regular polygons as the objects that collide with each other. Polygon vertices are constructed by taking a radius and rotating it the correct amount around a point.

Collisions are handled using the provided SAT collision detection code. When two objects collide, their velocity vectors are reflected across the penetration vector in order to simulate bouncing physics. The implementation of this isn't perfect, but is not the main focus of this assignment.

Collisions with walls are handled by simulating a one-dimensional rectangle aligned with the edges of the screen. In this case, the reflection vector can be hardcoded since an objects reflection when colliding with a wall is always the same.