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
		ifstream serializado ("Serialization.txt");
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

        for(int i = 0; i < pNode->doc_size; i++)
        {
            cout << pNode->docs[i][0]<< endl;
        }

    }
		
		
};

int main(){
	
	Trie trie;
    
	
	return 0;
}
