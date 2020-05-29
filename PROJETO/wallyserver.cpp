#include "lib/server_http.hpp" //Chamando pacotes do Simple Web Server
#include <sstream>
#include <fstream>

using namespace std;
using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

int main(){
	HttpServer server;
	server.config.port = 8080; //porta do servidor será localhost/8080

	//função que recebe query do tipo localhost:8080/query?text={text}
	server.resource["^/query$"]["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request){
		//Trecho do código para obter a query (consulta)
		auto query_fields = request->parse_query_string(); //Recebe o conteúdo de "entrada" (request é o pedido do user pro server)
		auto it = query_fields.find("text"); // Obtem o texto do conteudo
		cout << it->second << endl; //o it second é o valor q aparece em {text} la em cima
		//A resposta para o servidor vai ser um JSON do formato
		//{"res": "O seu projeto final vai ser incrível, [texto]!"}	
		//JSON
		// {"atributo1":"valor1",
		//	"atributo2": {"sub-atributo": "valor2"}} 
		string img_button = " mas você pode usar o wikipédia de verdade! <a href= \'https://en.wikipedia.org/wiki/"+it->second+"\'> Clique aqui</a>";	
		//img button é só um texto q dps a gente lida no javascript pra conseguirmos interpretar
		stringstream stream;
		stream << "{\"res\":\"" << "Não conseguimos a busca para  "<< it->second << " ..." << img_button << "\"}"; 
		cout << stream.str();
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