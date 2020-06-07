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

        ifstream file ("titles.txt");

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

        (*cons).push_back(*&(pNode->docs));
        (*cons_size).push_back(pNode->doc_size);
    }

    void split_search(string str)
    {
        vector<vector<int>*> * cons;
        vector<int>* cons_size, *resul;
        cons = new vector<vector<int>*>;
        cons_size = new vector<int>;
        int ini = 0;
        int f = 0;

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
        resul = new vector<int>;

        if((*cons).size() > 1)
        {
            
            for (int i = 0; i < (*cons_size)[0] ; i++)
            {
                resul->push_back((*((*cons)[0]+i))[0]);
                cout << (*((*cons)[0]+i))[0] << ",";

            }
            cout << endl;
            for (int i = 0; i < (*cons_size)[1] ; i++)
            {
                cout << (*((*cons)[1]+i))[0] << ",";

            }
            cout << endl;
            for (int i = 1; i < (*cons).size() ; i++)
            {
                intersec(resul,(*cons)[i], (*cons_size)[i] );
            }

            for (int i = 0; i < resul->size() ; i++)
            {
                cout << (*resul)[i] << ",";
            }
            
        }

    }

void intersec(vector<int>* resul,vector<int>* cons, int cons_size )
{
     int k = resul->size() - 1;

    for (int i = cons_size - 1; i > -1; i--)
    {
        if(k >= 0)
        {
            while ((*(cons+i))[0] < (*resul)[k])
            {
                (*resul).erase(resul->begin()+k);     
                k--;
                if(k < 0) break;
            }
            if ((*(cons+i))[0] == (*resul)[k]) k--;
        }
    }
    for (int i = k; i > -1; i--)
    {
        (*resul).erase(resul->begin()+i);  
    }
    

    return;  
}

	
		
};

int main(){
	
	Trie trie;
    string run = "";
    
    
    while (run != "0")
    {
        getline(cin, run);
        if((run != "0"))
        {
        trie.split_search(run);
        }
    }

	return 0;
}
