#include "../../include/Estados/MaquinaEstados.h"
#include "../../include/Ente/Menus/Menu.h"
#include "../../include/Ente/Menus/MenuTransicao.h"
#include "../../include/Ente/Menus/MenuPausa.h"
#include "../../include/Ente/Menus/MenuGameOver.h"
#include "../../include/Ente/Menus/Fases/Netuno.h"
#include "../../include/Ente/Menus/Fases/Mercurio.h"
#include "../../include/Ente/Menus/Fases/Fase.h"

namespace Estados {
    MaquinaEstados::MaquinaEstados():
        estadoAtual(NULL),
        mapaEstados(),
        tempo()
    {

    }

    MaquinaEstados::~MaquinaEstados() {
        mapaEstados.clear();
    }

    void MaquinaEstados::inserirEstado(Estado* est) {
        mapaEstados.insert(std::pair<IdEstado, Estado*>(est->getID(), est));
    }

    void MaquinaEstados::setEstadoAtual(IdEstado id) {
        Estado* temp = estadoAtual;
        if(mapaEstados[id]) {
            estadoAtual = mapaEstados[id];
            if(temp != NULL) {
                temp->cegar();  // Faz o estado anterior deixar de reagir à Entrada do usuário
                estadoAtual->getMenu()->pGrafico->atualizaView(Coordenada(COMPRIMENTO/2.f, ALTURA/2.f));  // Reseta a view para o centro da tela
                temp->getMenu()->pGrafico->atualizaView(Coordenada(COMPRIMENTO/2.f, ALTURA/2.f));  // Reseta a view para o centro da tela
                
                if(temp->getID() == Estados::IdEstado::mercurio || temp->getID() == Estados::IdEstado::netuno) {
                    Menus::Fases::Fase* fase = dynamic_cast<Menus::Fases::Fase*>(temp); //passa para o menu de tran
                    if(id == Estados::IdEstado::menuTransicao) {
                        Menus::MenuTransicao* menut = dynamic_cast<Menus::MenuTransicao*>(estadoAtual);
                        menut->setOrigem(temp->getID());
                        menut->setPontuacaoPrev(fase->getPontuacao());
                        menut->setMultiplayer(fase->getMultiplayer());
                    }
                    else if(id == Estados::IdEstado::menuGameOver) {
                        Menus::MenuGameOver* menuG = dynamic_cast<Menus::MenuGameOver*>(estadoAtual);
                        menuG->setPontuacao(fase->getPontuacao());
                    }
                }

                else if(temp->getID() == Estados::IdEstado::menuTransicao) {
                    if(id == Estados::IdEstado::netuno) {
                        Menus::Fases::Netuno* net = dynamic_cast<Menus::Fases::Netuno*>(estadoAtual);
                        Menus::MenuTransicao* menut = dynamic_cast<Menus::MenuTransicao*>(temp);
                        if(net != NULL && menut != NULL) {
                            net->resetarEstadoOriginal();
                            net->setPontuacao(menut->getPontuacaoPrev());
                            net->setMultiplayer(menut->getMultiplayer());
                            net->geraEntidades(true);
                        }
                    }
                }

                
            }


            if(temp != NULL) {
                if(temp->getID() == Estados::IdEstado::menuJogar) {
                    if(id == Estados::IdEstado::mercurio) {
                        Menus::Fases::Mercurio* tmp = dynamic_cast<Menus::Fases::Mercurio*>(estadoAtual);
                        if(tmp != NULL) {
                            tmp->resetarEstadoOriginal();
                            tmp->setPontuacao(0);
                            tmp->geraEntidades(true);
                        }
                    } else if(id == Estados::IdEstado::netuno) {
                        Menus::Fases::Netuno* tmp = dynamic_cast<Menus::Fases::Netuno*>(estadoAtual);
                        if(tmp != NULL) {
                            tmp->resetarEstadoOriginal();
                            tmp->setPontuacao(0);
                            tmp->geraEntidades(true);
                        }
                    }
                }
            }

            estadoAtual->executar(0);
            estadoAtual->getMenu()->reiniciarRelogio();
            estadoAtual->observar();
        }
    }

    void MaquinaEstados::setEstadoAtual(IdEstado id, std::list<Entidades::Entidade*> *lEnt) {
        Estado* temp = estadoAtual;
        if(id == IdEstado::menuPausa && mapaEstados[id]) {
            estadoAtual = mapaEstados[id];
            temp->cegar();  // Faz o estado anterior deixar de reagir à Entrada do usuário

            Menus::MenuPausa* pausa = dynamic_cast<Menus::MenuPausa*>(estadoAtual);
            pausa->setFaseID(temp->getID());
            pausa->setFase(dynamic_cast<Menus::Fases::Fase*>(temp));
            pausa->setLista(lEnt);

            estadoAtual->setAnterior(temp);
            estadoAtual->getMenu()->pGrafico->atualizaView(Coordenada(COMPRIMENTO/2.f, ALTURA/2.f));  // Reseta a view para o centro da tela
            estadoAtual->executar(0);
            estadoAtual->getMenu()->reiniciarRelogio();
            estadoAtual->observar();
        } else if(temp->getID() == IdEstado::menuPausa && mapaEstados[id]) {
            estadoAtual = mapaEstados[id];
            temp->cegar();  // Faz o estado anterior deixar de reagir à Entrada do usuário
            estadoAtual->getMenu()->reiniciarRelogio();
            estadoAtual->observar();
        }
    }

    void MaquinaEstados::setEstadoAnterior() {
        if(estadoAtual->getAnterior() != NULL && tempo.getElapsedTime().asSeconds() > 0.2) {
            setEstadoAtual(estadoAtual->getAnterior()->getID());
            tempo.restart();
        }
    }

    void MaquinaEstados::atualizarEstadoAtual(const float dt) {
        estadoAtual->atualizar(dt);
    }

    void MaquinaEstados::renderizarEstadoAtual() {
        estadoAtual->renderizar();
    }
} // namespace Estados