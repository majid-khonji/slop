#include "slopstates.hpp"

SlopState::~SlopState() {
}
void SlopState::onEnter( SlopMemory& memory ) {
}
void SlopState::onExit( SlopMemory& memory ) {
}
void SlopState::update( SlopMemory& memory, double dt ) {
}
void SlopState::draw( SlopMemory& memory, glm::mat4 matrix ) {
}

// Start
void SlopStart::update( SlopMemory& memory, double dt ) {
    if ( mouse->getButton( BTN_LEFT ) ) {
        memory.setState( (SlopState*)new SlopStartDrag( mouse->getMousePos() ) );
    }
}

SlopStartDrag::SlopStartDrag( glm::vec2 point ) {
    startPoint = point;
}

void SlopStartDrag::onEnter( SlopMemory& memory ) {
    memory.rectangle->setPoints(startPoint, startPoint);
}

void SlopStartDrag::update( SlopMemory& memory, double dt ) {
    memory.rectangle->setPoints(startPoint, mouse->getMousePos());
    char a = startPoint.y > mouse->getMousePos().y;
    char b = startPoint.x > mouse->getMousePos().x;
    char c = (a << 1) | b;
    switch ( c ) {
        case 0: mouse->setCursor( "lr_angle" ); break;
        case 1: mouse->setCursor( "ll_angle" ); break;
        case 2: mouse->setCursor( "ur_angle" ); break;
        case 3: mouse->setCursor( "ul_angle" ); break;
    }
    if ( !mouse->getButton( BTN_LEFT ) ) {
        memory.setState( (SlopState*)new SlopEndDrag() );
    }
}

void SlopStartDrag::draw( SlopMemory& memory, glm::mat4 matrix ) {
    memory.rectangle->draw( matrix );
}

void SlopEndDrag::onEnter( SlopMemory& memory ) {
    memory.running = false;
}