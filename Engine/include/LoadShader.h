#define GLEW_STATIC
#ifndef LOADSHADER_H
#define LOADSHADER_H


#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class LoadShader
{
    public:
        LoadShader();
        virtual ~LoadShader();

        void LoadFile(char*, string&);
        unsigned int vs, fs, program;
        unsigned int ShaderLoad(string&, unsigned int);

        void ShaderInit(char*, char*);
        void CleanUp();

    protected:

    private:
};

#endif // LOADSHADER_H
