# ToolKit

<img align="left" width="48" height="48" src="https://github.com/afraidofdark/ToolKit/blob/master/Resources/Textures/Icons/app.png?raw=true">ToolKit is a 3d editor & interactive application development platform. It allows users to create 3d scenes and bring in the interactivity via C++ plug-ins.

## Motivation

### Simplicity

Most games, projects using Unity, UE4 or even Godot, don't need all those tools and functionalities. Having a far simple game engine, increases your comprehansion of the framework & tools, wich in return gives you more freedom to do things your way. This approach may not be suitable for professional game studios, however it is very suitable for indies whom after unique projects.

This project has a unique goal which is keeping all the source code under 30k lines of code excluding dependencies. Instead of adding more capabilites, tools and getting more complicated, ToolKit will be oriented towards simplicity, performance and being/staying modern.

### Community

Bringing like minded people together around a project outputs invaluable assets as one can observe from projects like Blender & Godot. So the project's motivation is to bring people together who after uniqueness, simplicity, modernitiy and colloborative effort to create someting exceptional.

## Editor High Lights
- All required functionalites for scene creation, manipuation, save & load.
- All required utilities for Asset management. Create / Save / Refresh / Browse resource directories.
- Support having a workspace & multiple projects.
- Multiple Prespective & Orthographic views.
- Scene outliner to observe / interact entities in the scene.
- Entity inspector & interactive resource manipulation trough the inspector.
- Import whole scenes from various programs & formats including sketchfab, blender, glb, fbx ...
- Console window along with usefull scene inspection commands and easy command creation.

## Engine High Lights

- Default fragment & vertex shaders and ability to create custom shaders for materials.
- Sprite Sheets & Sprite Animation.
- Skeletal animation & Key frame animation.
- Resource serialization & deserialization to xml format.
- Scene management.

<p align="center">
  <img width="600" height="338" src="https://github.com/afraidofdark/ToolKit/blob/master/tk_ed_21.gif?raw=true">
</p>

## Build & Run

ToolKit comes with a Visual Studio solution. The solution has been created with Visual Studio 2019 community. All the required dependencies are in the project as prebuilt for Windows 10. 

### Creating new project
- Copy the visual studio template "ToolKit\ToolKitProject.zip" to  "_%USERPROFILE%\Documents\Visual Studio 2019\Templates\ProjectTemplates_
- Restart the Visual Studio and open the solution "ToolKit\ToolKit.sln"
- In the Solution Explorer, right click the solution "ToolKit"
- Add -> New Project
- Search for ToolKitProject and select it
- Fallow the instructions, this will create a new blank project

This way allows you to build an application entierly from scrach using the ToolKit engine. Alternatively you can use the ToolKit editor to create an interactivity plugin and publish the product as a web project or executable.

### Projects in the solution

#### Engine
- *ToolKit project* is the engine it self.
- *Editor project* is the 3d editor to create conent for your projects.
- *Import project* is the executable that Editor is utilizing for importing the resources for projects.

#### Sample
- *SpaceShooter project* is a unit test project and also serving as a showcase.
- *Template project* is a Visual Studio project template. You can make your adjustments to the template and export it to use as your project template. 

## Platforms

ToolKit does not have any Windows dependency and can be build for Linux and Mac easily. However my main OS is Windows, compiling from source and publishing the created apps will be done from Windows and I don't have any plans to support other OS anytime soon.
ToolKit can pubish for:

- Windows executable
- Web html + .wasm or .js

Although it's possible, publishing to these platforms are not streamlined, still a lot of manual configuration and building is needed. Publishing for Android is on the way.

### Web Platform

This feature is not stable & in active development.
- Install emscripten, download ninja and place it in, emsdk / upstream / emscripten. 
- In the ToolKit directory, create a Build directory. 
- Enter Build. Open cmd and Run "emcmake cmake -S .."
- Than run ninja
- Install chrome
- Install chrome C/C++ DevTools Support (Dwarf)
- From the developer tools settings (wheel icon *)
- Preferences / Sources / Check: "Enable javascript source maps"
- Experiments /  Check: "WebAssembly Debugging: Enable DWARF support"
- Go to ToolKit / Bin open cmd run "emrun SpaceShooter.html --browser chrome

You can see the c++ code, call stack, local - global scope and set break points.

## Dependencies
- stb_image - MIT 
- SDL 2.0 - Zlib
- rapidxml - MIT
- openal-soft - LGPL (Dynamicyl linked)
- glm - MIT
- glew - BSD, MIT
- Dear imgui - MIT
- Assimp - BSD
- lodepng - Zlib

## Roadmap

### Renderer
- Currently I am using Opengl ES 2.0 along with Sdl. I have not isolated renderer from the underlying api. That is, renderer, texture, mesh ect ... makes direct calls to the Opengl. This isolation is needed. 
- Forward renderer. 
  - Sort objects to minimize redundant state changes.
  - Support transparency by sorting objects by depth.
  - Support double sided transparent objects.
  - Dynamic batch small objects in polygon size.
  - Utilize instantiate for bigger objects in polygon size.
  - Environment lighting trough global light probe.
  - Simple shadow maps for directional lights.
  - Allow, pick 8 lights per object.
  - Point, spot, directional light entities for the editor.

### Scene manager
 - Implement Non-uniform octree scene patitioning.
 - Implement frustum culling.
 - Update picking queries to utilze octree.

### Editor
 - Editor plugins for enhencing the editor capabilities.
 - Create sound entity for the editor.

### Engine
- Implement Entity Component System.
- Play 3d sound.
- Replace openal with  MojoAL.

### Platform
- Publish menu for Windows And Web.
- Android support.
- FireBase for mobile monetization and mobile backend.

## Final Words

Project is in active development. Feel free to play around with it and get in touch with me.

Enjoy!
