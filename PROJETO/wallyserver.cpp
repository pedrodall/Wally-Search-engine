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

//funções para testar como lidar com um vetor de strings como a resposta da pesquisa:
//vector<string> lista(string a){
//	vector<string> lista;
//	for(int i =0;i<111;i++){
//		int x=i;
//		string stri= to_string(x);  
//		lista.push_back(stri+a);
//	}
//	return lista;
//}
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
        //Montamos nossa arvore com o arquivo serializado 
        //assim que a trie é criada
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


    //Nossa função de desializar vai receber o arquivo em sua forma comprimida
    //e montara a arvore baseado nas regras de deserializaçao que foram definidas em postrie.cpp
    void deserialize(ifstream& serializado) 
    {
        Node* pNode = pRoot;
        char letter;
        string number = "";
        vector<Node*> pNodes;
        int loading = 0;
        int i;
        bool k = false;
        //iteramos por cada letra do nosso arquivo e dependendo do char
        //uma certa regra sera aplicada
        while (serializado.get(letter)) 
        {
            //cout << letter << endl;
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



    void search(string plvr, vector<vector<int>*> * cons, vector<int>* cons_size)
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
                return;
            }    
        }

        (*cons).push_back(pNode->docs);
        (*cons_size).push_back(pNode->doc_size);
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

        for (f = 0; f < str.length(); f++)
        {
            //cout << str[f]<< f << endl;
            if (str[f] == ' ')
            {
                search(str.substr(ini,f-ini),cons,cons_size);
                //cout << f;
                ini = f+1;
            }
        }

        search(str.substr(ini,f-ini),cons,cons_size);

        t = clock() - t0;
        cout<< "Tempo de busca: ";
        cout << (float) t/CLOCKS_PER_SEC << endl;

        resul = new vector<vector<int>*>;


        
            
            for (int i = 0; i < (*cons_size)[0] ; i++)
            {
                resul->push_back(((*cons)[0]+i));
                //cout << (*((*cons)[0]+i))[0] << ",";


            }
            cout << endl;

            if((*cons).size() > 1)
            {
                // for (int i = 0; i < (*cons_size)[1] ; i++)
                // {
                //     cout << (*((*cons)[1]+i))[0] << ",";

                // }
                // cout << endl;
                for (int i = 1; i < (*cons).size() ; i++)
                {
                    intersec(resul,(*cons)[i], (*cons_size)[i]);
                }

                t = clock() - t0;
                cout<< "Tempo de busca booleana: ";
                cout << (float) t/CLOCKS_PER_SEC << endl;
            }

            ifstream file ("titulos.txt");
            vector<string> titulos;

            for (int i = 0; i < resul->size() ; i++)
            {
                //cout << (*(*resul)[i])[0] << ",";
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
}
trie;
int main(){

	HttpServer server;
	server.config.port = 8080; //porta do servidor será localhost/8080

	//função que recebe query do tipo localhost:8080/query?text={text}
	server.resource["^/query$"]["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request){
		//Trecho do código para obter a query (consulta)
		auto query_fields = request->parse_query_string(); 

		//Recebe o conteúdo de "entrada" (request é o pedido do user pro server)
		auto it = query_fields.find("text"); // Obtem o texto do conteudo
		cout << it->second << endl; //o it second é o valor q aparece em {text} la em cima
		//A resposta para o servidor vai ser um JSON do formato
		//{"res": "O seu projeto final vai ser incrível, [texto]!"}	
		//JSON
		//resultado[]=pesquisadopedro(it->second)
		// {"atributo1":"valor1",
		//	"atributo2": {"sub-atributo": "valor2"}} 
		vector<int> pos;
    	vector<string> pesquisas = trie.split_search(it->second, pos);
		vector<vector<string>> l= vinte(pesquisas);		
		string vazio = "Wally não encontrou nada, mas você pode usar o wikipédia de verdade! <a href= \'https://en.wikipedia.org/wiki/"+it->second+"\'> Clique aqui</a>";	
		//img button é só um texto q dps a gente lida no javascript pra conseguirmos interpretar
		stringstream stream;
		//stream << "{\"res\":\" Não conseguimos a busca para " << it->second << "..." << img_button << "\",\n"; 
		//stream<< "{\"teste0\":\""<<pesquisas[0]<<"\",\n";
		//for(int i=1;i<pesquisas.size();i++){
		//    stream << "\"teste"<<i<<"\":\""<< pesquisas[i]<<"\",\n";
		//}
		//stream << "\"teste"<<pesquisas.size()-1<<"\":\""<<pesquisas[pesquisas.size()-1]<<"\"}";
		
		stream<<"{\"res\":\""<<vazio<<"\",\n";
		stream<<"\"pesquisas\":[";
		for(int i=0;i<pesquisas.size()-1;i++){
			stream<<"[\""<<pesquisas[i]<<"\"],";
		}
		stream<<"[\""<<pesquisas[pesquisas.size()-1]<<"\"]],\n";
		stream<<"\"pag\":"<<l.size()<<"}";

		cout << stream.str()<<endl;
		response->write(stream);

	};
	//toda essa função acima server.resource dá uma resposta pro javascript (mexe com o input de texto do user)
	//como fazemos isso: atraves do json! (javascript object notation)



	//O método default do server é abrir um arquivo na pasta web/
	//vai receber querys do tipo localhost:8080/{text}
  	server.default_resource["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
		auto path = "./web/"+request->path; //caminho até os arquivos do tipo HTML
		SimpleWeb::CaseInsensitiveMultimap header;
		std::ifstream ifs(path, ifstream::in | ios::binary | ios::ate); //abrindo o arquivo dentro da pasta /web
		auto length = ifs.tellg();//comprimento do arquivo
       	ifs.seekg(0, ios::beg);
       	stringstream stream;   //tá pegando o conteúdo do html e passando pra uma string stream
       	stream << ifs.rdbuf(); //salvando o conteúdo em uma stringstream
       	//(ifs.rdbuf()) vai escrever no response a string stream

        header.emplace("Content-Length", to_string(length));
        response->write(header);
        response->write(stream.str().c_str(), length); //e inserindo na resposta do servidor
    };













//função para lidar com erros (não necessário)

    server.on_error = [](shared_ptr<HttpServer::Request> /*request*/, const SimpleWeb::error_code & /*ec*/) {
		//code
	};


    thread server_thread([&server]() {
        // Start server
        server.start();
    });

    // Wait for server to start so that the client can connect
    this_thread::sleep_for(chrono::seconds(1));

	server_thread.join();
}
