#include <iostream>
#include <string>
#include <vector>
#include "test.pb.h"
#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "google/protobuf/text_format.h"

using ::google::protobuf::RepeatedField;
using ::google::protobuf::int64;

int main()
{
	Test test;
	test.add_id(10);
	test.add_id(20);
	test.add_id(30);

	std::cout<<test.id_size()<<std::endl;

	std::cout<<test.id(1)<<std::endl;

	const RepeatedField<int64>& id_vec = test.id();
	for(auto a : id_vec)
	{
		// *itr += 1000; // this will throw an compiler error. It is not mutable.
		std::cout<< "id: "<<a<<std::endl;
	}

	std::string str;
	google::protobuf::TextFormat::PrintToString(test, &str);
	std::cout<< str << std::endl;
	
	RepeatedField<int64>* mut_vec = test.mutable_id();
	
	for(auto itr = mut_vec->begin(); itr != mut_vec->end(); ++itr)
	{
		*itr += 1000; // this will throw an compiler error. It is not mutable.
		std::cout<< "id: "<<*itr<<std::endl;
	}

	std::string str2;
	google::protobuf::TextFormat::PrintToString(test, &str2);
	std::cout<< str2 << std::endl;
	

}
