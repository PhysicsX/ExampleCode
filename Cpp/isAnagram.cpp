#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>

class SolutionWithMap {
public:
bool isAnagram(std::string str1, std::string str2)
{
	if(str1.size() != str2.size())
		return false;

	std::unordered_map<char, int> map;

	for(int i=0; i<str1.size(); i++)
	{
		map[str1[i]]++;
	}


	for(int i=0; i<str2.size(); i++)
	{
	
		if(str2.find(str1[i]) == std::string::npos)
			return false;
		else
		{
		
			map[str2[i]]--;
			if(map[str2[i]] == 0) map.erase(str2[i]);
		}
	}
	// do not print map member here, if it does then size will never not be zero
	return 0 == map.size();

}
};

class SolutionWithArray {
public:
bool isAnagram(std::string s, std::string t) {
    // Return false if s and t have different sizes.
    if (s.size() != t.size()) {
        return false;
    }

    // Create an array to store the frequency of each character in s and t.
    std::array<int, 26> sCount{}, tCount{};

    // Iterate through s and t, and increment the corresponding element in sCount and tCount.
    for (int i = 0; i < s.size(); ++i) {
        ++sCount[s[i] - 'a'];
        ++tCount[t[i] - 'a'];
    }

    // Compare sCount and tCount.
    return sCount == tCount;
}
};


int main()
{

	std::string str1 ="ulasdikme";
	std::string str2 ="dikmaulas";

	std::cout<<SolutionWithMap{}.isAnagram(str1, str2)<<std::endl;
	std::cout<<SolutionWithArray{}.isAnagram(str1, str2)<<std::endl;
	
	
	std::string testStr1 {"sedutperspiciatisundeomnisistenatuserrorsitvoluptatemaccusantiumdoloremquelaudantiumtotamremaperiameaqueipsaquaeabilloinventoreveritatisetquasiarchitectobeataevitaedictasuntexplicabonemoenimipsamvoluptatemquiavoluptassitaspernaturautoditautfugitsedquiaconsequunturmagnidoloreseosquirationevoluptatemsequinesciuntnequeporroquisquamestquidoloremipsumquiadolorsitametconsecteturadipiscivelitsedquianonnumquameiusmoditemporainciduntutlaboreetdoloremagnamaliquamquaeratvoluptatemutenimadminimaveniamquisnostrumexercitationemullamcorporissuscipitlaboriosamnisiutaliquidexeacommodiconsequaturquisautemveleumiurereprehenderitquiineavoluptatevelitessequamnihilmolestiaeconsequaturvelillumquidoloremeumfugiatquovoluptasnullapariatur"};

	std::string testStr2 {"ptenduruianmcuauepisttuvmnllecdqsueanipiunuunlscdvuisoseaeeeiauotuvaoaqsiaalnnmpmasvoanprtilvrqcesmvseanuisactetrlelesilmmuodanatnremueuqlilavqattnoeromtsdanadummrauorideiuaounisuqcmieesleiapmxatvgvtrmsopqapeoihsielratpaqmiaadmurmuuatbraeoeereqtlntqtiuneuifctteaneuectinrmsnrrunlmtueiniuitbprtaqtutidropcotslcdsaiuenoeearpaoecmarssisutnaestmqbiamtmttteeotooaieivoiqevaumlnaueonilaeavndtinuxdliuomoemnulamilnmomretairivioumoqeeeaeaioaalseupiipqttoutrmdlmesiadqiemmporlirltiltqsoseiueuttoaueatoteusqumitqiotmatssqeiasuetommrrdutiseitqauumoiuodbaliqicsptiousraputtacsmpqouxarsiasvoginurdaariaputlrleoehorcequieinueqaurqareidtlivuoctsiucuitprbpaniesuuilaoutqcoulrieamemlaeeeeooisunmredgisnotgeephcutsoeitlactfiunnessiiiuedttoo"};
	

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	for(size_t i {0}; i<10000; i++)
	{
		SolutionWithMap{}.isAnagram(testStr1, testStr2);
	}
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        
	auto speedMap = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count(); 

	std::cout<<"Time difference with map = "<<speedMap<<"[ms]"<<std::endl;
	
        begin = std::chrono::steady_clock::now();

	for(size_t i {0}; i<10000; i++)
	{
		SolutionWithArray{}.isAnagram(testStr1, testStr2);
	}
        end = std::chrono::steady_clock::now();
	
	auto speedArray = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count(); 
        std::cout<<"Time difference with array = "<<speedArray<<"[ms]"<<std::endl;
	
	std::cout<<"Array is faster than map "<<speedMap/speedArray<<" times"<<std::endl;
	
	return 0;
}

