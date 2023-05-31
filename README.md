# graphics-and-shaders-22
Repository for the graphics and shaders project for Summer 2022.
## Tasks for Week-1

| Final | Final |
| --- | --- |
|![image](https://github.com/npxx/graphics-and-shaders-22/assets/96121824/0353c8b3-fb43-4e16-af1a-b21a97c073c7)|![image](https://github.com/npxx/graphics-and-shaders-22/assets/96121824/7ce7574d-0b1a-4740-bdf3-011893ceedeb)|

- [x] Modify GLFW window flags for the following features:
  - [x] Application starts in fullscreen mode
  - **`GLFW_MAXIMIZED` Window Hint**
  - [x] Fixed Aspect Ration on resizing window
  - **`glfwSetWindowAspectRatio(..)`**
  - [x] Minimum and Maximum resolution
  - **`glfwSetWindowSizeLimits(..)`**
 
- [x] Modify input detection so that:
  - [x] Pressing R varies red value of background colour with time
  - [x] Pressing G varies green value of background colour with time
  - [x] Pressing B varies blue value of background colour with time.
  - **Added switch case to handle input and implemented sine variation of color channel with time**

- [x] Draw two triangles with only one common vertex using two different vertex array. Also make the second triangle a different color.
- **Created two vertex data arrays, also a new shader for coloring the triangles differently**

### Deadline : 6th June, 2022 11:59pm
### Instructions for submissions:
- Fork this repo if you have not already.
- Clone YOUR forked repo to your local machine.
- Checkout to the Week-1 branch.
- Finish tasks given above and commit.
- Push the commits to the Week-1 branch of YOUR origin
- Send a PR to the Week-1 branch of upstream before the deadline. (upstream is the original repo)
