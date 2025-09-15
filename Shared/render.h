inline float FIXED_TO_FLOAT(GLfixed x) {
    return static_cast<float>(x) / 65536.0f; // porque Q16.16
}

int EtapaRender = 5;
void DebugRender(int valor){
	EtapaRender +=valor;
	if (EtapaRender < 0){
		EtapaRender = 0;
	}	
	if (EtapaRender > 5){
		EtapaRender = 5;
	}	
    //std::cout << "EtapaRender: " << EtapaRender << std::endl;
}

void CalcularAnimaciones(){
    for (int i = 0; i < NUM_ANIMACIONES; i++) {        
		// Solo hacemos la transición para la animación del fondo
        if (animFrame[i] <= 100) {
			switch (i) {
				case fondo: {
					animFrame[i]+=2;
					for (int c = 0; c < 3; c++) {
						// Diferencia entre color objetivo y color anterior
						int delta = static_cast<int>((colorFondoTransicion[c] - colorFondoAnterior[c]) * 1000.0f); // escala temporal para int
						// Valor interpolado usando tu función Animacion
						int val = Animacion(delta, animFrame[i], easeInOut);
						// Reconstruir el valor float
						colorFondo[c] = colorFondoAnterior[c] + val / 1000.0f;
					}
					break;
				}
				case selector: {
					animFrame[i]+=2;
					if (animFrame[i] >= 100){
						colorSeleccion[0] = colorSeleccionFinal[0];
						colorSeleccion[1] = colorSeleccionFinal[1];
						colorSeleccion[2] = colorSeleccionFinal[2];

						colorSeleccionFinal[0] = colorSeleccionInicio[0];
						colorSeleccionFinal[1] = colorSeleccionInicio[1];
						colorSeleccionFinal[2] = colorSeleccionInicio[2];

						colorSeleccionInicio[0] = colorSeleccion[0];
						colorSeleccionInicio[1] = colorSeleccion[1];
						colorSeleccionInicio[2] = colorSeleccion[2];
						animFrame[i] = 0;
					}
					else {
						for (int c = 0; c < 3; c++) {
							// Diferencia entre color objetivo y color anterior
							int delta = static_cast<int>((colorSeleccionFinal[c] - colorSeleccionInicio[c]) * 1000.0f); // escala temporal para int
							// Valor interpolado usando tu función Animacion
							int val = Animacion(delta, animFrame[i], easeInOut);
							// Reconstruir el valor float
							colorSeleccion[c] = colorSeleccionInicio[c] + val / 1000.0f;
						}
					}
					//std::cout << "frame=" << animFrame[i] << std::endl;
					break;
				}
				default: break;
			}
        }
    }
}

// --- Función para dibujar la ficha ---
void Render() {   
	CalcularAnimaciones(); 
    glLoadIdentity();

	glTranslatef( posX, posZ, -cameraDistance+posY );
	glRotatef(rotY, 1, 0, 0); //angulo, X Y Z
	glRotatef(rotX, 0, 1, 0); //angulo, X Y Z
	glScalef(1024.0f / 65536.0f, 1024.0f / 65536.0f, 1024.0f / 65536.0f);
	glTranslatef( PivotX, PivotZ, PivotY);

	if (temblando){
		glTranslatef(temblandoAnim[temblandoFrame][0]*100, temblandoAnim[temblandoFrame][2]*100, temblandoAnim[temblandoFrame][1]*100);		
		temblandoFrame++;
		if (temblandoFrame > 9){
			temblando = false;
			temblandoFrame = 0;			
		}
	}

	glClearColor( colorFondo[0], colorFondo[1], colorFondo[2], 1.0f );	

    // Limpiar pantalla
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (EtapaRender < 1){return;}

	//dibujamos el tablero
    glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING); // No sombrear
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glBindTexture(GL_TEXTURE_2D, texTablero);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_SHORT, 0, objVertexdataModel);
    glNormalPointer(GL_BYTE, 0, objNormaldataModel);
    glTexCoordPointer(2, GL_FLOAT, 0, objTexdataModelF);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseWhite);

    glDrawElements(GL_TRIANGLES, objFacesModel * 3, GL_UNSIGNED_SHORT, objFacedataModel);

	if (EtapaRender < 2){return;}

    //sombras
	glDisable( GL_DEPTH_TEST ); //se quita el zbuffer
	glEnable( GL_BLEND ); // Enable blending for transparency.
	glBindTexture(  GL_TEXTURE_2D, texSombra ); //selecciona la textura
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glVertexPointer( 3, GL_SHORT, 0, objVertexdataSombra ); //selecciona los vertices
    glTexCoordPointer(2, GL_FLOAT, 0, objTexdataSombraF);
	glNormalPointer( GL_BYTE, 0, objNormaldataSombra ); //selecciona las normales
	
	// Evitar que la textura se repita y que haya sangrado
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	for(int i=0; i < NumJugadores*4; i++){
		glPushMatrix(); //guarda la matrix
		SetPos(i, true);
		if (Fichas[i].vivo && !Fichas[i].gano){
			if (casilleros[Fichas[i].casillero].visitantes > 9){
			    glScalef(0.5f,0.5f,0.5f);	
				glTranslatef( PosHabitantesDieciseis[Fichas[i].IndiceHabitante][0],
						      0,
						      PosHabitantesDieciseis[Fichas[i].IndiceHabitante][1]);	
				
			}
			else if (casilleros[Fichas[i].casillero].visitantes > 4){
			    glScalef(0.5f,0.5f,0.5f);	
				glTranslatef( PosHabitantesNueve[Fichas[i].IndiceHabitante][0],
						      0,
						      PosHabitantesNueve[Fichas[i].IndiceHabitante][1]);	
				
			}
			else if (casilleros[Fichas[i].casillero].visitantes > 1){
			    glScalef(0.6f,0.6f,0.6f);	
				glTranslatef( PosHabitantesCuatro[Fichas[i].IndiceHabitante][0],
						      0,
						      PosHabitantesCuatro[Fichas[i].IndiceHabitante][1]);					
			}	
		}
		glColor4f(1.0f, 1.0f, 1.0f, OpacidadSombra); 
		glRotatef(rotX, 0, -1, 0); //para simular que mira hacia la luz
		glDrawElements( GL_TRIANGLES, objFacesSombra * 3, GL_UNSIGNED_SHORT, objFacedataSombra );
		glPopMatrix(); //reinicia la matrix a donde se guardo
	}

	if (EtapaRender < 3){return;}
	
	//Seleccionado
	if (EstadoJuego == SeleccionFicha){
		glPushMatrix(); //guarda la matrix
		glVertexPointer( 3, GL_SHORT, 0, objVertexdataSeleccion ); //selecciona los vertices
		glTexCoordPointer( 2, GL_FLOAT, 0, objTexdataSeleccionF );
		glBindTexture(  GL_TEXTURE_2D, texSeleccion ); //selecciona la textura	
		glNormalPointer( GL_BYTE, 0, objNormaldataSeleccion ); //selecciona las normales
		glColor4f(colorSeleccion[0], colorSeleccion[1], colorSeleccion[2], 1.0f);
		glTranslatef(Fichas[FichaSeleccionada].posX, 0, Fichas[FichaSeleccionada].posY);
		//dibuja
		glDrawElements( GL_TRIANGLES, objFacesSombra * 3, GL_UNSIGNED_SHORT, objFacedataSeleccion );
		glPopMatrix(); //reinicia la matrix a donde se guardo	
	}

	if (EtapaRender < 4){return;}

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	//Fichas
	glEnable(GL_LIGHTING); // No sombrear
	glEnable( GL_DEPTH_TEST ); //se recupera el zbuffer
	glDisable( GL_TEXTURE_2D ); //desactiva las texturas
	glVertexPointer( 3, GL_SHORT, 0, objVertexdataFicha ); //selecciona los vertices
	glNormalPointer( GL_BYTE, 0, objNormaldataFicha ); //selecciona las normales

	glMaterialfv(   GL_FRONT_AND_BACK, GL_SPECULAR, objSpecular );
    #ifdef __SYMBIAN32__  
        // Symbian (OpenGL ES 1.1 con punto fijo)
        glMaterialx(GL_FRONT_AND_BACK, GL_SHININESS, 12 << 16);
    #else
        // PC (OpenGL normal)
        glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 12);
    #endif

	for(int e=0; e < NumJugadores; e++){
		//primero setea el color por equipo
		switch (e) {
			case Verde:
				objAmbient[0] = ambientDiffuseGreen[0];
				objAmbient[1] = ambientDiffuseGreen[1];
				objAmbient[2] = ambientDiffuseGreen[2];
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseGreen);
				break;
			case Amarillo:
				objAmbient[0] = ambientDiffuseYellow[0];
				objAmbient[1] = ambientDiffuseYellow[1];
				objAmbient[2] = ambientDiffuseYellow[2];
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseYellow);
				break;
			case Azul:
				objAmbient[0] = ambientDiffuseBlue[0];
				objAmbient[1] = ambientDiffuseBlue[1];
				objAmbient[2] = ambientDiffuseBlue[2];
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseBlue);
				break;
			case Rojo:
			default:
				objAmbient[0] = ambientDiffuseRed[0];
				objAmbient[1] = ambientDiffuseRed[1];
				objAmbient[2] = ambientDiffuseRed[2];
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseRed);
				break;
		}
		glMaterialfv(   GL_FRONT_AND_BACK, GL_AMBIENT,  objAmbient  );

		//dibuja las 4 fichas
		for(int i=0; i < 4; i++){
			glPushMatrix(); //guarda la matrix
			int ficha = e*4+i;
			SetPos(ficha, false);	//lo dibuja en su posicion y reinicia la matrix	
			//esto es cuando hay varias ficahs en un mismo casillero
			if (Fichas[ficha].vivo && !Fichas[ficha].gano){	
				if (casilleros[Fichas[ficha].casillero].visitantes > 9){
					glScalef(0.5f,0.5f, 0.5f);		
					glTranslatef( PosHabitantesDieciseis[Fichas[ficha].IndiceHabitante][0],
							      0,
							      PosHabitantesDieciseis[Fichas[ficha].IndiceHabitante][1]);	
					
				}
				else if (casilleros[Fichas[ficha].casillero].visitantes > 4){
					glScalef(0.5f,0.5f, 0.5f);		
					glTranslatef( PosHabitantesNueve[Fichas[ficha].IndiceHabitante][0],
							      0,
							      PosHabitantesNueve[Fichas[ficha].IndiceHabitante][1]);	
					
				}
				else if (casilleros[Fichas[ficha].casillero].visitantes > 1){
					glScalef(0.6f,0.6f, 0.6f);		
					glTranslatef( PosHabitantesCuatro[Fichas[ficha].IndiceHabitante][0],
							      0,
							      PosHabitantesCuatro[Fichas[ficha].IndiceHabitante][1]);	
				}			    
			}
			glDrawElements( GL_TRIANGLES, objFacesFicha * 3, GL_UNSIGNED_SHORT, objFacedataFicha );
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f); 
			glPopMatrix(); //reinicia la matrix a donde se guardo
		}
	}

	if (EtapaRender < 5){return;}
	
	//dado
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable( GL_TEXTURE_2D ); //activa la textura
	glBindTexture(  GL_TEXTURE_2D, texDado ); //selecciona la textura	
	glVertexPointer( 3, GL_SHORT, 0, objVertexdataDado ); //selecciona los vertices
	glNormalPointer( GL_BYTE, 0, objNormaldataDado ); //selecciona las normales
    glTexCoordPointer( 2, GL_FLOAT, 0, objTexdataDadoF );

	switch (TurnoDe) {
		case Verde:
			objAmbient[0] = ambientDiffuseGreen[0];
			objAmbient[1] = ambientDiffuseGreen[1];
			objAmbient[2] = ambientDiffuseGreen[2];
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseGreen);
			break;
		case Amarillo:
			objAmbient[0] = ambientDiffuseYellow[0];
			objAmbient[1] = ambientDiffuseYellow[1];
			objAmbient[2] = ambientDiffuseYellow[2];
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseYellow);
			break;
		case Azul:
			objAmbient[0] = ambientDiffuseBlue[0];
			objAmbient[1] = ambientDiffuseBlue[1];
			objAmbient[2] = ambientDiffuseBlue[2];
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseBlue);
			break;
		case Rojo:
		default:
			objAmbient[0] = ambientDiffuseRed[0];
			objAmbient[1] = ambientDiffuseRed[1];
			objAmbient[2] = ambientDiffuseRed[2];
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuseRed);
			break;
	}
	glMaterialfv(   GL_FRONT_AND_BACK, GL_AMBIENT,  objAmbient  );

	//reset pos rot
	glTranslatef(animacionPos[animacionPosFrame][0]+posDado[TurnoDe][0], 
			     animacionPos[animacionPosFrame][2], 
			     animacionPos[animacionPosFrame][1]+posDado[TurnoDe][1]); //x, z, y

	//rotacion del dado
	glRotatef(-animacionRot[animacionPosFrame][0], 0, 0, 1); //angulo, X Y Z
	glRotatef(-animacionRot[animacionPosFrame][1], 0, 1, 0); //angulo, X Y Z
	glRotatef(-animacionRot[animacionPosFrame][2], 1, 0, 0); //angulo, X Y Z
	SetDado();
	
	glDrawElements( GL_TRIANGLES, objFacesDado * 3, GL_UNSIGNED_SHORT, objFacedataDado );
	
	if (97 > animacionPosFrame){
		animacionPosFrame++;
	}
	else if (EstadoJuego == DadoLanzado){
		CalcOpciones();
	}
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}