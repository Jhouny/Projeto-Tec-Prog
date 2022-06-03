#include "../../../include/Ente/Menus/MenuPontuacao.h"
#include "../../../include/ElementosGraficos/Texto.h"

namespace Menus{
    MenuPontuacao::MenuPontuacao():
        Menu()
        {
        setID(Estados::IdEstado::pontuacao);
        /*
        setTitulo("PONTUAÇÃO");
        getTitulo()->setPosicao(Coordenada(COMPRIMENTO/2.f - getTitulo()->getTexto()->getLocalBounds().width/2.f, 100.f));
        getTitulo()->setContorno(sf::Color(200, 50, 50, 230), 5);*/
        
        executar(0);
    }

    MenuPontuacao::~MenuPontuacao() {}

    void MenuPontuacao::criaBotoes(){
        pBotao = new ElementosGraficos::Botao(Coordenada(200, 100), Coordenada(1100.f, 650.f),Estados::IdEstado::menuAbertura,"VOLTAR"); //VOLTA PARA O MENU
        pBotao->ativar();
        botoesAtivos.insert(std::pair<ElementosGraficos::Botao*, bool>(pBotao, true));        
    }

    void MenuPontuacao::incluir(ElementosGraficos::Texto *texto){
        if(texto)
            lTextos.push(texto);
        else
            cout << "Ponteiro para texto esta nulo" << endl;

    }

    void MenuPontuacao::criaTextos(){
        pTexto = new ElementosGraficos::Texto(Coordenada(400,250),Coordenada(COMPRIMENTO/7.f,50),"Posicao:");
        pTexto->setCor(sf::Color::Yellow);
        getTitulo()->setContorno(sf::Color(200, 50, 50, 230), 5);
        incluir(pTexto);

        pTexto = new ElementosGraficos::Texto(Coordenada(400,250),Coordenada((float)COMPRIMENTO/2.f,50),"Nome:");
        pTexto->setCor(sf::Color::Yellow);
        getTitulo()->setContorno(sf::Color(200, 50, 50, 230), 5);
        incluir(pTexto);

        pTexto = new ElementosGraficos::Texto(Coordenada(400,250),Coordenada(COMPRIMENTO/1.f-COMPRIMENTO/5.f,50),"Pontuação: ");
        pTexto->setCor(sf::Color::Yellow);
        getTitulo()->setContorno(sf::Color(200, 50, 50, 230), 5);
        incluir(pTexto);

        pTexto = new ElementosGraficos::Texto(Coordenada(400,150),Coordenada(COMPRIMENTO/7.f,150),"1");
        pTexto->setCor(sf::Color::Yellow);
        getTitulo()->setContorno(sf::Color(200, 50, 50, 230), 5);
        incluir(pTexto);

        pTexto = new ElementosGraficos::Texto(Coordenada(400,150),Coordenada(COMPRIMENTO/7.f,250),"2");
        pTexto->setCor(sf::Color::Yellow);
        getTitulo()->setContorno(sf::Color(200, 50, 50, 230), 5);
        incluir(pTexto);

        pTexto = new ElementosGraficos::Texto(Coordenada(400,150),Coordenada(COMPRIMENTO/7.f,350),"3");
        pTexto->setCor(sf::Color::Yellow);
        getTitulo()->setContorno(sf::Color(200, 50, 50, 230), 5);
        incluir(pTexto);

        pTexto = new ElementosGraficos::Texto(Coordenada(400,150),Coordenada(COMPRIMENTO/7.f,450),"4");
        pTexto->setCor(sf::Color::Yellow);
        getTitulo()->setContorno(sf::Color(200, 50, 50, 230), 5);
        incluir(pTexto);

        pTexto = new ElementosGraficos::Texto(Coordenada(400,150),Coordenada(COMPRIMENTO/7.f,550),"5");
        pTexto->setCor(sf::Color::Yellow);
        getTitulo()->setContorno(sf::Color(200, 50, 50, 230), 5);
        incluir(pTexto);
    }

    void MenuPontuacao::atualizar(const float dt){
         for(it = botoesAtivos.begin(); it != botoesAtivos.end(); it++){
            (it->first)->executar();
        }
    }

    void MenuPontuacao::renderizar(){
        pGrafico->draw(&fundo, false);
        int i;
        for(i = 0; i < lTextos.getTamanho(); i++ ){
            pGrafico->draw(lTextos[i]->getTexto());
        }
         for(it = botoesAtivos.begin(); it != botoesAtivos.end(); it++){
            pGrafico->draw((it->first)->getSprite(),false);
            pGrafico->draw((it->first)->getTexto());
        }
    }

    void MenuPontuacao::executar(const float dt){
        criaBotoes();
        criaTextos();
        setFundoAleatorio();
        pGrafico->setTamView(Coordenada(COMPRIMENTO, ALTURA));
        pGrafico->atualizaView(Coordenada(COMPRIMENTO/2.f, ALTURA/2.f));
    }
}