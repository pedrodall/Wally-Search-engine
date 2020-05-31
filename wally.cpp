#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

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
	void array_size(int size) {
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
		deserialize(serializado);
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
				pNode->array_size(stoi(number));
				number = "";
			}
			else number = number + letter;
		}
	}

    void search(string plvr)
    {
        clock_t t0, t;
	    t0 = clock();
        string more = "";

        Node* pNode = pRoot;
        vector<int> consultas;
        string line;
        int j = 0;
        
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
        ifstream file ("titles.txt");

        for(int i = 0; i < pNode->doc_size; i++)
        {
            consultas.push_back(pNode->docs[i][0]);
        }

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
        // for(int i = 0; i < pNode->doc_size; i++)
        // {
        //     cout << "{"<< i << "}" << pNode->docs[i][0]<< endl;
        //     if(i % 2 == 1)
        //     {
        //         cout<< "Ver mais?"<< endl;
        //         cin >> more;

        //         if(more != "s")
        //         {
        //             return;
        //         }
        //     }
        // }

    }


		
		
};

int main(){
	
	Trie trie;
    string run = "";
    while (run != "0")
    {
        cin >> run;
        if((run != "0"))
        {
        trie.search(run);
        }
    }

	return 0;
}
