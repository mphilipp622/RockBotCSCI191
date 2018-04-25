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
    char tmp[1024];

    ifstream in(filename);

    if(!in.is_open()) {

        cout<<"File cannot be open"<<endl;
        return;
    }

    while(!in.eof()){

        in.getline(tmp,1024);
        str +=tmp;
        str +='\n';
    }
    cout<< str<<endl;

}

unsigned int LoadShader::ShaderLoad(string& source, unsigned int mode)
{
    unsigned int id;
      const char*  csource;
      char error[1024];

     id = glCreateShader(mode);
      csource = source.c_str();

       glShaderSource(id,1,&csource, NULL);
       glCompileShader(id);

       glGetShaderInfoLog(id,1024,NULL, error);

       cout<<"Compile Statu \n"<< error<<endl;

      return id;
}

void LoadShader::ShaderInit(char* vFileName, char* fFileName)
{
    string source;

     LoadFile(vFileName,source);
     vs = ShaderLoad(source,GL_VERTEX_SHADER);

     source ="";

    LoadFile(fFileName,source);
     fs = ShaderLoad(source,GL_FRAGMENT_SHADER);

     program =glCreateProgram();

     glAttachShader(program,vs);
     glAttachShader(program,fs);

     glLinkProgram(program);
     //glUseProgram(program);
}

void LoadShader::CleanUp()
{
    glDetachShader(program,vs);
  glDetachShader(program,fs);
  glDeleteShader(vs);
  glDeleteShader(fs);
  glDeleteProgram(program);
}
