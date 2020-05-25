#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

struct node
{
    //cada nó tera 128 filhos e uma lista de docs dentro
    node* Pfilho[128];
    vector<vector<int>> Docs;
    //futuro:tornar Docs vetor de vetores

    
    //projeto futuro como otimizar o numero de filhos de um nó

    node()
    {
        for (int i = 0; i < 128; i++)
        {
            Pfilho[i] = nullptr;
        }

    }


};

class Trie
{
    public:
    
    node* pRoot = new node;

    Trie(){}

    void add_plvr(string plvr, node* ppos, int id, int pos)
    {
        //caso nao reste mais letras em nossa palavra armazenaremos 
        //nossa id nesse utlimo nó
        cout << plvr[0] << endl;
        if (plvr == "")
        {
            //caso nao tenha nenhuma id dentro do nosso nó
            //armazenaremos a id dentro dele junto com a posicao onde a palavra ocorre
            if (ppos->Docs.size() == 0)
            {
                ppos->Docs.push_back({id,pos});
            }
            //caso ja tenha ids dentro, verificamos se o ultimo id tenha sido 
            //do atual documento que estamos armazenando, caso seja não precisaremos
            //armazenar novamente
            else if(ppos->Docs[ppos->Docs.size()-1][0] != id)
            {
                ppos->Docs.push_back({id,pos});
            }
            //caso seja o proprio documento somente add a posicao onde a palavra ocorre           
            else if(ppos->Docs[ppos->Docs.size()-1][0] == id)
            {
                ppos->Docs[ppos->Docs.size()-1].push_back(pos);
            }
            return;
        }
        //caso contrario iremos criar um nó filho para nosso atual nó
        //caso não exista o nó adequado para a atual letra
        if(ppos->Pfilho[(int) plvr[0]] == nullptr)
        {
            ppos->Pfilho[(int) plvr[0]] = new node;
        }
        //continuamos descendo na arvore
        add_plvr(plvr.substr(1,plvr.length() - 1), ppos->Pfilho[(int) plvr[0]], id, pos);   
    }

    //adiciona a id do documento na trie
    void add_doc(string doc, int id)
    {
        
        int c = 0;
        int i = 0;
        int f = 0;
        int pos = 0;
        while(c < doc.length())
        {
            
            //itera sobre o documento ate encontrar um caracter diferente 
            //de " ", significando que é o começo de uma palavra
            while(doc[c] == ' ' && c < doc.length())
            {
                c++;  
                
            }
            i = c;
            //itera do começo da palavra econtrada ate o final dela
            while(doc[c] != ' ' && c < doc.length()) 
            {
                c++;            
            }
            f = c - 1;
            //adiconamos a palavra que encontramos
            if(i<=f)
            {
                pos++;
                add_plvr(doc.substr(i,f-i+1),pRoot,id,pos);
            }
        }
    }
}