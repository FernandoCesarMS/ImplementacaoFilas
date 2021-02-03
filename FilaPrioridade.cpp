#include "FilaPrioridade.hpp"

FilaPrioridade::FilaPrioridade(){
    tamanho = 0;
    cabeca = NULL;
    menorPrioridade = 0;
}

int FilaPrioridade::estaVazio(){
    if (tamanho  == 0){
        return 1;
    }
    else{
        return 0;
    }
}

int FilaPrioridade::remover(){
    if (this->estaVazio() == 1)
    {
        return NULL;
    }
    else
    {
        int a = this->cabeca->getDado();
        if (this->getTamanho() != 1)
            this->cabeca = new No(this->cabeca->getProximo());
        else
            this->cabeca = new No(NULL,NULL, NULL);
        tamanho--;
        return a;
    }   
}

void FilaPrioridade::inserir(int prioridade, int dado){
    if (estaVazio() == 1){
        this->cabeca = new No(prioridade,dado, NULL);
        tamanho++;
    }   
    else{
        if (this->tamanho == 1){
            if (this->cabeca->getPrioridade() <= prioridade){
                No *aux = new No(prioridade,dado, NULL);
                this->cabeca->setProximo(aux);
                tamanho++;
            }
            else{
                No *aux = new No(this->cabeca->getPrioridade(),this->cabeca->getDado(), NULL);
                No *aux2 = new No(prioridade,dado, aux);
                this->cabeca = aux2;
                tamanho++;
            }
        }
        else{
            int mat[2][64],i;
            bool inserido = false;
            No *a = new No(prioridade,dado, NULL);
            No *aux = new No(this->cabeca->getPrioridade(),this->cabeca->getDado(), this->cabeca->getProximo());
            for (i=0;aux->getProximo() != NULL;i++){
                No *aux2 = new No(prioridade,dado, aux->getProximo());
                if ((inserido == false) && (aux->getProximo()->getPrioridade() > prioridade)){
                    aux->setProximo(aux2);
                    inserido = true;
                }
                mat[0][i] = aux->getPrioridade();
                mat[1][i] = aux->getDado();
                aux = new No(aux->getProximo());
            }
            mat[0][i] = aux->getPrioridade();
            mat[1][i] = aux->getDado();
            if (prioridade > aux->getPrioridade()){
                i++;
                mat[0][i] = prioridade;
                mat[1][i] = dado;
            }
            this->cabeca = NULL;
            tamanho = 0;
            for (int j=i;j>=0;j--){
                if (tamanho == 0){
                    this->cabeca = new No(mat[0][j],mat[1][j], NULL);
                }
                else{
                    No *inser = new No(this->cabeca->getPrioridade(),this->cabeca->getDado(), this->cabeca->getProximo());
                    this->cabeca = new No(mat[0][j],mat[1][j], inser);
                }
                tamanho++;
            } 
        }
    }
}   
unsigned FilaPrioridade::getTamanho(){
    return this->tamanho;
}
int FilaPrioridade::getMeio(){
    int posicaoMeio;
    if (this->getTamanho() % 2 == 0)
        posicaoMeio = this->getTamanho() / 2;
    else
        posicaoMeio = (this->getTamanho() - 1) / 2;
    No *aux = new No(this->cabeca);
    for (int i = 0; i < posicaoMeio; i++)
        aux = new No(aux->getProximo());
    return aux->getDado();
}
int FilaPrioridade::getUltimo(){
    No *aux = new No(this->cabeca);
    for (int i = 0; i < this->getTamanho() - 1; i++)
        aux = new No(aux->getProximo());
    return aux->getDado();
}
void FilaPrioridade::furaFila(int dado){
    No *aux = new No(this->cabeca->getPrioridade(),this->cabeca->getDado(),this->cabeca->getProximo());
    this->cabeca = new No(menorPrioridade,dado, aux);
    tamanho++;
    menorPrioridade++;
}
void FilaPrioridade::print(){
    No *aux = new No(this->cabeca);
    cout << aux->getDado() << " ";
    for (int i=0;aux->getProximo() != NULL;i++){
        aux = new No(aux->getProximo());
        cout << aux->getDado() << " ";
    }  
}