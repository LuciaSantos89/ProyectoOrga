#ifndef TDAFILE_H
#define TDAFILE_H


#include <string>
#include <fstream>

using namespace::std;

class TDAFile
{
private:
    fstream file;
public:
    TDAFile();
    ~TDAFile();
    void Init();
    bool open(string,ios_base::openmode);//open the file
    int read(char*,int);//logical variable to read
    int write(const char*,int);//logical variable to write
    bool seek(int);//move the pointer to other site
    bool seek(int,ios_base::seekdir);//move the pointer to other site
    int tell();
    bool flush();//empty the buffers
    bool close();//close the file
    bool isOpen();//file is Open
    bool isOk();
    bool boF();
    bool eoF();//end of file


};

#endif
