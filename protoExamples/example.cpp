#include <iostream>
#include "example.pb.h"
#include <fstream>      // std::filebuf

#include <chrono>
#include <thread> 
int main()
{

    /// serialize to bytearray

    Person per;
    per.set_id(5000);
    per.set_number(5000);
    per.set_anotherid(5000);
    per.set_aid(5000);
    per.set_bid(5000);
    per.set_cid(5000);
    per.set_did(5000);    
    per.set_eid(5000);    
    per.set_fid(5000);    
    per.set_gid(5000);    
    //per.set_name("MadamCurie");
    //gper.clear_name();
    //std::cout<<per.name();
    endl(std::cout);
    size_t size = per.ByteSizeLong();
    std::cout<<"size bytes "<<size<<std::endl;
    void *buffer = malloc(size);
    bool flag = per.SerializeToArray(buffer, size);
    if(flag == false)
        std::cout<<"serialize problem"<<std::endl;

    Person per3;

    per3.ParseFromArray(buffer,size);
    endl(std::cout);   
    std::cout<<"id "<<per3.id();
    endl(std::cout);
    std::cout<<"id "<<per3.number();
    endl(std::cout);
    std::cout<<"id "<<per3.anotherid();




    //serialize to string

    std::string str = per.SerializeAsString();

    uint32_t var = 5000;
    
    std::cout<<"var size " <<sizeof(var)*10; 
    endl(std::cout);
    std::cout<<"serialized string size " <<str.size();
    endl(std::cout);
    std::cout<<"serialized string " <<str;


    Person per2;

    per2.ParseFromString(str);
    endl(std::cout);   
    std::cout<<"id "<<per2.id();
    endl(std::cout);
    std::cout<<"id "<<per2.number();
    endl(std::cout);
    std::cout<<"id "<<per2.anotherid();


    // file example

    Person file;
    file.set_number(321);
    std::string filename = "test.txt";
    std::fstream output(filename, std::ios::out | std::ios::trunc | std::ios::binary);
    if(!file.SerializeToOstream(&output))
    {
        std::cout<<"failed to write a file"<<std::endl;
    }
    output.close();

    
    endl(std::cout);
    Person file2;
    std::fstream input(filename, std::ios::in | std::ios::binary);

    if (!input) {
         std::cout << ": File not found." << std::endl;
    }

    if(!file2.ParseFromIstream(&input))
    {
        std::cout<<"failed to read a file"<<std::endl;
    }
    std::cout<<"number from file "<<file2.number()<<std::endl;





    return 0;
}