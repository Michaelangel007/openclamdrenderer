This is an implementation of a deferred 3D renderer written in C++, with SFML for context creation, OpenGL for grabbing screen buffers, and OpenCL for doing all the 3D lifting

While using OpenCL for doing 3D rasterised graphics is a tad somewhat completely stupid, its panned out much better than expected. 3D is handled as tait-bryan rotations rather than matrix multiplication with homogeneous coordinates for simplicity

There is support for: Textures with mipmapping, deferred lighting (no specular, but not hard to implement), static generated shadows, poor/broken ambient occlusion, multiple movable/rotatable objects and a few other things I've probably forgotten

Performance in the sponza atrium (400k tris) is 6.7ms/frame at 1280x768, and 13.5ms/frame at 1680x1050. This benchmarked on an hd7970 (cpu is completely irrelevant), for two dynamic lights with statically (ie once only) calculated shadows. Soft shadows currently add 1ms, and 2ms respectively

Also included is the beginnings of a space game under /game

Source code is a bit of mess as well due to being written with functionality in mind, not cleanliness

If you want to compile it, you'll need boost (boost::compute depends on it), opencl, sfml 2, and boost::compute (not officially a boost library)

The code has officially moved to https://github.com/20k/OpenCLRenderer due to the complete lack of support for google code.