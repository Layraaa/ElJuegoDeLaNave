#include <iostream>
#include <windows.h>
#include <conio.h>
#include <list>
#include <stdio.h>
#include <random>
#include <chrono>

using namespace std;

/* TO DO 
Contador cuenta atras para comenzar
*/

/* Mueve el cursor a donde sea necesario */
void moverxy(int x, int y = 40){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pw;
    pw.X = x;
    pw.Y = y;
    SetConsoleCursorPosition(hCon, pw);
}

/* Elimina los Input introducidos*/
void ClearInputBuffer()
{
    PINPUT_RECORD ClearBuffer1 = new INPUT_RECORD[1024];
    DWORD ClearBuffer2;
    ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE),ClearBuffer1,1024,&ClearBuffer2);
    delete[] ClearBuffer1;
}

/* Establece la visibilidad del cursor */
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

/* Genera numeros aleatoriamente */
int random(){
	random_device rd;
    mt19937::result_type seed = rd() ^ (
            (mt19937::result_type)
            chrono::duration_cast<chrono::seconds>(
                chrono::system_clock::now().time_since_epoch()
                ).count() +
            (mt19937::result_type)
            chrono::duration_cast<chrono::microseconds>(
                chrono::high_resolution_clock::now().time_since_epoch()
                ).count() );

    mt19937 gen(seed);
    uniform_int_distribution<unsigned> distrib(1, 74);
    return distrib(gen);
}

class juego{
    private:
        int x, y;
        int vidas = 3, puntos = 0;
    public:
        void movernave();
        void borrarnave();
        void escribirnave();
        void asteroides(int id);

        juego(int _x): x(_x){

            /* Oculta el cursor en la consola */
            ShowConsoleCursor(false);

            /* El usuario escribe para empezar la partida */
            cout << "*  _____ _     _                              _        _                    *" << endl;
            cout << "* | ____| |   (_)_   _  ___  __ _  ___     __| | ___  | | __ _              *" << endl;
            cout << "* |  _| | |   | | | | |/ _ \\/ _` |/ _ \\   / _` |/ _ \\ | |/ _` |             *" << endl;
            cout << "* | |___| |   | | |_| |  __/ (_| | (_) | | (_| |  __/ | | (_| |             *" << endl;
            cout << "* |_____|_|  _/ |\\__,_|\\___|\\__, |\\___/   \\__,_|\\___| |_|\\__,_|             *" << endl;
            cout << "*           |__/            |___/                                           *" << endl;
            cout << "*                                                                           *" << endl;
            cout << "*  _ __   __ ___   _____                                                    *" << endl;
            cout << "* |  _ \\ / _  \\ \\ / / _ \\                                                   *" << endl;
            cout << "* | | | | (_| |\\ V /  __/                                                   *" << endl;
            cout << "* |_| |_|\\__,_| \\_/ \\___|                                                   *" << endl;
            cout << "*                                                                           *" << endl;
            cout << "* Hecho por @Layraaa                                                        *" << endl;
            cout << "* Presiona una tecla para comenzar...                                       *" << endl;
            cout << "* Maximiza tu pantalla para poder jugar                                     *" << endl;
            getch();
            
            /* Crear escenario */
            system ("CLS");
            cout << "*  _____ _     _                              _        _                    *" << endl;
            cout << "* | ____| |   (_)_   _  ___  __ _  ___     __| | ___  | | __ _              *" << endl;
            cout << "* |  _| | |   | | | | |/ _ \\/ _` |/ _ \\   / _` |/ _ \\ | |/ _` |             *" << endl;
            cout << "* | |___| |   | | |_| |  __/ (_| | (_) | | (_| |  __/ | | (_| |             *" << endl;
            cout << "* |_____|_|  _/ |\\__,_|\\___|\\__, |\\___/   \\__,_|\\___| |_|\\__,_|             *" << endl;
            cout << "*           |__/            |___/                                           *" << endl;
            cout << "*                                                                           *" << endl;
            cout << "*  _ __   __ ___   _____                                                    *" << endl;
            cout << "* |  _ \\ / _  \\ \\ / / _ \\                                                   *" << endl;
            cout << "* | | | | (_| |\\ V /  __/                                                   *" << endl;
            cout << "* |_| |_|\\__,_| \\_/ \\___|                                                   *" << endl;
            cout << "*                                                                           *" << endl;
            cout << "* Hecho por @Layraaa                                       Vidas: 3         *" << endl;
            cout << "* https://github.com/Layraaa/ElJuegoDeLaNave               Puntos: 0        *" << endl;
            cout << "*****************************************************************************" << endl;
            for (int i = 0; i < 26; i++)
            {
                cout << "*                                                                           *" << endl;
            }
            cout << "*****************************************************************************" << endl;
            escribirnave();
            
            /* Genera la seed del randomizador*/
            srand(_getpid());

            /* Mientras tenga más de 0 vidas, el usuario sigue jugando */
            /* 10 asteroides, 6 a velocidad 1, 4 a velocidad 2*/
            while (vidas > 0)
            {
                movernave();
                asteroides(0);
                asteroides(1);
                asteroides(2);
                asteroides(3);
                asteroides(4);
                asteroides(5);
                asteroides(6);
                asteroides(7);
                asteroides(8);
                asteroides(9);
                asteroides(1);
                asteroides(4);
                asteroides(6);
                asteroides(9);
                movernave();
                Sleep(50 - (puntos / 100));
            }

            /* Juego terminado */
            moverxy(0, 43);
            cout << "Juego terminado" << endl;
            cout << "Presiona una tecla para salir..." << endl;
            ClearInputBuffer();
            getch();
            ShowConsoleCursor(true);
        }
        
};

/* Crea los asteroides, los mueve y comprueba si han golpeado contra la nave */
void juego::asteroides(int id){
    /* Crea dos arrays que almacenaran los valores de los asteroides*/
    static int array_height[10];
    static int array_x_axis[10];

    /* Genera los valores de altura */
    if (array_height[id] != 0 && array_x_axis[id] < 1 || array_x_axis[id] > 74)
    {
        array_height[id] = 0;
        array_x_axis[id] = random();
    }

    /*Se mueve a la posicion siguiente del asteroide*/
    moverxy(array_x_axis[id],15 + array_height[id]); // 15 es la altura inicial del asteroide por el encabezado

    /* Comprueba si es el primer asteroide y borra el anterior en cuyo caso*/
    if (array_height[id] != 0){
        moverxy(array_x_axis[id],15 + array_height[id] - 1);
        cout << " ";
        moverxy(array_x_axis[id],15 + array_height[id]);
    }

    /* Comprueba si lanza el asteroide hacia una linea más hacia abajo o si se ha chocado contra la nave o no */
    if (array_height[id] != 25){ // 25 es la altura donde se encuentra la nave
        cout << "#";
        array_height[id]++;
    } else {
        if (x <= (array_x_axis[id]) && x >= (array_x_axis[id] - vidas - 1)) /* Comprueba si la nave se ha chocado*/
        {
            /* Quita una vida*/
            vidas--;

            /* Reescribe la nave la hace más pequeña */
            moverxy(0);
            cout << "\x1b[2K";
            cout << "*                                                                           *" << endl;
            escribirnave();

            /* Actualiza el numero de vidas */
            moverxy(66, 12);
            cout << vidas;
        } else {

            /*Suma puntos*/
            puntos++;

            /* Actualiza el numero de puntos */
            moverxy(67, 13);
            cout << puntos;
        }

        /* Reestablece la altura a 0 del asteroide */
        array_height[id] = 0;

        /* Reestablece el eje x del asteroide */
        array_x_axis[id]= random();
    }
};

/* Mueve la nave hasta los limites */
void juego::movernave(){
    if (GetKeyState('A') < 0) {
        if (x > 1)
        {
            borrarnave();
            x--;
            escribirnave();
        }
    }
    if (GetKeyState('D') < 0) {
        if (x < 71 + (3 - vidas))
        {
            borrarnave();
            x++;
            escribirnave();
        }
    }
};

// Borrar toda la linea \x1b[2K
/* Permite borrar la nave para escribirla despues */
void juego::borrarnave(){
    switch (vidas)
    {
    case 3:
        moverxy(x); cout << "     " << endl;
        break;
    case 2:
        moverxy(x); cout << "    " << endl;
        break;
    case 1:
        moverxy(x); cout << "   " << endl;
        break;
    default:
        break;
    }
    
};

/* Escribe la nave en la consola */
void juego::escribirnave(){
    switch (vidas)
    {
    case 3:
        moverxy(x); cout << ("<--->");
        break;
    case 2:
        moverxy(x); cout << ("<-->");
        break;
    case 1:
        moverxy(x); cout << ("<->");
        break;
    default:
        break;
    }
    
};

int main()
{   
    /* Inicio del juego */
    juego juego(35);
}