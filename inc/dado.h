// MACROS
#define MATERIAL_MAX 1
#define objVerticesDado    248
#define objFacesDado       236

/** Vertices for the Dado object. */
static const GLshort objVertexdataDado[248 * 3]={
    239, -158, -250,
    226, -198, -250,
    198, -226, -250,
    158, -239, -250,
    -158, -239, -250,
    -198, -226, -250,
    -226, -198, -250,
    -239, -158, -250,
    -239, 158, -250,
    -226, 198, -250,
    -198, 226, -250,
    -158, 239, -250,
    158, 239, -250,
    198, 226, -250,
    226, 198, -250,
    239, 158, -250,
    -239, -250, -158,
    -226, -250, -198,
    -198, -250, -226,
    -158, -250, -239,
    158, -250, -239,
    198, -250, -226,
    226, -250, -198,
    239, -250, -158,
    239, -250, 158,
    226, -250, 198,
    198, -250, 226,
    158, -250, 239,
    -158, -250, 239,
    -198, -250, 226,
    -226, -250, 198,
    -239, -250, 158,
    -239, -158, 250,
    -226, -198, 250,
    -198, -226, 250,
    -158, -239, 250,
    158, -239, 250,
    198, -226, 250,
    226, -198, 250,
    239, -158, 250,
    239, 158, 250,
    226, 198, 250,
    198, 226, 250,
    158, 239, 250,
    -158, 239, 250,
    -198, 226, 250,
    -226, 198, 250,
    -239, 158, 250,
    250, -158, 239,
    250, -198, 226,
    250, -226, 198,
    250, -239, 158,
    250, -239, -158,
    250, -226, -198,
    250, -198, -226,
    250, -158, -239,
    250, 158, -239,
    250, 198, -226,
    250, 226, -198,
    250, 239, -158,
    250, 239, 158,
    250, 226, 198,
    250, 198, 226,
    250, 158, 239,
    -250, -158, -239,
    -250, -198, -226,
    -250, -226, -198,
    -250, -239, -158,
    -250, -239, 158,
    -250, -226, 198,
    -250, -198, 226,
    -250, -158, 239,
    -250, 158, 239,
    -250, 198, 226,
    -250, 226, 198,
    -250, 239, 158,
    -250, 239, -158,
    -250, 226, -198,
    -250, 198, -226,
    -250, 158, -239,
    -158, 250, -239,
    -198, 250, -226,
    -226, 250, -198,
    -239, 250, -158,
    -239, 250, 158,
    -226, 250, 198,
    -198, 250, 226,
    -158, 250, 239,
    158, 250, 239,
    198, 250, 226,
    226, 250, 198,
    239, 250, 158,
    239, 250, -158,
    226, 250, -198,
    198, 250, -226,
    158, 250, -239,
    -224, 239, -239,
    -239, 224, -239,
    -239, 239, -224,
    -239, 239, 224,
    -239, 224, 239,
    -224, 239, 239,
    224, -239, 239,
    239, -239, 224,
    239, -224, 239,
    224, 239, -239,
    239, 239, -224,
    239, 224, -239,
    -224, -239, 239,
    -239, -224, 239,
    -239, -239, 224,
    224, -239, -239,
    239, -224, -239,
    239, -239, -224,
    -239, -224, -239,
    -224, -239, -239,
    -239, -239, -224,
    239, 224, 239,
    239, 239, 224,
    224, 239, 239,
    239, -158, -250,
    226, -198, -250,
    198, -226, -250,
    158, -239, -250,
    -158, -239, -250,
    -198, -226, -250,
    -226, -198, -250,
    -239, -158, -250,
    -239, 158, -250,
    -226, 198, -250,
    -198, 226, -250,
    -158, 239, -250,
    158, 239, -250,
    198, 226, -250,
    226, 198, -250,
    239, 158, -250,
    -239, -250, -158,
    -226, -250, -198,
    -198, -250, -226,
    -158, -250, -239,
    158, -250, -239,
    198, -250, -226,
    226, -250, -198,
    239, -250, -158,
    239, -250, 158,
    226, -250, 198,
    198, -250, 226,
    158, -250, 239,
    -158, -250, 239,
    -198, -250, 226,
    -226, -250, 198,
    -239, -250, 158,
    -239, -158, 250,
    -226, -198, 250,
    -198, -226, 250,
    -158, -239, 250,
    158, -239, 250,
    198, -226, 250,
    226, -198, 250,
    239, -158, 250,
    239, 158, 250,
    226, 198, 250,
    198, 226, 250,
    158, 239, 250,
    -158, 239, 250,
    -198, 226, 250,
    -226, 198, 250,
    -239, 158, 250,
    250, -158, 239,
    250, -198, 226,
    250, -226, 198,
    250, -239, 158,
    250, -239, -158,
    250, -226, -198,
    250, -198, -226,
    250, -158, -239,
    250, 158, -239,
    250, 198, -226,
    250, 226, -198,
    250, 239, -158,
    250, 239, 158,
    250, 226, 198,
    250, 198, 226,
    250, 158, 239,
    -250, -158, -239,
    -250, -198, -226,
    -250, -226, -198,
    -250, -239, -158,
    -250, -239, 158,
    -250, -226, 198,
    -250, -198, 226,
    -250, -158, 239,
    -250, 158, 239,
    -250, 198, 226,
    -250, 226, 198,
    -250, 239, 158,
    -250, 239, -158,
    -250, 226, -198,
    -250, 198, -226,
    -250, 158, -239,
    -158, 250, -239,
    -198, 250, -226,
    -226, 250, -198,
    -239, 250, -158,
    -239, 250, 158,
    -226, 250, 198,
    -198, 250, 226,
    -158, 250, 239,
    158, 250, 239,
    198, 250, 226,
    226, 250, 198,
    239, 250, 158,
    239, 250, -158,
    226, 250, -198,
    198, 250, -226,
    158, 250, -239,
    239, -224, 239,
    239, -239, 224,
    239, 224, -239,
    239, 239, -224,
    239, -239, -224,
    239, -224, -239,
    239, 239, 224,
    239, 224, 239,
    226, -198, -250,
    226, 198, -250,
    226, -250, -198,
    226, -250, 198,
    226, -198, 250,
    226, 198, 250,
    226, 250, 198,
    226, 250, -198,
    -239, 239, -224,
    -239, 224, -239,
    -239, 224, 239,
    -239, 239, 224,
    -239, -239, 224,
    -239, -224, 239,
    -239, -224, -239,
    -239, -239, -224,
    -226, -198, -250,
    -226, 198, -250,
    -226, -250, -198,
    -226, -250, 198,
    -226, -198, 250,
    -226, 198, 250,
    -226, 250, -198,
    -226, 250, 198
};

/* Define normals for the cube */
static const GLbyte objNormaldataDado[248 * 3]={
    0,0,-127,
    0,0,-127,
    0,0,-127,
    0,0,-127,
    0,0,-127,
    0,0,-127,
    0,0,-127,
    0,0,-127,
    0,0,-127,
    0,0,-127,
    0,0,-127,
    0,0,-127,
    0,0,-127,
    0,0,-127,
    0,0,-127,
    0,0,-127,
    0,-127,0,
    0,-127,0,
    0,-127,0,
    0,-127,0,
    0,-127,0,
    0,-127,0,
    0,-127,0,
    0,-127,0,
    0,-127,0,
    0,-127,0,
    0,-127,0,
    0,-127,0,
    0,-127,0,
    0,-127,0,
    0,-127,0,
    0,-127,0,
    0,0,127,
    0,0,127,
    0,0,127,
    0,0,127,
    0,0,127,
    0,0,127,
    0,0,127,
    0,0,127,
    0,0,127,
    0,0,127,
    0,0,127,
    0,0,127,
    0,0,127,
    0,0,127,
    0,0,127,
    0,0,127,
    127,0,0,
    127,0,0,
    127,0,0,
    127,0,0,
    127,0,0,
    127,0,0,
    127,0,0,
    127,0,0,
    127,0,0,
    127,0,0,
    127,0,0,
    127,0,0,
    127,0,0,
    127,0,0,
    127,0,0,
    127,0,0,
    -127,0,0,
    -127,0,0,
    -127,0,0,
    -127,0,0,
    -127,0,0,
    -127,0,0,
    -127,0,0,
    -127,0,0,
    -127,0,0,
    -127,0,0,
    -127,0,0,
    -127,0,0,
    -127,0,0,
    -127,0,0,
    -127,0,0,
    -127,0,0,
    8,118,46,
    39,120,15,
    41,120,9,
    38,118,-29,
    47,118,-9,
    15,120,-40,
    9,119,-42,
    -30,117,-39,
    -9,117,-48,
    -41,119,-16,
    -42,120,-10,
    -39,118,29,
    -47,118,8,
    -15,120,39,
    -9,120,40,
    28,118,37,
    -35,86,-86,
    -88,31,-86,
    -88,86,-31,
    -88,86,31,
    -88,31,86,
    -35,86,86,
    35,-86,86,
    88,-86,31,
    88,-31,86,
    35,86,-86,
    88,86,-31,
    88,31,-86,
    -35,-86,86,
    -88,-31,86,
    -88,-86,31,
    35,-86,-86,
    88,-31,-86,
    88,-86,-31,
    -88,-31,-86,
    -35,-86,-86,
    -88,-86,-31,
    88,31,86,
    88,86,31,
    35,86,86,
    -1,-2,-127,
    0,1,-127,
    -3,3,-127,
    4,2,-127,
    -4,2,-127,
    3,3,-127,
    2,5,-127,
    0,-3,-127,
    1,5,-127,
    0,1,-127,
    3,1,-127,
    -4,1,-127,
    4,1,-127,
    -3,0,-127,
    -2,-2,-127,
    0,5,-127,
    1,-127,-3,
    0,-127,1,
    3,-127,2,
    -4,-127,1,
    4,-127,2,
    -3,-127,2,
    -2,-127,5,
    0,-127,-3,
    -1,-127,5,
    0,-127,1,
    -3,-127,0,
    4,-127,1,
    -4,-127,0,
    3,-127,0,
    3,-127,-2,
    0,-127,5,
    1,-2,127,
    0,1,127,
    3,3,127,
    -4,2,127,
    4,2,127,
    -3,3,127,
    -3,5,127,
    0,-3,127,
    -1,5,127,
    0,1,127,
    -3,0,127,
    4,1,127,
    -4,1,127,
    3,0,127,
    3,-2,127,
    0,5,127,
    127,-2,-1,
    127,4,-1,
    127,3,-3,
    127,2,4,
    127,2,-4,
    127,3,3,
    127,4,1,
    127,-3,0,
    127,5,1,
    127,-2,1,
    127,1,3,
    127,1,-4,
    127,1,4,
    127,1,-3,
    127,-1,-1,
    127,5,0,
    -127,-2,1,
    -127,4,1,
    -127,2,3,
    -127,1,-4,
    -127,2,4,
    -127,2,-3,
    -127,4,-1,
    -127,-3,0,
    -127,5,-1,
    -127,-1,-1,
    -127,0,-3,
    -127,1,4,
    -127,1,-4,
    -127,0,3,
    -127,-2,1,
    -127,5,0,
    -4,127,-1,
    3,127,0,
    2,127,2,
    0,127,-5,
    1,127,3,
    0,127,-1,
    3,127,-2,
    -4,127,-1,
    4,127,-2,
    -3,127,-2,
    -3,127,-5,
    0,127,3,
    -1,127,-5,
    0,127,-1,
    -3,127,0,
    4,127,-1,
    85,-40,85,
    85,-85,40,
    85,40,-85,
    85,85,-40,
    85,-85,-40,
    85,-40,-85,
    85,85,40,
    85,40,85,
    -3,5,-127,
    0,1,-127,
    0,-127,1,
    -2,-127,-2,
    0,1,127,
    -3,-2,127,
    0,127,-1,
    -3,127,2,
    -85,85,-40,
    -85,40,-85,
    -85,40,85,
    -85,85,40,
    -85,-85,40,
    -85,-40,85,
    -85,-40,-85,
    -85,-85,-40,
    0,1,-127,
    2,-2,-127,
    3,-127,5,
    0,-127,1,
    3,5,127,
    0,1,127,
    0,127,-1,
    2,127,-5
};

/** Indices to the Dado object vertices. */
static const GLushort objFacedataDado[236 * 3]={
    7,11,15,
    23,27,31,
    39,43,47,
    55,59,63,
    71,75,79,
    87,91,95,
    200,131,130,
    241,199,198,
    196,203,202,
    96,233,232,
    247,195,194,
    193,167,166,
    164,207,206,
    235,234,101,
    156,147,146,
    227,171,170,
    169,159,158,
    102,217,216,
    132,215,214,
    212,179,178,
    176,135,134,
    105,219,218,
    149,155,154,
    152,191,190,
    189,151,150,
    108,237,236,
    141,123,122,
    120,175,174,
    172,143,142,
    111,221,220,
    184,127,126,
    124,139,138,
    136,187,186,
    238,115,239,
    160,183,182,
    181,211,210,
    209,163,162,
    200,132,131,
    223,222,119,
    122,221,111,
    156,148,147,
    240,115,238,
    188,136,151,
    130,233,96,
    204,196,195,
    218,133,105,
    140,124,123,
    115,137,239,
    226,111,220,
    102,145,217,
    168,160,159,
    243,108,236,
    192,152,167,
    154,237,108,
    216,157,102,
    172,144,143,
    162,223,119,
    212,180,179,
    245,101,234,
    176,120,135,
    170,104,103,
    112,173,113,
    178,107,106,
    184,128,127,
    117,181,118,
    116,185,114,
    109,189,110,
    99,193,100,
    208,164,163,
    97,197,98,
    232,201,96,
    101,205,235,
    230,119,222,
    105,213,219,
    15,0,3,
    0,1,3,
    1,2,3,
    3,4,7,
    4,5,7,
    5,6,7,
    7,8,11,
    8,9,11,
    9,10,11,
    11,12,15,
    12,13,15,
    13,14,15,
    15,3,7,
    31,16,19,
    16,17,19,
    17,18,19,
    19,20,23,
    20,21,23,
    21,22,23,
    23,24,27,
    24,25,27,
    25,26,27,
    27,28,31,
    28,29,31,
    29,30,31,
    31,19,23,
    47,32,35,
    32,33,35,
    33,34,35,
    35,36,39,
    36,37,39,
    37,38,39,
    39,40,43,
    40,41,43,
    41,42,43,
    43,44,47,
    44,45,47,
    45,46,47,
    47,35,39,
    63,48,51,
    48,49,51,
    49,50,51,
    51,52,55,
    52,53,55,
    53,54,55,
    55,56,59,
    56,57,59,
    57,58,59,
    59,60,63,
    60,61,63,
    61,62,63,
    63,51,55,
    79,64,67,
    64,65,67,
    65,66,67,
    67,68,71,
    68,69,71,
    69,70,71,
    71,72,75,
    72,73,75,
    73,74,75,
    75,76,79,
    76,77,79,
    77,78,79,
    79,67,71,
    95,80,83,
    80,81,83,
    81,82,83,
    83,84,87,
    84,85,87,
    85,86,87,
    87,88,91,
    88,89,91,
    89,90,91,
    91,92,95,
    92,93,95,
    93,94,95,
    95,83,87,
    130,96,201,
    201,200,130,
    198,97,241,
    241,128,199,
    202,98,197,
    197,196,202,
    194,99,247,
    247,204,195,
    166,100,193,
    193,192,167,
    206,101,165,
    165,164,206,
    146,102,157,
    157,156,146,
    170,103,227,
    227,144,171,
    158,104,169,
    169,168,159,
    214,105,133,
    133,132,214,
    178,106,231,
    231,212,178,
    134,107,177,
    177,176,134,
    154,108,149,
    149,148,155,
    190,109,244,
    244,152,190,
    150,110,189,
    189,188,151,
    122,111,141,
    141,140,123,
    174,112,224,
    224,120,174,
    142,113,173,
    173,172,142,
    126,114,185,
    185,184,126,
    138,115,125,
    125,124,138,
    186,116,242,
    242,136,186,
    182,117,229,
    229,160,182,
    210,118,181,
    181,180,211,
    162,119,209,
    209,208,163,
    200,215,132,
    122,121,221,
    156,155,148,
    240,125,115,
    188,187,136,
    130,129,233,
    204,203,196,
    218,225,133,
    140,139,124,
    115,138,137,
    226,141,111,
    102,146,145,
    168,183,160,
    243,149,108,
    192,191,152,
    154,153,237,
    216,228,157,
    172,171,144,
    162,161,223,
    212,211,180,
    245,165,101,
    176,175,120,
    170,169,104,
    112,174,173,
    178,177,107,
    184,199,128,
    117,182,181,
    116,186,185,
    109,190,189,
    99,194,193,
    208,207,164,
    97,198,197,
    232,246,201,
    101,206,205,
    230,209,119,
    105,214,213
};

/* textura UV */
static const GLbyte objTexdataDado[248 * 2] ={
    -5,23,
    -8,30,
    -15,35,
    -25,37,
    -104,37,
    -114,35,
    -121,30,
    -124,23,
    -124,-29,
    -121,-36,
    -114,-41,
    -104,-43,
    -25,-43,
    -15,-41,
    -8,-36,
    -5,-29,
    102,44,
    112,46,
    119,51,
    122,58,
    122,110,
    119,117,
    112,122,
    102,124,
    22,124,
    12,122,
    5,117,
    2,110,
    2,58,
    5,51,
    12,46,
    22,44,
    5,22,
    8,28,
    14,33,
    24,35,
    100,35,
    109,33,
    116,28,
    119,22,
    119,-28,
    116,-35,
    109,-39,
    100,-41,
    24,-41,
    14,-39,
    8,-35,
    5,-28,
    -120,108,
    -117,115,
    -110,119,
    -101,121,
    -25,121,
    -15,119,
    -8,115,
    -5,108,
    -5,58,
    -8,51,
    -15,46,
    -25,45,
    -101,45,
    -110,46,
    -117,51,
    -120,58,
    118,-61,
    115,-55,
    109,-50,
    99,-48,
    23,-48,
    14,-50,
    7,-55,
    4,-61,
    4,-111,
    7,-118,
    14,-122,
    23,-124,
    99,-124,
    109,-122,
    115,-118,
    118,-111,
    -102,-123,
    -112,-121,
    -118,-117,
    -121,-111,
    -121,-61,
    -118,-54,
    -112,-50,
    -102,-48,
    -27,-48,
    -18,-50,
    -11,-54,
    -8,-61,
    -8,-111,
    -11,-117,
    -18,-121,
    -27,-123,
    63,-56,
    -109,-53,
    -112,-55,
    -112,-114,
    -109,-116,
    61,29,
    -96,-58,
    -23,-59,
    -25,-57,
    63,-110,
    -103,-109,
    -100,-110,
    -96,-112,
    -21,-116,
    -18,-114,
    -26,-114,
    -25,-110,
    -23,-109,
    -21,-53,
    -26,-60,
    -18,-55,
    -100,-57,
    -103,-59,
    61,-25,
    -36,-112,
    -19,-115,
    -23,-111,
    -25,-106,
    -25,-68,
    -23,-63,
    -26,-51,
    -34,-51,
    -96,-51,
    56,-55,
    60,-59,
    61,-64,
    61,-102,
    60,-107,
    -96,-112,
    -89,-112,
    -16,-64,
    -33,-59,
    -29,-63,
    -28,-68,
    -28,-106,
    -29,-111,
    -20,-106,
    -21,-101,
    -21,-66,
    -104,-58,
    -99,-61,
    -98,-66,
    -98,-104,
    -99,-109,
    -14,-110,
    -15,-105,
    -34,-117,
    -89,-113,
    -93,-109,
    -95,-104,
    -95,-66,
    -93,-61,
    -30,-55,
    -37,-55,
    -89,-55,
    68,-26,
    64,-22,
    62,-17,
    62,21,
    64,26,
    -104,-118,
    -95,-117,
    -37,-57,
    -30,-59,
    -25,-62,
    -23,-66,
    -23,-101,
    -25,-105,
    -30,-109,
    -37,-110,
    -89,-110,
    -95,-109,
    -100,-105,
    -102,-101,
    -103,-66,
    -101,-62,
    -96,-59,
    -89,-57,
    -35,-54,
    -27,-55,
    -21,-59,
    -19,-64,
    -19,-105,
    -21,-110,
    -26,-114,
    -34,-115,
    -95,-115,
    -103,-114,
    -109,-110,
    -111,-105,
    -111,-64,
    -109,-59,
    -103,-55,
    -96,-53,
    64,-64,
    66,-59,
    -116,-58,
    -114,-64,
    -114,-105,
    53,30,
    58,26,
    59,21,
    59,-17,
    58,-22,
    -106,-61,
    -105,-66,
    -105,-101,
    70,-111,
    66,-107,
    64,-102,
    -95,-56,
    -98,-56,
    61,-112,
    65,-112,
    -28,-116,
    -24,-116,
    59,-27,
    63,-27,
    -29,-112,
    56,-111,
    -33,-115,
    -20,-61,
    -89,-57,
    -96,-55,
    53,-26,
    -106,-106,
    65,-54,
    61,-54,
    62,31,
    59,31,
    -98,-114,
    -94,-114,
    -24,-58,
    -28,-58,
    -19,-59,
    -104,-51,
    -14,-58,
    -104,-113,
    -26,-118,
    68,30,
    70,-55,
    -115,-110
};

int animacionPosFrame = 97;
static const int animacionPos[98][3] ={
    {4289, -3898, 2133},
    {4289, -3898, 2133},
    {4134, -3667, 2229},
    {3979, -3437, 2238},
    {3825, -3207, 2163},
    {3671, -2978, 2003},
    {3518, -2749, 1758},
    {3364, -2521, 1428},
    {3211, -2292, 1014},
    {3058, -2065, 515},
    {2914, -1873, 388},
    {2778, -1718, 632},
    {2642, -1562, 790},
    {2507, -1407, 863},
    {2372, -1252, 851},
    {2237, -1098, 754},
    {2102, -944, 572},
    {1968, -790, 305},
    {1827, -683, 378},
    {1687, -581, 414},
    {1546, -480, 364},
    {1421, -384, 271},
    {1359, -313, 274},
    {1298, -266, 281},
    {1239, -225, 282},
    {1178, -189, 276},
    {1113, -156, 265},
    {1047, -131, 272},
    {986, -116, 274},
    {925, -109, 271},
    {868, -106, 275},
    {819, -99, 279},
    {776, -86, 280},
    {735, -67, 278},
    {696, -42, 272},
    {656, -10, 266},
    {624, 22, 273},
    {602, 53, 276},
    {589, 86, 276},
    {583, 120, 274},
    {584, 158, 269},
    {587, 191, 274},
    {588, 216, 278},
    {587, 232, 280},
    {583, 242, 280},
    {577, 246, 280},
    {569, 245, 280},
    {558, 238, 278},
    {544, 226, 276},
    {526, 207, 271},
    {506, 189, 273},
    {490, 179, 276},
    {478, 176, 276},
    {468, 182, 276},
    {459, 195, 274},
    {452, 216, 270},
    {445, 245, 265},
    {431, 272, 265},
    {409, 294, 262},
    {376, 312, 255},
    {339, 320, 257},
    {307, 318, 260},
    {285, 317, 265},
    {275, 319, 266},
    {275, 325, 266},
    {285, 335, 263},
    {300, 342, 263},
    {315, 338, 262},
    {331, 322, 257},
    {349, 295, 250},
    {368, 275, 256},
    {384, 267, 258},
    {397, 271, 259},
    {400, 273, 260},
    {391, 272, 257},
    {378, 277, 255},
    {362, 293, 251},
    {341, 305, 253},
    {331, 313, 255},
    {327, 315, 256},
    {330, 313, 255},
    {341, 305, 253},
    {359, 294, 250},
    {371, 285, 253},
    {376, 282, 254},
    {374, 283, 254},
    {364, 290, 251},
    {349, 299, 251},
    {341, 305, 253},
    {341, 305, 253},
    {349, 300, 251},
    {360, 291, 251},
    {365, 289, 252},
    {361, 291, 251},
    {352, 297, 250},
    {350, 298, 251},
    {355, 295, 250},
    {357, 294, 250}
};

static const int animacionRot[100][3] = {
    {-537, -55, 76},
    {-609, -32, 127},
    {-642, 5, 132},
    {-676, 35, 116},
    {-728, 47, 77},
    {-773, 34, 44},
    {-798, 11, 31},
    {-817, -11, 29},
    {-835, -31, 34},
    {-859, -47, 48},
    {-929, -47, 99},
    {-983, -3, 121},
    {-1029, 36, 102},
    {-1098, 42, 51},
    {-1143, 14, 25},
    {-1172, -18, 23},
    {-1206, -44, 39},
    {-1258, -53, 77},
    {-1267, -37, 84},
    {-1268, -22, 86},
    {-1269, -9, 87},
    {-1273, 1, 87},
    {-1288, 7, 83},
    {-1302, 15, 78},
    {-1317, 19, 71},
    {-1332, 21, 64},
    {-1348, 20, 56},
    {-1363, 16, 49},
    {-1375, 10, 45},
    {-1384, 1, 42},
    {-1393, -6, 41},
    {-1401, -12, 41},
    {-1410, -17, 42},
    {-1419, -20, 45},
    {-1429, -22, 48},
    {-1441, -22, 52},
    {-1451, -20, 55},
    {-1459, -17, 58},
    {-1465, -13, 59},
    {-1470, -7, 60},
    {-1473, 0, 61},
    {-1476, 6, 61},
    {-1478, 10, 60},
    {-1480, 13, 60},
    {-1482, 14, 60},
    {-1483, 14, 59},
    {-1484, 13, 59},
    {-1486, 10, 59},
    {-1487, 6, 59},
    {-1488, 1, 59},
    {-1490, -4, 59},
    {-1492, -7, 59},
    {-1494, -8, 59},
    {-1496, -8, 60},
    {-1499, -7, 60},
    {-1503, -3, 61},
    {-1507, 1, 61},
    {-1513, 4, 60},
    {-1520, 5, 60},
    {-1528, 5, 59},
    {-1536, 2, 58},
    {-1542, -1, 57},
    {-1545, -4, 57},
    {-1547, -4, 57},
    {-1548, -3, 57},
    {-1547, 0, 56},
    {-1545, 2, 56},
    {-1541, 3, 56},
    {-1536, 2, 56},
    {-1529, 0, 56},
    {-1524, -2, 56},
    {-1520, -1, 56},
    {-1518, 0, 56},
    {-1518, 1, 56},
    {-1520, 0, 56},
    {-1523, 0, 56},
    {-1528, 0, 56},
    {-1533, 0, 55},
    {-1536, 0, 55},
    {-1537, 0, 55},
    {-1536, 0, 55},
    {-1533, 0, 55},
    {-1528, 0, 56},
    {-1525, 0, 56},
    {-1524, 0, 56},
    {-1525, 0, 56},
    {-1528, 0, 56},
    {-1532, 0, 56},
    {-1534, 0, 56},
    {-1533, 0, 56},
    {-1531, 0, 56},
    {-1528, 0, 56},
    {-1527, 0, 56},
    {-1528, 0, 56},
    {-1530, 0, 56},
    {-1531, 0, 56},
    {-1529, 0, 56},
    {-1529, 0, 56},
    {-1530, 0, 56},
    {-1529, 0, 56}
};
