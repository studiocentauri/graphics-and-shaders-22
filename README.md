# graphics-and-shaders-22
Repository for the graphics and shaders project for Summer 2022.
## Tasks for Week-2
- [x] Modify input detection so that pressing R key rotates the triangle with time
- [ ] Color Cycle in triangle :
  - [ ] Draw a triangle with three different colors at its corners (loaded via color vertex data).
  - [ ] Define a time period for a complete cycle 'T' and time in the current cycle 't'.
  - [ ] Load all the variables as uniforms to the shader
  - [ ] Linearly interpolate between the colors based on current time.
  - [ ] The end result should be something like if V1,V2,V3 are the vertices and C1,C2,C3 are the colors:
    - At t=0, (V1,C1),(V2,C2),(V3,C3)
    - At t=T/3, (V1,C3),(V2,C1),(V3,C2)
    - At t=2T/3, (V1,C2),(V2,C3),(V3,C1)
    - At t=T, (V1,C1),(V2,C2),(V3,C3)
- [x] ShaderToy : 
  - [x] Make a checkers board in shadertoy
  - [x] Make shadertoy program which displays the graph of any equation f(x,y) = 0.
- [ ] Texture : 
  - [ ] Load a image of your choice and render it on the triangle.
  - [ ] Rotate the texture by 90 degrees clockwise.
- [x] UI : 
  - [x] Make a new UI window.
  - [x] Make two check box variables 'Draw Triangle' and 'Draw Rectangle', checking either of which draws that respective shape.
  - [x] Provide a means to change texture of rectangle at runtime.
  - [x] Make another checkbox for showing/hiding frame rate in that window.
  - [x] Make one more checkbox for VSync.
### Deadline : 16th June, 2022 11:59pm
### Instructions for submissions:
- Fork this repo if you have not already.
- Clone YOUR forked repo to your local machine.
- Checkout to the Week-2 branch.
- Finish tasks given above and commit.
- Push the commits to the Week-2 branch of YOUR origin
- Send a PR to the Week-2 branch of upstream before the deadline. (upstream is the original repo)
