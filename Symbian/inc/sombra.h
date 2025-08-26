// MACROS
#define MATERIAL_MAX 1
#define objVerticesSombra    4
#define objFacesSombra       2

/** Vertices for the Sombra object. */
static const GLshort objVertexdataSombra[4 * 3]={
    -166, -5000, 168,
    525, -5000, 166,
    -166, -5000, -523,
    525, -5000, -523
};

/* Define normals for the cube */
static const GLbyte objNormaldataSombra[4 * 3]={
    0,127,0,
    0,127,0,
    0,127,0,
    0,127,0
};

/** Indices to the Sombra object vertices. */
static const GLushort objFacedataSombra[2 * 3]={
    1,2,0,
    1,3,2
};

/* textura UV */
static const GLbyte objTexdataSombra[4 * 2] ={
    -127,127,
    127,127,
    -127,-127,
    127,-127
};
