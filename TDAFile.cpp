#include "TDAFile.h"

TDAFile::TDAFile(){
}

void TDAFile::Init(){
}

TDAFile::~TDAFile(){
}

bool TDAFile::open(string fn, ios_base::openmode mode){
	this->file.open(fn.c_str(),mode);
	if(this->file.is_open()){
		return true;
	}
	return false;
}

int TDAFile::read(char* buffer, int s){
	if(!this->file.is_open()){
		return -1;
	}
	this->file.read(buffer,s);
	return 0;
}

int TDAFile::write(const char* buffer, int s){
	if(!this->file.is_open()){
		return -1;
	}
	this->file.write(buffer,s);
	return 0;
}

bool TDAFile::seek(int p){
	if(!this->file.is_open()){
		return false;
	}
	this->file.seekg(0, ios_base::end);
	int a = file.tellg();
	if(p>a){
		return false;
	}
	this->file.seekg(p);
	this->file.seekp(p);
	return true;
}

bool TDAFile::seek(int p,ios_base::seekdir dir){
    if(!this->file.is_open()){
        return false;
    }
    this->file.seekg(0, ios_base::end);
    int a = file.tellg();
    if(p>a){
        return false;
    }
    this->file.seekg(p,dir);
    this->file.seekp(p,dir);
    return true;
}

int TDAFile::tell(){
	if(!this->file.is_open()){
		return -1;
	}
	int a=this->file.tellg();
	int b=this->file.tellp();
	if(a==b){
		return b;
	}
	else{
		this->file.seekg(b);
		this->file.seekp(b);
		return b;
	}
}

bool TDAFile::flush(){
	this->file.flush();
	if(this->file.rdstate()!= 0){
		return false;
	}
	return true;
}

bool TDAFile::close(){
	this->file.close();
	if(this->file.rdstate()!= 0){
		return false;
	}
	return true;
}

bool TDAFile::isOpen(){
	if(this->file.is_open()){
		return true;
	}
	return false;
}

bool TDAFile::isOk(){
	if(this->file.good()){
		return true;
	}
	return false;
}

bool TDAFile::eoF(){
	if(this->file.eof()){
		return true;
	}
	return false;
}
