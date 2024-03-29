#include <ebb/node.hpp>
#include <ebb/window.hpp>
#include <ebb/renderer.hpp>
#include <ebb/mesh/renderer.hpp>
#include <ebb/transform.hpp>
#include <stdio.h>
#include <ebb/math.hpp>

/**
 * Showcase movement over time. TODO: deltaTime and other timing stuff
*/
class Rotate : public Ebb::Node {
public:
    using Ebb::Node::Node;

    void update() override {
        object->rotateY(0.01);
    }

    Ebb::Transform *object;

private:
};

using Node = Ebb::Node;
int main(int argc, char **argv) {
    Ebb::Window::setup();
    Node *root = new Node;
    Ebb::NodeTreeManager manager(root);
    Ebb::Renderer *renderer = new Ebb::Renderer(root, new Ebb::Window(800,600, "Test window"));
    manager.addManager(renderer);
    
    Ebb::Transform *mesh = new Ebb::Transform(root);
    Rotate *r = new Rotate(mesh);
    r->object = mesh;
    mesh->translate(Ebb::Math::vec3(0.0f, 0.0f, -2.0f));
    Ebb::MeshRenderer *meshRender = new Ebb::MeshRenderer(mesh, Ebb::Mesh::loadOBJ("models/monke.obj"));
    
    manager.run();

    Ebb::Window::teardown();
    return 0;
}