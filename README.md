# circuit-gtk

## System for simulation of eletrical and digital circuits.

Description:
- This is a continuation of [this](https://github.com/Felipe-Aquino/circuit/tree/develop) one.
- Now using [gtkmm3](https://developer.gnome.org/gtkmm-tutorial/stable/) to create the user interface.
- App is, indeed, where the main elements that appears in the must be created. 
- Canvas must take care of every circuit element ( or component). So far, the only components implemented is the Wire, Voltage source and the Resistor.  
- Additional information: Press 'r' to create a resistor, 'v' to create a voltage source or 'w' to create a wire. To hide or show the grid, press 'g'. Esc is used to cancel the creation of the component. Latter, these options will be implemented in the menu. 

By now, you can not delete de component, and the simulation only prints the matrices on the terminal.

In order to make a shape for a Component, now you can read simple svg files (only with rect and circle). But don't forget to surround your svg picture with a rect or circle, this element will work as a conteiner.
To see one example of implementation just open Resistor.cpp. If you want to make a svg check the file resistor.svg and you will understand how it works.  

### Todo
- [*]  Create the capacitor component.
- [*]  Create a functional popup menu.
- [ ]  Create a better makefile.
- [ ]  Comment all the code.
- [ ]  Remove useless inherit code from the old [circuit](https://github.com/Felipe-Aquino/circuit/tree/develop) project.




### Last update: 17 May 2017  