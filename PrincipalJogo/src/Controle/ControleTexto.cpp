#include "../../include/Controle/Controletexto.h"
#include "../../include/Ente/Menus/MenuGameOver.h"

namespace Controle{

    ControleTexto::ControleTexto(Menus::MenuGameOver* menu):
        Observador(),
        espaco("Space"),
        apagar("BackSpace"),
        tamMax(20),
        contador(0),
        pMenu(menu)
    {

    }

    ControleTexto::~ControleTexto(){

    }

    void ControleTexto::compartilharTeclaPressionada(std::string tecla) {
        cout << "entrouTexto" << endl;
        if (tecla == "Enter" || tecla == "Right" || tecla == "Left" || 
            tecla == "Up" || tecla == "Down" || tecla == "Escape" || 
            tecla == "Control" || tecla == "Shift" || tecla == "RControl" || 
            tecla == "RShift" || tecla == "Tab"|| tecla == "Unknown") {
            return;
        }
        if(contador <= tamMax){
            if(tecla == "Space"){
                nome += " ";
                contador++;
            } else if(tecla == apagar && contador >=0 ){
                nome.erase(contador--);
            }
            else{
                nome += tecla;
                contador++;             
            }
        }
        cout << "saiuTexto" << endl;
    }

    void ControleTexto::compartilharTeclaLiberada(std::string tecla){ //Precisa?
        
    }
    void ControleTexto::apagaNome(){
        nome = "";
        contador = 0;
    }


}