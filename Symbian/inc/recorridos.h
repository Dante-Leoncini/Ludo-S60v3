//posicion muerto y Victoria
int posMuertos[16][2] = {
	{-2750, -1750},{-1750, -1750},{-2750, -2750},{-1750, -2750},
	{ 2750, -1750},{ 1750, -1750},{ 2750, -2750},{ 1750, -2750},
	{ 2750,  1750},{ 1750,  1750},{ 2750,  2750},{ 1750,  2750},
	{-2750,  1750},{-1750,  1750},{-2750,  2750},{-1750,  2750}
};

int posVictoria[16][2] = {
	{-610, -0},{-290, 0},{-610,  310},{-610, -310}, //verde
	{ 0, -610},{0, -290},{-310, -610},{ 310, -610},
	{ 610, -0},{ 290, 0},{ 610, -310},{ 610,  310},
	{ 0,  610},{0,  290},{ 310,  610},{-310,  610}
};

//posicion de los trofeos
int posTrofeos[4][2] = {
	{-2250, -2250},{2250, -2250},{2250, 2250},{-2250, 2250},
};

//de 2 a 4
int PosHabitantesCuatro[4][2] = {
	{250, 250},{-250, -250},{250, -250},{-250, 250}
};

//de 5 a 9
int PosHabitantesNueve[9][2] = {
	{250, 250},{-250, -250},{250, -250},{-250, 250},
	{0, 250},{0, -250},{-250, 0},{250, 0},
	{0, 0}
};

//de 10 a 16
int PosHabitantesDieciseis[16][2] = {
	{300, 300},{-300, -300},{300, -300},{-300, 300},
	{100, 100},{-100, -100},{-100, 100},{100, -100},
	{100, 300},{-100, 300},{100, -300},{-100, -300}, //Y
	{300, 100},{300, -100},{-300, 100},{-300, -100} //X
};

int posDado[4][2] = {
	{-1300, -1300},{750, -1300},{750,  1200},{-1400, 1200}
};

class Casillero { //clase ficha
	public:
		bool seguro;
		int x;
		int y;
		int visitantes;
};

//Crea un array de objetos "Casillero"
Casillero casilleros[72] = { //X,Y,CanFichas,
		{seguro: true, x: -3000, y: -500, visitantes: 0}, //0
		{seguro: false, x: -2500, y: -500, visitantes: 0},
		{seguro: false, x: -2000, y: -500, visitantes: 0},
		{seguro: false, x: -1500, y: -500, visitantes: 0},
		{seguro: false, x: -1000, y: -500, visitantes: 0},
		{seguro: false, x: -500,  y: -1000, visitantes: 0},
		{seguro: false, x: -500,  y: -1500, visitantes: 0},
		{seguro: false, x: -500,  y: -2000, visitantes: 0},
		{seguro: false, x: -500,  y: -2500, visitantes: 0},
		{seguro: true, x: -500,  y: -3000, visitantes: 0},//9
		{seguro: false, x: -500,  y: -3500, visitantes: 0},
		{seguro: false, x: 0,     y: -3500, visitantes: 0},
		{seguro: false, x: 500,   y: -3500, visitantes: 0},
		{seguro: true, x: 500,   y: -3000, visitantes: 0},//13
		{seguro: false, x: 500,   y: -2500, visitantes: 0},
		{seguro: false, x: 500,   y: -2000, visitantes: 0},
		{seguro: false, x: 500,   y: -1500, visitantes: 0},
		{seguro: false, x: 500,   y: -1000, visitantes: 0},
		{seguro: false, x: 1000,  y: -500, visitantes: 0},
		{seguro: false, x: 1500,  y: -500, visitantes: 0},
		{seguro: false, x: 2000,  y: -500, visitantes: 0},
		{seguro: false, x: 2500,  y: -500, visitantes: 0},
		{seguro: true, x: 3000,  y: -500, visitantes: 0},//22
		{seguro: false, x: 3500,  y: -500, visitantes: 0},
		{seguro: false, x: 3500,  y: 0, visitantes: 0},
		{seguro: false, x: 3500,  y: 500, visitantes: 0},
		{seguro: true, x: 3000,  y: 500, visitantes: 0},//26
		{seguro: false, x: 2500,  y: 500, visitantes: 0},
		{seguro: false, x: 2000,  y: 500, visitantes: 0},
		{seguro: false, x: 1500,  y: 500, visitantes: 0},
		{seguro: false, x: 1000,  y: 500, visitantes: 0},
		{seguro: false, x: 500,   y: 1000, visitantes: 0},
		{seguro: false, x: 500,   y: 1500, visitantes: 0},
		{seguro: false, x: 500,   y: 2000, visitantes: 0},
		{seguro: false, x: 500,   y: 2500, visitantes: 0},
		{seguro: true, x: 500,   y: 3000, visitantes: 0},//35
		{seguro: false, x: 500,   y: 3500, visitantes: 0},
		{seguro: false, x: 0,     y: 3500, visitantes: 0},
		{seguro: false, x: -500,  y: 3500, visitantes: 0},
		{seguro: true, x: -500,  y: 3000, visitantes: 0},//39
		{seguro: false, x: -500,  y: 2500, visitantes: 0},
		{seguro: false, x: -500,  y: 2000, visitantes: 0},
		{seguro: false, x: -500,  y: 1500, visitantes: 0},
		{seguro: false, x: -500,  y: 1000, visitantes: 0},
		{seguro: false, x: -1000, y: 500, visitantes: 0},
		{seguro: false, x: -1500, y: 500, visitantes: 0},
		{seguro: false, x: -2000, y: 500, visitantes: 0},
		{seguro: false, x: -2500, y: 500, visitantes: 0},
		{seguro: true, x: -3000, y: 500, visitantes: 0},//48
		{seguro: false, x: -3500, y: 500, visitantes: 0},
		{seguro: false, x: -3500, y: 0, visitantes: 0}, 
		{seguro: false, x: -3500, y: -500, visitantes: 0}, //51
		
		{seguro: true, x: -3000, y: 0, visitantes: 0}, //52 final verde 1
		{seguro: true, x: -2500, y: 0, visitantes: 0}, //53 final verde 2
		{seguro: true, x: -2000, y: 0, visitantes: 0}, //54  final verde 3
		{seguro: true, x: -1500, y: 0, visitantes: 0}, //55 final verde 4
		{seguro: true, x: -1000, y: 0, visitantes: 0}, //56 final verde 5
		
		{seguro: true, x: 0, y: -3000, visitantes: 0}, //57 final amarillo 1
		{seguro: true, x: 0, y: -2500, visitantes: 0}, //58 final amarillo 2
		{seguro: true, x: 0, y: -2000, visitantes: 0}, //59  final amarillo 3
		{seguro: true, x: 0, y: -1500, visitantes: 0}, //60 final amarillo 4
		{seguro: true, x: 0, y: -1000, visitantes: 0}, //61 final amarillo 5
		
		{seguro: true, x: 3000, y: 0, visitantes: 0}, //62 final azul 1
		{seguro: true, x: 2500, y: 0, visitantes: 0}, //63 final azul 2
		{seguro: true, x: 2000, y: 0, visitantes: 0}, //64  final azul 3
		{seguro: true, x: 1500, y: 0, visitantes: 0}, //65 final azul 4
		{seguro: true, x: 1000, y: 0, visitantes: 0}, //66 final azul 5
		
		{seguro: true, x: 0, y: 3000, visitantes: 0}, //67 final rojo 1
		{seguro: true, x: 0, y: 2500, visitantes: 0}, //68 final rojo 2
		{seguro: true, x: 0, y: 2000, visitantes: 0}, //69  final rojo 3
		{seguro: true, x: 0, y: 1500, visitantes: 0}, //70 final rojo 4
		{seguro: true, x: 0, y: 1000, visitantes: 0}, //71 final rojo 5
};

//las posiciones X e Y de las fichas
int RutaVerde[56]={
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
		21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
		41,42,43,44,45,46,47,48,49,50,
		52,53,54,55,56 //FINAL
};

int RutaAmarillo[56]={
		13,14,15,16,17,18,19,20,
		21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
		41,42,43,44,45,46,47,48,49,50,51,0,1,2,3,4,5,6,7,8,9,10,11,
		57,58,59,60,61 //FINAL
};

int RutaAzul[56]={
		26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
		41,42,43,44,45,46,47,48,49,50,51,
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
		21,22,23,24,
		62,63,64,65,66 //FINAL
};

int RutaRojo[56]={39,40,
		41,42,43,44,45,46,47,48,49,50,51,
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
		21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,
		67,68,69,70,71 //FINAL
};

