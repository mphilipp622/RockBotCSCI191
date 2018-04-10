#include "LoadShader.h"

LoadShader::LoadShader()
{
    //ctor
}

LoadShader::~LoadShader()
{
    //dtor
}

void LoadShader::LoadFile(char* filename, string& str)
{
    char tmp[1024]; // one line at a time
    ifstream in(filename);

    if(!in.is_open())
    {
        cout << filename << " Does Not Exist in LoadShader::LoadFile()" << endl;
        return;
    }

    while(!in.eof())
    {
        in.getline(tmp, 1024); // read a whole line of data and store it into tmp
        str += tmp; // add the data to the string
        str += '\n'; // add an endl
    }

    cout << str << endl;

}

unsigned int LoadShader::ShaderLoad(string& source, unsigned int mode)
{
    unsigned int id;
    const char* csource;

    char error[1024];
    csource = source.c_str();

    id = glCreateShader(mode); // what kind of shader is it? That's what mode does. Fragment or Vertex shader

    glShaderSource(id, 1, &csource, NULL);

    glCompileShader(id);

    glGetShaderInfoLog(id, 1024, NULL, error); // store shader error for debugging

    cout << "Compile Status: " << error << endl; // output error

    return id;
}

void LoadShader::ShaderInit(char* vFileName, char* fFileName)
{
    string source;

    LoadFile(vFileName, source);
    vs = ShaderLoad(source, GL_VERTEX_SHADER); // vertex data is now in memory

    source = "";

    LoadFile(fFileName, source);
    fs = ShaderLoad(source, GL_FRAGMENT_SHADER); // fragment data is now in memory

    program = glCreateProgram();

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program); // similar to assembly. Link data so GPU knows what to do
}

void LoadShader::CleanUp()
{
    glDetachShader(program, vs);
    glDetachShader(program, fs);

    glDeleteShader(vs);
    glDeleteShader(fs);
    glDeleteProgram(program);
}
