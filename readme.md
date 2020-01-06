## Overview
TMA4 requires you to write THREE C++ programs using the information you have studied in Units 13-16.

## C++ Programs
1. Write a program that creates a class hierarchy for simple geometry.

   1. Start with a `Point` class to hold x and y values of a point. Overload the `<<` operator to print point values, and the `+` and `–` operators to add and subtract point coordinates (Hint: keep x and y separate in the calculation).

   2. Create a pure abstract base class `Shape`, which will form the basis of your shapes. The `Shape` class will contain abstract functions to calculate area and circumference of the shape, plus provide the coordinates (Points) of a rectangle that encloses the shape (*a bounding box*). These will be overloaded by the derived classes. Create a `display()` function that will display the name of the class, and all stored information about the class (including area, circumference, and bounding box).

   3. Build the hierarchy by creating the `Shape` classes `Circle`, `Square`, and `Triangle`. For these derived classes, create default constructors, and constructors whose arguments can initialize the shapes appropriately using the correct number of `Point` objects (i.e., `Circle` requires a `Point` center and a radius, `Square` requires four `Point` vertices, while `Triangle` requires three `Point` vertices).

   4. In `main()`, create one instance each of the following: Circle (10, -5) with a radius of 23; Square (5, -5)(-10,7)(4,23)(-6,12); and Triangle(0,0)(10,10)(-15,15). Display the information from each object.

2. Create an inheritance hierarchy of `Rodent`: `Mouse`, `Gerbil`, `Hamster`, etc. In the base class, provide methods that are common to all `Rodents`, and refine these in the derived classes to perform different behaviours depending on the specific type of `Rodent`. Rodent must be created as a pure abstract base class. Create an array of pointers (10) to `Rodent`, and fill it with different specific types of `Rodents`. Call your base class methods, and display the results.

3. Using the Standard C++ Library `vector` as an underlying implementation, create a `Set` template class that accepts only one of each type of object that you put into it. Make a nested `iterator` class that supports the “end sentinel” concept in Unit 16. Write test code for your `Set` in `main()`, using both your `Set` template class and the Standard C++ Library `set` template to verify that the behaviour is correct.

## Deliverables
The deliverables for this TMA are as per the TMA Requirements document.

All deliverables must be zipped into one file. You can upload the file via Moodle, or email the file directly to your tutor.