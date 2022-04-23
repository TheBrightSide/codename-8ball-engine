# Welcome to the **Engine I Have No Name For** (codenamed: 8ball-engine)


## Overview
- This engine does not do anything new and fancy except trying to incorporate memory safety as much as possible, whilst maintaining performance (by utilizing the usage of smart pointers, mainly **std::weak_ptr** and **std::shared_ptr**)
- For now this engine is only capable of rendering 2D and doesn't have a scene system nor a camera system
- The engine is based on the Entity Component System and it is mainly controlled via the GameManager.cpp and the components folder
- You can add more IO functionality in the util folder (audio, scripting, textures, windows, gui, etc), there is already a bunch of functionality implemented there - Window initializing (with **SDL2**), gui (with **Dear ImGui**), Texture loading and rendering (with **SDL2**).
- For rendering this engine uses SDL2 because of its cross-platform abilities and support of multiple rendering backends such as Vulkan, OpenGL and Direct3D.

## Building/Compiling
- On Windows you would have to install MSYS2 with configured SDL2 and SDL2_image in it (ImGui is already integrated in the engine, check `src/util/imgui`)
- On GNU+Linux/Unix you would only have to set up your compilers and libraries through your package manager of choice
- To compile the project you need to run the `build.py` script which would go through the whole src folder and compile everything

# Idea for a Scene System (TODO)
- the engine uses the ECS at its core so a scene could be an array of entities with components inside in the format of JSON
<p>Example:</p>

```json
[
    {
        "components": {
            "TransformComponent2D": {
                "Position": [1.2, 2.4],
                "Rotation": [],
                "Scale": []
            },
            "SpriteComponent": {
                "SpriteImagePath": "path/to/your/image.png"
            }
            /* insert your behaviour components */
        }
    },
    {
        "components": {
            "TransformComponent2D": {
                "Position": [0, 0],
                "Rotation": [0, 0],
                "Scale": [0, 0]
            }
        }
    }
]
```
