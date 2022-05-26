#ifndef _GRAFICO_H_
#define _GRAFICO_H_

#include"../Auxiliares/stdafx.h"

class Jogador;
namespace Gerenciadores {
    class Grafico {
        private:
            sf::RenderWindow* window;
            sf::Event* event;
            sf::View view;
            sf::View minimap;

            // Mapeia o path das texturas aos elementos 
            std::map<const char*, sf::Texture*> mapaTexturas;

            /* Seguindo a sugestão do monitor Matheus Burda, usa-se o padrão Singleton */
            static Gerenciadores::Grafico* instancia;
            Grafico();
            
        public:
            ~Grafico();

            static Grafico* getInstancia();

            void draw(sf::RectangleShape* shape);
            
            void draw(sf::Sprite* sp);

            void setTamView(Coordenada t){//nova
                view.setSize(t.x,t.y);
            }

            void setMinimap(Coordenada t){//nova
                minimap.setSize(t.x,t.y);
            }
            void setMinimapViewport();//nova
            //minimapView.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));

            void setRotate();//nova

            void atualizaView(Jogador* player);//nova
                
            
            void atualizaMinimap(Coordenada p);    //nova

            void clear();

            void display();

            bool isOpened() const;

            void terminar();

            void setCenter(Coordenada c1);

            void setCenter(Coordenada c1, Coordenada c2);

            sf::Texture* loadTexture(const char* path);

            sf::Event* getEvent() const;

            sf::RenderWindow* getWindow() const;
    };
};

#endif