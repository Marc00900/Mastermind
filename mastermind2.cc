#include <iostream>
#include <vector>
#include <random>
using namespace std;

typedef vector< vector<int> >Matriznum;
typedef vector< vector<char> >Matrizfich;
typedef vector<int> Vec;

struct Jugador {
    int Intents = 0;
    vector<int> Jugades;
    vector<string> Resultat;
};

Vec transform(int c){
    //transform = trasforma el codigo a vector.
    //Pre: c es un numero entero positivo de 4 digitos.
    //Post: Devuelve un vector con cada digito del numero c.
    Vec v(4);
    for(int i=0;i<4;++i){
        //Inv: El vector v contiende los digitos [4-i] del numero c en la posicion [3-(i-1)]
        v[3-i]=c%10;
        c/=10;
    }
    return v;
}

bool codigo_correcto(Vec &comb,int cod){
    //codigo_correcto = comprueba si el codigo/intento es valido.
    //Pre: comb es un vector de enteros vacio y cod en un numero entero positivo.
    /*Post: Devuelve verdadero si 1234<=cod<=8765 y no se repite ningun numero y si el codigo no contiene 9 o 0.
            En caso contrario, devuelve falso.*/
    bool incorrect=false;
    if(cod>=1234 and cod<=9876){
        comb=transform(cod);
        int i=0;
        while(not incorrect and i<4){
            //Inv: no se repite ningun numero en el codigo e i-1<4
            int j=i+1;
            while(not incorrect and j<4){
                //Inv: no se repite ningun numero en el codigo, i-1<4, j-1<4 y además en la posicion del vector j-1 no se encuentra ningún 0.
                if(comb[i]==comb[j] or comb[j]==0) incorrect=true;
                else ++j;
            }
            if(not incorrect) ++i;
        }
    }
    else incorrect=true;
    return not incorrect;
}

void jugador_a(Vec &comb, Jugador &C){
    //Pre: comb es un vector de enteros vacio.
    int cod;
    bool continuar =false;
    while(not continuar){
        cout<<"Jugador A, escull el codi secret:"<<endl;
        cin>>cod;
        if(codigo_correcto(comb,cod)) continuar=true;
        else cout<<"Error, codi incorrecte."<<endl;
    }
    if (continuar == true){
        C.Jugades.push_back(cod);
        C.Intents += 1;
    }
}

bool triar_mode(bool &Mode){
    //Detecta quin mode es vol jugar.
    //Pre: Mode es un bolea.
    //Post: Torna el resultat escollit pel jugador, el qual pot ser Manual o Automatic.
    char input;
    cin >> input;
    if (input == 'A'){
        Mode = false;
    } else if(input == 'M'){
        Mode = true;
    } else {
       cout << "Error: Mode de joc incorrecte." << endl << "Quin mode de joc vols triar, Manual (M)/ Aleatori (A)? :"<< endl;
       triar_mode(Mode);
    }
    return Mode;
}

int aleatori(int min, int max){
    static random_device device{};
    static default_random_engine engine{ device()};
    uniform_int_distribution<int> distribution{min, max};
    return distribution(engine);
}

int main(){
    int i=0; //contador de jugadas
    const int Blau = 1, Groc = 2, Vermell = 3, Verd = 4; 
    const int Marro = 5, Rosa = 6, Violeta = 7, Taronja = 8;
    char Negre='X', Blanques='O';
    bool correct =false, Manual;
    Jugador A,B;
    Vec combinacion(4);
    cout << "BENVINGUT AL JOC MASTERMIND!!" << endl << "Quin mode de joc vols triar, Manual (M)/ Aleatori (A)? :" << endl;
    triar_mode(Manual);
    jugador_a(combinacion, A);
}
