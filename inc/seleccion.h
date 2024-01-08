// MACROS
#define MATERIAL_MAX 1
#define objVerticesSeleccion    4
#define objFacesSeleccion       2

/** Vertices for the Seleccion object. */
static const GLshort objVertexdataSeleccion[4 * 3]={
    -345, -5000, 346,
    345, -5000, 344,
    -345, -5000, -345,
    345, -5000, -345
};

/* Define normals for the cube */
static const GLbyte objNormaldataSeleccion[4 * 3]={
    0,127,0,
    0,127,0,
    0,127,0,
    0,127,0
};

/** Indices to the Seleccion object vertices. */
static const GLushort objFacedataSeleccion[2 * 3]={
    1,2,0,
    1,3,2
};

/* textura UV */
static const GLbyte objTexdataSeleccion[4 * 2] ={
    -127,127,
    127,127,
    -127,-127,
    127,-127
};
