class FontUV {
    public:
        struct Glyph {
            GLfloat uvs[8]; // cada letra tiene sus UV
        };

        std::map<std::string, Glyph> atlas; // diccionario de letras (clave: "A", "Ñ", etc.)

        FontUV(int texW, int texH) {
            // ejemplo: letra 'A' en x=1, y=1, w=5, h=7
            addGlyph("A", texW, texH, 1, 0, 5, 10);
            addGlyph("B", texW, texH, 7, 0, 5, 10);
            addGlyph("C", texW, texH, 13, 0, 5, 10);
            addGlyph("D", texW, texH, 19, 0, 5, 10);
            addGlyph("E", texW, texH, 25, 0, 5, 10);
            addGlyph("F", texW, texH, 31, 0, 5, 10);
            addGlyph("G", texW, texH, 37, 0, 5, 10);
            addGlyph("H", texW, texH, 43, 0, 5, 10);
            addGlyph("I", texW, texH, 49, 0, 5, 10);
            addGlyph("J", texW, texH, 55, 0, 5, 10);
            addGlyph("K", texW, texH, 61, 0, 5, 10);
            addGlyph("L", texW, texH, 67, 0, 5, 10);
            addGlyph("M", texW, texH, 73, 0, 5, 10);
            addGlyph("N", texW, texH, 1, 10, 5, 10);
            addGlyph("Ñ", texW, texH, 79, 10, 5, 10);
            addGlyph("O", texW, texH, 7, 10, 5, 10);
            addGlyph("P", texW, texH, 13, 10, 5, 10);
            addGlyph("Q", texW, texH, 19, 10, 5, 10);
            addGlyph("R", texW, texH, 25, 10, 5, 10);
            addGlyph("S", texW, texH, 31, 10, 5, 10);
            addGlyph("T", texW, texH, 37, 10, 5, 10);
            addGlyph("U", texW, texH, 43, 10, 5, 10);
            addGlyph("V", texW, texH, 49, 10, 5, 10);
            addGlyph("W", texW, texH, 55, 10, 5, 10);
            addGlyph("X", texW, texH, 61, 10, 5, 10);
            addGlyph("Y", texW, texH, 67, 10, 5, 10);
            addGlyph("Z", texW, texH, 73, 10, 5, 10);
            addGlyph("a", texW, texH, 1, 21, 5, 10);
            addGlyph("b", texW, texH, 7, 21, 5, 10);
            addGlyph("c", texW, texH, 13, 21, 5, 10);
            addGlyph("d", texW, texH, 19, 21, 5, 10);
            addGlyph("e", texW, texH, 25, 21, 5, 10);
            addGlyph("f", texW, texH, 31, 21, 5, 10);
            addGlyph("g", texW, texH, 37, 21, 5, 10);
            addGlyph("h", texW, texH, 43, 21, 5, 10);
            addGlyph("i", texW, texH, 49, 21, 5, 10);
            addGlyph("j", texW, texH, 55, 21, 5, 10);
            addGlyph("k", texW, texH, 61, 21, 5, 10);
            addGlyph("l", texW, texH, 67, 21, 5, 10);
            addGlyph("m", texW, texH, 73, 21, 5, 10);
            addGlyph("n", texW, texH, 1, 41, 5, 10);
            addGlyph("ñ", texW, texH, 79, 41, 5, 10);
            addGlyph("o", texW, texH, 7, 41, 5, 10);
            addGlyph("p", texW, texH, 13, 41, 5, 10);
            addGlyph("q", texW, texH, 19, 41, 5, 10);
            addGlyph("r", texW, texH, 25, 41, 5, 10);
            addGlyph("s", texW, texH, 31, 41, 5, 10);
            addGlyph("t", texW, texH, 37, 41, 5, 10);
            addGlyph("u", texW, texH, 43, 41, 5, 10);
            addGlyph("v", texW, texH, 49, 41, 5, 10);
            addGlyph("w", texW, texH, 55, 41, 5, 10);
            addGlyph("x", texW, texH, 61, 41, 5, 10);
            addGlyph("y", texW, texH, 67, 41, 5, 10);
            addGlyph("z", texW, texH, 73, 41, 5, 10);
            addGlyph("!", texW, texH, 36, 1, 5, 10);
            // seguís agregando todas las que necesites...
        }

        const GLfloat* getUV(const std::string& c) {
            return atlas[c].uvs;
        }

    private:
        void addGlyph(const std::string& c, int texW, int texH, int x, int y, int w, int h) {
            GLfloat u1 = (GLfloat)x / texW;
            GLfloat u2 = (GLfloat)(x + w) / texW;
            GLfloat v1 = (GLfloat)y / texH;
            GLfloat v2 = (GLfloat)(y + h) / texH;

            Glyph g;
            g.uvs[0] = u1; g.uvs[1] = v1; // top-left
            g.uvs[2] = u2; g.uvs[3] = v1; // top-right
            g.uvs[4] = u1; g.uvs[5] = v2; // bottom-left
            g.uvs[6] = u2; g.uvs[7] = v2; // bottom-right

            atlas[c] = g;
        }
};

FontUV font(128, 128);