#include <iostream>
#include <string>
#include <map>
#include <memory>
using namespace std;

// Base Interface for all Diagrams
// Every diagram should be able to calculate, draw, and drag
class Diagram {
public:
    virtual void calc() = 0;
    virtual void draw() = 0;
    virtual void drag() = 0;
};

// Concrete Graph Class
// Represents a graphical diagram
class Graph : public Diagram {
public:
    void calc() override { cout << "Calculating Graph\n"; }
    void draw() override { cout << "[Graph] Drawing graphical representation.\n"; }
    void drag() override { cout << "Dragging Graph\n"; }
};

// Concrete Figure Class
// Represents a figure using textual representation
class Figure : public Diagram {
public:
    void calc() override { cout << "Calculating Figure\n"; }
    void draw() override { cout << "[Figure Stub] Drawing textual stub.\n"; }
    void drag() override { cout << "Dragging Figure\n"; }
};

// Proxy Pattern (Used for Graphs Only)
// Used to control access to the real drawing logic
class DrawProxy {
public:
    virtual void draw() = 0;
};

class DrawGraph : public DrawProxy {
public:
    void draw() override {
        cout << "[Graph Proxy] Drawing graphical + textual stub\n";
    }
};

// Flyweight Pattern (Used for Figures Only)
// Share intrinsic state (like figure type) and pass external state (like coordinates)
class FlyweightFigure {
protected:
    string type;  // type of figure e.g. circle, square
public:
    FlyweightFigure(string t) : type(t) {}
    virtual void draw() = 0;
};

// Colored flyweight figure
class ColoredFigure : public FlyweightFigure {
public:
    ColoredFigure(string t) : FlyweightFigure(t) {}
    void draw() override {
        cout << "[Colored Flyweight] Drawing colored figure of type: " << type << "\n";
    }
};

// Black & White flyweight figure
class BWFigure : public FlyweightFigure {
public:
    BWFigure(string t) : FlyweightFigure(t) {}
    void draw() override {
        cout << "[B/W Flyweight] Drawing black and white figure of type: " << type << "\n";
    }
};

// Factory to manage flyweight instances
class FlyweightFactory {
    map<string, shared_ptr<FlyweightFigure>> pool;
public:
    shared_ptr<FlyweightFigure> getFigure(string type) {
        if (pool.find(type) == pool.end()) {
            if (type.find("Color") != string::npos)
                pool[type] = make_shared<ColoredFigure>(type);
            else
                pool[type] = make_shared<BWFigure>(type);
        }
        return pool[type];
    }
};

// Builder Pattern for Graph
class Builder {
public:
    virtual void setCoord(string coord) = 0;
    virtual void calc() = 0;
    virtual void draw() = 0;
    virtual void drag() = 0;
};

// Bar Graph Builder (Singleton)
class BarBuilder : public Builder {
    string coord;
    DrawGraph proxy;
    BarBuilder() = default;  // private constructor
public:
    static BarBuilder& getInstance() {
        static BarBuilder instance;
        return instance;
    }
    void setCoord(string c) override { coord = c; }
    void calc() override { cout << "Bar calc at " << coord << "\n"; }
    void draw() override { proxy.draw(); }
    void drag() override { cout << "Drag Bar at " << coord << "\n"; }
};

// Line Graph Builder (Singleton)
class LineBuilder : public Builder {
    string coord;
    DrawGraph proxy;
    LineBuilder() = default;  // private constructor
public:
    static LineBuilder& getInstance() {
        static LineBuilder instance;
        return instance;
    }
    void setCoord(string c) override { coord = c; }
    void calc() override { cout << "Line calc at " << coord << "\n"; }
    void draw() override { proxy.draw(); }
    void drag() override { cout << "Drag Line at " << coord << "\n"; }
};

// Director orchestrates the steps of building a graph
class Director {
    Builder* builder;
public:
    void setBuilder(Builder* b) { builder = b; }
    void construct(string type, string coord) {
        builder->setCoord(coord);
        builder->calc();
        builder->draw();
        builder->drag();
    }
};

// Graph Factory (Uses Builder + Proxy)
class GraphFactory {
public:
    void createGraph(string type, string coord) {
        Director d;
        if (type == "Bar") {
            d.setBuilder(&BarBuilder::getInstance());
            d.construct(type, coord);
        } else if (type == "Line") {
            d.setBuilder(&LineBuilder::getInstance());
            d.construct(type, coord);
        }
    }
};

// Figure Factory (Uses Flyweight, Singleton)
class FigureFactory {
    FlyweightFactory flyFactory;
    FigureFactory() = default;
public:
    static FigureFactory& getInstance() {
        static FigureFactory instance;
        return instance;
    }
    shared_ptr<FlyweightFigure> getFigure(string type, string coord) {
        auto fig = flyFactory.getFigure(type);
        cout << "Coordinates: " << coord << endl;
        fig->draw();
        return fig;
    }
};

// Main Diagram Factory
class DiagramFactory {
    GraphFactory graphFactory;
public:
    void createGraph(string type, string coord) {
        graphFactory.createGraph(type, coord);
    }

    void createFigure(string type, string coord) {
        FigureFactory::getInstance().getFigure(type, coord);
    }

    void getDiagram(string element, string type, string coord) {
        if (element == "Graph") createGraph(type, coord);
        else if (element == "Figure") createFigure(type, coord);
    }
};

// Client Code
int main() {
    DiagramFactory df;

    // Demonstrate Graphs (with proxy drawing)
    df.getDiagram("Graph", "Line", "(10,20)");
    df.getDiagram("Graph", "Bar", "(15,30)");

    // Demonstrate Figures (using flyweight instances)
    df.getDiagram("Figure", "CircleColor", "(5,5)");
    df.getDiagram("Figure", "SquareBW", "(2,3)");

    return 0;
}
