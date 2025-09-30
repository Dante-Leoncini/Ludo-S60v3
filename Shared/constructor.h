void ConstructL(){
    ConvertirTexData(objTexdataDado, objTexdataDadoF, 248 * 2);

    //esto arregla las fichas. sus coordenadas estaban mal
    for (int i=0; i<145; i++){
        objVertexdataFicha[i*3+1] += 5000;
    }

	for(int i=0; i<4; i++){
		Equipos[i].termino = false;
		Equipos[i].puesto = 0;
		Equipos[i].llegaron = 0;	
	}
	for(int i=0; i<16; i++){
		Fichas[i].vivo = false;	//nacen muertos	
		Fichas[i].gano = false;	//nacen sin ganar	
		Fichas[i].movimiento = false;	//no tiene movimiento
		Fichas[i].progreso = 0;
		Fichas[i].casillero = -1;
		Fichas[i].AnimFrame = 0;
		Fichas[i].IndiceHabitante = 1;
		if (i < 4){
			Fichas[i].equipo = Verde; 
			//Fichas[i].color[4] = MATERIALCOLOR(0.01, 0.63, 0.29, 1.0); //colorEquipo2;
		}
		else if (i < 8){
			Fichas[i].equipo = Amarillo;
			//Fichas[i].color[4] = MATERIALCOLOR(1.0, 0.87, 0.02, 1.0); //colorEquipo4;
		}
		else if (i < 12){
			Fichas[i].equipo = Azul;
			//Fichas[i].color[4] = MATERIALCOLOR(0.20, 0.36, 0.83, 1.0); //colorEquipo3;
		}
		else {
			Fichas[i].equipo = Rojo;
			//Fichas[i].color[4] = MATERIALCOLOR(0.92, 0.12, 0.15, 1.0); //colorEquipo1;
		}
		Fichas[i].posX = posMuertos[i][0];
		Fichas[i].posY = posMuertos[i][1];
	}
}