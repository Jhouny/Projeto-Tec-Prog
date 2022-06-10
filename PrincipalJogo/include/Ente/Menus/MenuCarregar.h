#ifndef _MENU_CARREGAR_H_
#define _MENU_CARREGAR_H_

#include "Menu.h"

#include "../../ElementosGraficos/BotaoPath.h"
#include "../../Controle/ControleMenu.h"
#include "../Entidades/Dinamicas/Jogador.h"

namespace Menus{
    class MenuCarregar: public Menu {
        private:
            ElementosGraficos::BotaoPath* pBotaoPath;
            Controle::ControleMenu pControleMenu;
            std::vector<std::string> vectorCaminhos;
            Entidades::Personagens::Jogador* jogador1;
            Entidades::Personagens::Jogador* jogador2;
            std::list<Entidades::Entidade> lEntes;
            
        public:
            MenuCarregar( Entidades::Personagens::Jogador* jog1,Entidades::Personagens::Jogador* jog2);

            ~MenuCarregar();
            void getLista();

            void leCaminhoArquivos();

            void carregarFase();

            void lerTrecho(std::string in);

            void ativarControle();

            void desativarControle();

            void criaBotoes() ;

            void renderizar() ;

            void atualizar(const float dt);

            void executar(const float dt);
                        

    };
}

#endif