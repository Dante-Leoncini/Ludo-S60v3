// MACROS
#define objVerticesFicha    145
#define objFacesFicha       272

/** Vertices for the Ficha object. */
static const GLshort objVertexdataFicha[145 * 3]={
    0, -5000, -165,
    -116, -5000, -116,
    -165, -5000, 0,
    -116, -5000, 116,
    0, -5000, 165,
    116, -5000, 116,
    165, -5000, 0,
    116, -5000, -116,
    -63, -5000, -152,
    -152, -5000, -63,
    -152, -5000, 63,
    -63, -5000, 152,
    63, -5000, 152,
    152, -5000, 63,
    152, -5000, -63,
    63, -5000, -152,
    -19, -4752, -46,
    -36, -4752, -36,
    -46, -4752, -19,
    -50, -4752, 0,
    -46, -4752, 19,
    -36, -4752, 36,
    -19, -4752, 46,
    0, -4752, 50,
    19, -4752, 46,
    36, -4752, 36,
    46, -4752, 19,
    50, -4752, 0,
    46, -4752, -19,
    36, -4752, -36,
    19, -4752, -46,
    0, -4556, -77,
    0, -4592, -100,
    0, -4675, -100,
    0, -4733, -46,
    16, -4533, -38,
    29, -4556, -71,
    38, -4592, -93,
    42, -4633, -100,
    38, -4675, -93,
    29, -4710, -71,
    18, -4733, -43,
    29, -4533, -29,
    54, -4556, -54,
    71, -4592, -71,
    77, -4633, -77,
    71, -4675, -71,
    54, -4710, -54,
    33, -4733, -33,
    38, -4533, -16,
    71, -4556, -29,
    93, -4592, -38,
    100, -4633, -42,
    93, -4675, -38,
    71, -4710, -29,
    43, -4733, -18,
    42, -4533, 0,
    77, -4556, 0,
    100, -4592, 0,
    109, -4633, 0,
    100, -4675, 0,
    77, -4710, 0,
    46, -4733, 0,
    38, -4533, 16,
    71, -4556, 29,
    93, -4592, 38,
    100, -4633, 42,
    93, -4675, 38,
    71, -4710, 29,
    43, -4733, 18,
    29, -4533, 29,
    54, -4556, 54,
    71, -4592, 71,
    77, -4633, 77,
    71, -4675, 71,
    54, -4710, 54,
    33, -4733, 33,
    16, -4533, 38,
    29, -4556, 71,
    38, -4592, 93,
    42, -4633, 100,
    38, -4675, 93,
    29, -4710, 71,
    18, -4733, 43,
    0, -4525, 0,
    0, -4533, 42,
    0, -4556, 77,
    0, -4592, 100,
    0, -4633, 109,
    0, -4675, 100,
    0, -4710, 77,
    0, -4733, 46,
    -16, -4533, 38,
    -29, -4556, 71,
    -38, -4592, 93,
    -42, -4633, 100,
    -38, -4675, 93,
    -29, -4710, 71,
    -18, -4733, 43,
    -29, -4533, 29,
    -54, -4556, 54,
    -71, -4592, 71,
    -77, -4633, 77,
    -71, -4675, 71,
    -54, -4710, 54,
    -33, -4733, 33,
    0, -4752, -50,
    -38, -4533, 16,
    -71, -4556, 29,
    -93, -4592, 38,
    -100, -4633, 42,
    -93, -4675, 38,
    -71, -4710, 29,
    -43, -4733, 18,
    -42, -4533, 0,
    -77, -4556, 0,
    -100, -4592, 0,
    -109, -4633, 0,
    -100, -4675, 0,
    -77, -4710, 0,
    -46, -4733, 0,
    -38, -4533, -16,
    -71, -4556, -29,
    -93, -4592, -38,
    -100, -4633, -42,
    -93, -4675, -38,
    -71, -4710, -29,
    -43, -4733, -18,
    -29, -4533, -29,
    -54, -4556, -54,
    -71, -4592, -71,
    -77, -4633, -77,
    -71, -4675, -71,
    -54, -4710, -54,
    -33, -4733, -33,
    -16, -4533, -38,
    -29, -4556, -71,
    -38, -4592, -93,
    -42, -4633, -100,
    -38, -4675, -93,
    -29, -4710, -71,
    -18, -4733, -43,
    0, -4533, -42,
    0, -4633, -109,
    0, -4710, -77
};

/* Define normals for the cube */
static const GLbyte objNormaldataFicha[145 * 3]={
    0,53,-115,
    -82,53,-82,
    -115,53,0,
    -82,53,82,
    0,53,115,
    82,53,82,
    115,53,0,
    82,53,-82,
    -44,53,-107,
    -107,53,-44,
    -107,53,44,
    -44,53,107,
    44,53,107,
    107,53,44,
    107,53,-44,
    44,53,-107,
    -46,40,-111,
    -85,40,-85,
    -111,40,-46,
    -120,40,0,
    -111,40,46,
    -85,40,85,
    -46,40,111,
    0,40,120,
    46,40,111,
    85,40,85,
    111,40,46,
    120,40,0,
    111,40,-46,
    85,40,-85,
    46,40,-111,
    0,88,-91,
    0,48,-118,
    0,-48,-118,
    0,-48,-118,
    20,116,-47,
    35,88,-84,
    45,48,-109,
    49,0,-117,
    45,-48,-109,
    36,-86,-86,
    45,-48,-109,
    36,116,-36,
    65,88,-65,
    83,48,-83,
    90,0,-90,
    83,-48,-83,
    66,-86,-66,
    83,-48,-83,
    47,116,-20,
    84,88,-35,
    109,48,-45,
    117,0,-49,
    109,-48,-45,
    86,-86,-36,
    109,-48,-45,
    51,116,0,
    91,88,0,
    118,48,0,
    127,0,0,
    118,-48,0,
    94,-86,0,
    118,-48,0,
    47,116,20,
    84,88,35,
    109,48,45,
    117,0,49,
    109,-48,45,
    86,-86,36,
    109,-48,45,
    36,116,36,
    65,88,65,
    83,48,83,
    90,0,90,
    83,-48,83,
    66,-86,66,
    83,-48,83,
    20,116,47,
    35,88,84,
    45,48,109,
    49,0,117,
    45,-48,109,
    36,-86,86,
    45,-48,109,
    0,127,0,
    0,116,51,
    0,88,91,
    0,48,118,
    0,0,127,
    0,-48,118,
    0,-86,94,
    0,-48,118,
    -20,116,47,
    -35,88,84,
    -45,48,109,
    -49,0,117,
    -45,-48,109,
    -36,-86,86,
    -45,-48,109,
    -36,116,36,
    -65,88,65,
    -83,48,83,
    -90,0,90,
    -83,-48,83,
    -66,-86,66,
    -83,-48,83,
    0,40,-120,
    -47,116,20,
    -84,88,35,
    -109,48,45,
    -117,0,49,
    -109,-48,45,
    -86,-86,36,
    -109,-48,45,
    -51,116,0,
    -91,88,0,
    -118,48,0,
    -127,0,0,
    -118,-48,0,
    -94,-86,0,
    -118,-48,0,
    -47,116,-20,
    -84,88,-35,
    -109,48,-45,
    -117,0,-49,
    -109,-48,-45,
    -86,-86,-36,
    -109,-48,-45,
    -36,116,-36,
    -65,88,-65,
    -83,48,-83,
    -90,0,-90,
    -83,-48,-83,
    -66,-86,-66,
    -83,-48,-83,
    -20,116,-47,
    -35,88,-84,
    -45,48,-109,
    -49,0,-117,
    -45,-48,-109,
    -36,-86,-86,
    -45,-48,-109,
    0,116,-51,
    0,0,-127,
    0,-86,-94
};

/** Indices to the Ficha object vertices. */
static const GLushort objFacedataFicha[272 * 3]={
    8,106,0,
    14,29,28,
    15,106,30,
    12,25,24,
    9,19,18,
    13,25,5,
    10,19,2,
    11,23,22,
    8,17,16,
    12,23,4,
    9,17,1,
    10,21,20,
    14,27,6,
    11,21,3,
    13,27,26,
    15,29,7,
    34,40,41,
    33,38,39,
    31,37,32,
    142,84,35,
    28,48,55,
    144,39,40,
    32,38,143,
    31,35,36,
    28,62,27,
    39,47,40,
    37,45,38,
    36,42,43,
    40,48,41,
    39,45,46,
    37,43,44,
    35,84,42,
    44,52,45,
    42,50,43,
    48,54,55,
    45,53,46,
    44,50,51,
    42,84,49,
    26,62,69,
    46,54,47,
    54,62,55,
    52,60,53,
    50,58,51,
    49,84,56,
    26,76,25,
    54,60,61,
    52,58,59,
    49,57,50,
    58,64,65,
    56,84,63,
    24,76,83,
    60,68,61,
    58,66,59,
    57,63,64,
    62,68,69,
    60,66,67,
    24,91,23,
    67,75,68,
    65,73,66,
    63,71,64,
    68,76,69,
    66,74,67,
    65,71,72,
    63,84,70,
    71,77,78,
    76,82,83,
    73,81,74,
    71,79,72,
    70,84,77,
    22,91,98,
    75,81,82,
    73,79,80,
    82,91,83,
    80,89,81,
    79,86,87,
    77,84,85,
    22,105,21,
    81,90,82,
    80,87,88,
    78,85,86,
    85,84,92,
    20,105,113,
    89,97,90,
    87,95,88,
    85,93,86,
    91,97,98,
    89,95,96,
    86,94,87,
    96,104,97,
    95,101,102,
    93,99,100,
    97,105,98,
    95,103,96,
    94,100,101,
    92,84,99,
    30,34,41,
    105,112,113,
    102,111,103,
    100,109,101,
    99,84,107,
    16,34,106,
    104,111,112,
    102,109,110,
    100,107,108,
    111,117,118,
    109,115,116,
    107,84,114,
    20,120,19,
    111,119,112,
    109,117,110,
    107,115,108,
    112,120,113,
    18,120,127,
    119,125,126,
    116,124,117,
    115,121,122,
    120,126,127,
    118,124,125,
    115,123,116,
    114,84,121,
    123,131,124,
    122,128,129,
    126,134,127,
    125,131,132,
    122,130,123,
    121,84,128,
    18,134,17,
    126,132,133,
    134,140,141,
    131,139,132,
    129,137,130,
    128,84,135,
    16,134,141,
    132,140,133,
    131,137,138,
    128,136,129,
    137,31,32,
    135,84,142,
    30,48,29,
    139,144,140,
    138,32,143,
    135,31,136,
    140,34,141,
    138,33,139,
    8,16,106,
    14,7,29,
    15,0,106,
    12,5,25,
    9,2,19,
    13,26,25,
    10,20,19,
    11,4,23,
    8,1,17,
    12,24,23,
    9,18,17,
    10,3,21,
    14,28,27,
    11,22,21,
    13,6,27,
    15,30,29,
    34,144,40,
    33,143,38,
    31,36,37,
    28,29,48,
    144,33,39,
    32,37,38,
    31,142,35,
    28,55,62,
    39,46,47,
    37,44,45,
    36,35,42,
    40,47,48,
    39,38,45,
    37,36,43,
    44,51,52,
    42,49,50,
    48,47,54,
    45,52,53,
    44,43,50,
    26,27,62,
    46,53,54,
    54,61,62,
    52,59,60,
    50,57,58,
    26,69,76,
    54,53,60,
    52,51,58,
    49,56,57,
    58,57,64,
    24,25,76,
    60,67,68,
    58,65,66,
    57,56,63,
    62,61,68,
    60,59,66,
    24,83,91,
    67,74,75,
    65,72,73,
    63,70,71,
    68,75,76,
    66,73,74,
    65,64,71,
    71,70,77,
    76,75,82,
    73,80,81,
    71,78,79,
    22,23,91,
    75,74,81,
    73,72,79,
    82,90,91,
    80,88,89,
    79,78,86,
    22,98,105,
    81,89,90,
    80,79,87,
    78,77,85,
    20,21,105,
    89,96,97,
    87,94,95,
    85,92,93,
    91,90,97,
    89,88,95,
    86,93,94,
    96,103,104,
    95,94,101,
    93,92,99,
    97,104,105,
    95,102,103,
    94,93,100,
    30,106,34,
    105,104,112,
    102,110,111,
    100,108,109,
    16,141,34,
    104,103,111,
    102,101,109,
    100,99,107,
    111,110,117,
    109,108,115,
    20,113,120,
    111,118,119,
    109,116,117,
    107,114,115,
    112,119,120,
    18,19,120,
    119,118,125,
    116,123,124,
    115,114,121,
    120,119,126,
    118,117,124,
    115,122,123,
    123,130,131,
    122,121,128,
    126,133,134,
    125,124,131,
    122,129,130,
    18,127,134,
    126,125,132,
    134,133,140,
    131,138,139,
    129,136,137,
    16,17,134,
    132,139,140,
    131,130,137,
    128,135,136,
    137,136,31,
    30,41,48,
    139,33,144,
    138,137,32,
    135,142,31,
    140,144,34,
    138,143,33
};