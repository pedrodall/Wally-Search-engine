#include "lib/server_http.hpp" //Chamando pacotes do Simple Web Server
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>

using namespace std;
using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

vector<vector<string>> vinte(vector<string> lista){
	vector<vector<string>> c;
	for(int i=0;i<lista.size();i++){
		if((i)%20==0){
			c.push_back({});
		}
		vector<string> *a = &c[c.size()-1];
		a->push_back(lista[i]);
	} 
	return c;
}

struct Node {
	int doc_size;
	vector<int>* docs; 
	Node* pChild[128];
	Node() {
		for (int i = 0; i < 128; i++) {
			pChild[i] = nullptr;
		}
		doc_size = 0;
	}
	void tamanho(int size) {
		docs = new vector<int>[size];
		doc_size = size;
	}
};

class Trie
{
    public: 

    Node *pRoot = new Node;

    Trie() 
    {
		ifstream serializado ("Trie.txt");
        clock_t t0, t;
        t0 = clock();
		deserialize(serializado);
        t = clock() - t0;
        cout << (float) t/CLOCKS_PER_SEC << endl;
        cout << "fim da deserializacao" << endl;
		serializado.close();
	}

    void print()
    {
        cout << "#################################" << endl;
        for(int i = 0; i < 128; i++)
        {
            if(pRoot->pChild[i])
            {
                if(((pRoot->pChild[i])->doc_size) == 1)
                {
                    cout << ((pRoot->pChild[i])->docs)[0][0]<< endl;
                }
            }
        }
    }

        bool check_number(string str) 
    {
        for (int i = 0; i < str.length(); i++)
        {
            if (isdigit(str[i]) == false) return false;
        }
            return true;
    }

    vector<string> openT(vector<string> titulos, vector<int> postitulos)
    {
        vector<string> texto;
        string n;
        bool check = false;

        cout << "Numero de resultados esultados: " << titulos.size() << endl;
        for (int i = 0; i < titulos.size(); i++)
        {
            cout << "["<< i << "]"<<titulos[i] << endl;
            if(i % 20 == 19)
            {
                check = true;
                cout<< "Aperte: "<< endl;
                cout << endl;
                cout<< "[X] Qualquer tecla para passar para a proxima pagina" << endl;
                cout << "[X] O numero do documento para vizualizar ele" << endl;
                cout << "[X] <quit> para uma nova pesquisa"<< endl;

                cin >> n;
                if(check_number(n)) break;
                else if (n == "quit")
                {
                    return texto;
                }
                
            }
        }

        if (titulos.size() == 0)
        {
            cout << "Nenhuma pesquisa encontrada" << endl;
            return texto;
        }

        if (check == false)
        {
            cout<< "Aperte: "<< endl;
            cout << endl;
            cout<< "[X] Qualquer tecla para passar para a proxima pagina" << endl;
            cout << "[X] O numero do documento para vizualizar ele" << endl;
            cout << "[X] <quit> para uma nova pesquisa"<< endl;
            cin >> n;
            if(!check_number(n)) return texto;
        }
        

        string line;
        string a1 = "texto/txtlimpo_";
        string a2 = to_string(postitulos[stoi(n)]/10000);
        string a3 =".txt";
        string result = a1+a2+a3;
        ifstream file(result);
        int j = postitulos[stoi(n)];
        int i = j/10000;
        int k = 0;
        while (k != j - i * 10000)
        {
            getline(file,line);
            if (line == "</doc>")
            {
                k ++;
            }
        
        }
        getline(file,line);
        cout << line << endl;
        texto.push_back(line);

        while (line != "ENDOFARTICLE.")
        {
            getline(file,line);
            cout << line << endl;
            texto.push_back(line);
        }

        return texto;

    }


    void deserialize(ifstream& serializado) 
    {
		Node* pNode = pRoot;
		char letter;
		string number = "";
		vector<Node*> pNodes;
		int loading = 0;
		int i;
        bool k = false;

		while (serializado.get(letter)) 
        {

            if(k == true)
            {
                if(letter == ';')
                {
                    (*(pNode->docs + i)).push_back(stoi(number));
                    number = "";
                }
                else if(letter == '|')
                {
                    k = false;
                    i++;
                    number = "";
                }
                else number = number + letter;

            }
			else if (letter == ',') 
            {
				//pNode->docs.push_back(stoi(number));
				(*(pNode->docs + i)).push_back(stoi(number));
				//!i++;
				number = "";
                k = true;
			}
			else if (letter == '.') 
            {
				pNodes.push_back(pNode);
				pNode->pChild[stoi(number)] = new Node;
				pNode = pNode->pChild[stoi(number)];
				number = "";
			}
			else if (letter == '-') 
            {
				pNode = pNodes.back();
				if (pNode == pRoot) 
                {
					loading++;
					//cout << loading << endl;	
				}
				pNodes.pop_back();
				number = "";
			}
			else if (letter == '+') 
            {
				i = 0;
				pNode->tamanho(stoi(number));
				number = "";
			}
			else number = number + letter;
		}
	}

    void search(string plvr)
    {
        clock_t t0, t;
        string more;
        Node* pNode = pRoot;
        vector<int> consultas;
        string line;
        int j = 0;
        t0 = clock();
        
        for(int i = 0; i< plvr.size();i++)
        {
            if ((pNode->pChild)[ (int) plvr[i] ])
            {
                pNode = pNode->pChild[(int) plvr[i]];
            }
            else
            {
                return;
            }    
        }

        t = clock() - t0;
        cout << (float) t/CLOCKS_PER_SEC << endl;

        for(int i = 0; i < pNode->doc_size; i++)
        {
            consultas.push_back(pNode->docs[i][0]);
        }

        ifstream file ("titulos.txt");

        for(int i = 0; i < pNode->doc_size; i++)
        {
            
            while(j < consultas[i])
            {
                getline(file,line);
                j++;
            }
            getline(file,line);
            cout << "["<< j << "]"<<line << endl;
            if(i % 20 == 19)
            {
                cout<< "########### ver mais? ###########"<< endl;
                cin >> more;
                cout << "#################################" << endl;
                if(more != "s")
                {
                    return;
                }
            }
            
        }

        cout << "########### end ###########" << endl;
    }



    int search(string plvr, vector<vector<int>*> * cons, vector<int>* cons_size)
    {
        Node* pNode = pRoot;

        for(int i = 0; i< plvr.size();i++)
        {
            if ((pNode->pChild)[ (int) plvr[i] ])
            {
                pNode = pNode->pChild[(int) plvr[i]];
            }
            else
            {
                return 1;
            }    
        }

        (*cons).push_back(pNode->docs);
        (*cons_size).push_back(pNode->doc_size);

        return 0;
    }

    vector<string> split_search(string str,  vector<int> &postextos)
    {
        clock_t t0, t;
        vector<vector<int>*> * cons, *resul;
        vector<int>* cons_size;
        cons = new vector<vector<int>*>;
        cons_size = new vector<int>;
        postextos.clear();
        string line;
        int j = 0;
        int ini = 0;
        int f = 0;
        t0 = clock();
        int z = 0;

        for (f = 0; f < str.length(); f++)
        {

            if (str[f] == ' ')
            {
                z += search(str.substr(ini,f-ini),cons,cons_size);

                ini = f+1;
            }
        }

        z += search(str.substr(ini,f-ini),cons,cons_size);

        if(z >= 1) return {};

        t = clock() - t0;
        cout<< "Tempo de busca: ";
        cout << (float) t/CLOCKS_PER_SEC << endl;

        resul = new vector<vector<int>*>;


        
            
            for (int i = 0; i < (*cons_size)[0] ; i++)
            {
                resul->push_back(((*cons)[0]+i));



            }
            cout << endl;

            if((*cons).size() > 1)
            {

                for (int i = 1; i < (*cons).size() ; i++)
                {
                    intersec(resul,(*cons)[i], (*cons_size)[i]);
                }

                t = clock() - t0;
                cout<< "Tempo de busca booleana: ";
                cout << (float) t/CLOCKS_PER_SEC << endl;
            }

            if( (*resul)[0]->size() == 0 ) { return {}; }

            ifstream file ("titulos.txt");
            vector<string> titulos;

            for (int i = 0; i < resul->size() ; i++)
            {

                while(j < (*(*resul)[i])[0])
                {
                    getline(file,line);
                    j++;
                }
                getline(file,line);
                titulos.push_back(line);
                postextos.push_back(j);
                j++;
                
            }

            return titulos;

            
        

    }

void intersec(vector<vector<int>*>* resul,vector<int>* cons, int cons_size)
{
     int k = resul->size() - 1;

    for (int i = cons_size - 1; i > -1; i--)
    {
        if(k >= 0)
        {
            while ((*(cons+i))[0] < (*(*resul)[k])[0])
            {
                (*resul).erase(resul->begin()+k);     
                k--;
                if(k < 0) break;
            }
            if ((*(cons+i))[0] == (*(*resul)[k])[0]) k--;
        }
    }
    for (int i = k; i > -1; i--)
    {
        (*resul).erase(resul->begin()+i);  
    }
    

    return;  
}
}trie;


int main(){

	HttpServer server;
	server.config.port = 8080; 


	server.resource["^/query$"]["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request){

		auto query_fields = request->parse_query_string(); 

		auto it = query_fields.find("text"); 
		cout << it->second << endl; 

		vector<int> pos;
    	vector<string> pesquisas = trie.split_search(it->second, pos);
		vector<vector<string>> l= vinte(pesquisas);		
		string vazio = "Wally não encontrou nada, mas você pode usar o wikipédia de verdade! <a href= \'https://en.wikipedia.org/wiki/"+it->second+"\'> Clique aqui</a>";	
		stringstream stream;
		stream<<"{\"res\":\""<<pesquisas.size()<<" pesquisas encontradas."<<"\",\n";
		stream<<"\"pesquisas\":[";
		for(int i=0;i<pesquisas.size()-1;i++){
			stream<<"[\""<<pesquisas[i]<<"\"],";
		}
		stream<<"[\""<<pesquisas[pesquisas.size()-1]<<"\"]],\n";
		stream<<"\"pag\":"<<l.size()<<"}";

		cout << stream.str()<<endl;
		response->write(stream);

	};
  	server.default_resource["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
		auto path = "./web/"+request->path; 
		SimpleWeb::CaseInsensitiveMultimap header;
		std::ifstream ifs(path, ifstream::in | ios::binary | ios::ate); 
		auto length = ifs.tellg();
       	ifs.seekg(0, ios::beg);
       	stringstream stream;   
       	stream << ifs.rdbuf(); 
        header.emplace("Content-Length", to_string(length));
        response->write(header);
        response->write(stream.str().c_str(), length); 
    };













//função para lidar com erros (não necessário)

    server.on_error = [](shared_ptr<HttpServer::Request> /*request*/, const SimpleWeb::error_code & /*ec*/) {
	};


    thread server_thread([&server]() {
        // Start server
        server.start();
    });

    // Wait for server to start so that the client can connect
    this_thread::sleep_for(chrono::seconds(1));

	server_thread.join();
}
