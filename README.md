# Cpp-Bezier
Addon for nodejs to calculate rasterization of Bezier curves.

The Bezier curve algorithm was one that I learned of very early on in programming when
I was learning Java to develop Minecraft plugins. I was in a chat with a core contributor
of a server mod which was used quite extensively for creating structures quickly.

He forwarded me some reading on Bezier curves and I really enjoyed the thought of
trying to improve the algorithm to make it as efficient as possible.

![Screenshot of rasterized Bezier curve demo](test-results/bezier-rasterize-commit%3D47e0fd4.PNG)

The difficult part of rasterizing a Bezier curve is that it is drawn by a t-step
function from 0-1, so you have to make some predictions of what the initial `t` should equal, and
you must ensure that the pixels being drawn are not too far apart, as the t-step can be bigger
and smaller at different parts of the curve to be filled in.
