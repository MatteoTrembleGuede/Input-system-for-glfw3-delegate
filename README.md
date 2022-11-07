# Input system for glfw3 + delegate

## Input
Meant to handle keyboard+mouse inputs or any device recognised by glfw3 as a joystick.
It contains functions that allow you to:
 - create several input instances (for example in a splitscreen game) listening to a specific device (keyboard+mouse or one controller/joystick) or any joystick.
 - bind/unbind functions to events such as key pressing/holding/releasing or to axes such as physical sticks/triggers from a controller or virtual ones mapped on one or two keys (for example walk forward/backward in a game is one virtual axis mapped on W/S)
 - change the keys assigned to actions/axes
 - save/load a set of bindings
 - etc...

example code of how to bind functions to keyboard or joystick:

![example](https://i.imgur.com/voIamq4.png)

example code of how to save/load a set of keys

![example](https://i.imgur.com/EMVjo2B.png)

example code of a key mapping menu widget (made with dear imgui)

![example](https://i.imgur.com/5bAwugl.png)

## Delegate

![example](https://i.imgur.com/PG9Be4f.png)
