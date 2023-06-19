# graphics-and-shaders-22
Repository for the graphics and shaders project for Summer 2022.

| Plain colour | Color cycle | Rotation |
| :-: | :-: | :-: |
|  ![image](https://github.com/npxx/graphics-and-shaders-22/assets/96121824/2a7a6f49-6ca0-46ea-96b5-12578085b3da)|  ![image](https://github.com/npxx/graphics-and-shaders-22/assets/96121824/0a7c9a5b-5b3b-40c8-8f53-95dee095ae2b)| ![image](https://github.com/npxx/graphics-and-shaders-22/assets/96121824/8e6d6103-e744-476b-a8a4-764c500c7c8f)|
| Triangle | Rectange | Tri + Rect |
|  ![image](https://github.com/npxx/graphics-and-shaders-22/assets/96121824/db00a9d7-e81f-41f4-9800-2fed44a2b06a)|  ![image](https://github.com/npxx/graphics-and-shaders-22/assets/96121824/b83063bd-8e03-4af5-b0bf-9afbfa9c01f0)|  ![image](https://github.com/npxx/graphics-and-shaders-22/assets/96121824/d005b013-ae37-4b0a-b264-4d37025344c5)|
|  Multi-texture  |  VSync  |   .  |
|  ![image](https://github.com/npxx/graphics-and-shaders-22/assets/96121824/16ce9f80-9a58-4dbe-b2df-aea450b3a5e8)|  ![image](https://github.com/npxx/graphics-and-shaders-22/assets/96121824/183e8f75-23b4-4a3b-8284-4dfe626c1ee8)|  .   |
| t = 0 ->T/3 | t = T/3 -> 2T/3 | t = 2T/3 -> T |
|  ![image](https://github.com/npxx/graphics-and-shaders-22/assets/96121824/b4774f7a-1666-47fb-a5c1-27901db06143)|  ![image](https://github.com/npxx/graphics-and-shaders-22/assets/96121824/333610a6-78fd-4897-8a6f-8883c141fe88)|   ![image](https://github.com/npxx/graphics-and-shaders-22/assets/96121824/33544982-f341-4b71-98b2-b1ce55e005c0)|

## Tasks for Week-2
- [x] Modify input detection so that pressing R key rotates the triangle with time
- [x] Color Cycle in triangle :
  - [x] Draw a triangle with three different colors at its corners (loaded via color vertex data).
  - [x] Define a time period for a complete cycle 'T' and time in the current cycle 't'.
  - [x] Load all the variables as uniforms to the shader
  - [x] Linearly interpolate between the colors based on current time.
  - [x] The end result should be something like if V1,V2,V3 are the vertices and C1,C2,C3 are the colors:
    - At t=0, (V1,C1),(V2,C2),(V3,C3)
    - At t=T/3, (V1,C3),(V2,C1),(V3,C2)
    - At t=2T/3, (V1,C2),(V2,C3),(V3,C1)
    - At t=T, (V1,C1),(V2,C2),(V3,C3)
- [x] ShaderToy : 
  - [x] Make a checkers board in shadertoy
  - [x] Make shadertoy program which displays the graph of any equation f(x,y) = 0.
- [x] Texture : 
  - [x] Load a image of your choice and render it on the triangle.
  - [x] Rotate the texture by 90 degrees clockwise.
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
