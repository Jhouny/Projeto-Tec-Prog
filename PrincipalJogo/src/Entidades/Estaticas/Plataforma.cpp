#include "../../../include/Entidades/Estaticas/Plataforma.h"

Plataforma::Plataforma(Coordenada tam, Coordenada pos, ID id):
    Obstaculo(tam, pos, false, false, ID::platforma) {
    shape.setFillColor(sf::Color::Magenta);
}

Plataforma::~Plataforma() { }

void Plataforma::executar() { }