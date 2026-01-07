Graph Editing Software - README (phase 2)
=========================================

Overview:
---------
This C++ implementation simulates a graph editing software system that supports two types of editable visual elements: Graphs and Figures. The system is designed using object-oriented principles and implements several key design patterns, namely:

1. Factory Method (main pattern)
2. Builder Pattern (for constructing Graphs)
3. Singleton Pattern (for central factories and builders)
4. Proxy Pattern (for handling Graph rendering)
5. Flyweight Pattern (for optimizing repeated Figure instances)

Diagram Types:
--------------
- **Graphs**: Include Line and Bar Graphs.
  - Each is created using the Builder pattern.
  - Drawing is done via a Proxy, combining graphical + textual representation.
- **Figures**: Include types like Colored or Black & White figures.
  - Drawing is textual-only using stub output.
  - Flyweight pattern ensures shared figure types for memory efficiency.

Drawing Representation:
-----------------------
There are two styles of rendering elements:
- **Graphical Drawing**: Done through Proxy (for Graphs only)
- **Textual Drawing / Stubs**: Used for Figures, including via Flyweight

Design Patterns Used:
---------------------
1. **Factory Method**: 
   - Centralized in `DiagramFactory` to produce either a Graph or a Figure.
   - Delegates graph and figure creation to their respective factories.

2. **Builder Pattern** (for Graphs):
   - `Director` class orchestrates the creation process.
   - `LineBuilder` and `BarBuilder` handle individual graph creation logic.

3. **Singleton Pattern**:
   - Ensures one shared instance of:
     - `FigureFactory` (for managing Flyweight figures)
     - `BarBuilder` and `LineBuilder` (graph creators)

4. **Proxy Pattern**:
   - Applied to `Graph` drawing only.
   - Abstracts away direct drawing logic with a `DrawGraph` proxy class.

5. **Flyweight Pattern**:
   - Applied to Figures only.
   - `FlyweightFactory` shares instances of `ColoredFigure` and `BWFigure` (Black & White).
   - Coordinates are passed externally to avoid redundancy.

Structure Summary:
------------------
- `Diagram`: Base abstract class for all diagrams (Graph or Figure).
- `Graph`, `Figure`: Concrete implementations.
- `DrawProxy`, `DrawGraph`: Proxy for rendering Graphs.
- `FlyweightFigure`, `ColoredFigure`, `BWFigure`: Shared flyweight objects for textual Figures.
- `FlyweightFactory`: Caches and reuses figure types.
- `Builder`, `LineBuilder`, `BarBuilder`: Used for step-by-step Graph construction.
- `Director`: Controls the construction process.
- `GraphFactory`, `FigureFactory`: Specialized factories for each type.
- `DiagramFactory`: Central entry point used by clients.
- `main()`: Demonstrates creation of different diagram elements.

Usage:
------
Run the program and it will simulate:
- Creating and drawing a Line Graph and Bar Graph via proxy
- Creating and drawing Colored and B/W Figures using Flyweight sharing
- Output will reflect drawing operations in a textual, readable stub format

Author:
-------
This code is tailored from your design and humanized for clarity and extensibility.

