#include <stdio.h>
#include <stdlib.h>

/* Alunos: João Gabriel Santana e Rafael Bona
RGA João: 201811316011
RGA Rafael: 201811316022

Professor, nós escolhemos pela praticidade e simplicidade, 
prezando pela usabilidade do sistema para os usuários.
Por isso ocultamos o funcionamento da leitura e gravação no arquivo.

1) Se o arquivo não existir, o sistema prossegue normalmente,
cadastrando os carros ou excluindo. Somente no final, na função gravarArquivo()
que o sistema cria o arquivo e grava os dados da lista nele.

2) Se o arquivo existir, o sistema carrega os dados na lista.
Para isso, convencionamos que o código do carro tem que ser maior que zero.
No final, o arquivo é sobrescrito, mesmo que o usuário não tenha mudado nada.

Tudo isso acontece por debaixo dos panos, sem o usuário saber de nada.
Desse modo, o uso do programa se torna simples e mais interativo.
*/

// registro do carro 
struct carro {
    int codigo;
    char nome[35];
    char marca[35];
    int ano;
    float vcompra;
    float vrevenda;
    float vlucro;
    struct carro *prox;
};
typedef struct carro Carro;

// declaração das funções modularizadas
int menu(); // menuzinho bonitinho com as opções
Carro *criarNovoCarro(); // cria um novo elemento com alocação dinâmica
void exibirDadosCarro(Carro *element); // exibi dados de um elemento somente
void adicionarCarroListaFim(Carro *head, Carro *novo); // adiciona elemento no fim 
void adicionarCarroListaOrd(Carro *head, Carro *novo); // adiciona elemento ordenadamente
Carro *procurarUltimo(Carro *head); // procura o ultimo elemento da lista
void listarCarros(Carro *head); // percorre a lista mostrando os dados de todos os registros
Carro *excluirCarro(Carro *head, int codigo); // exclui um elemento de acordo com o código
Carro *acharCarroAntigo(Carro *head); // percorre toda a lista e retorna o elemento com ano mais antigo
Carro *acharCarroLucro(Carro *head); // percorre toda a lista e retorna o elemento com maior lucro
Carro *lerArquivo(Carro *head); // ler do arquivo e grava na lista de acordo com a ordem no arquivo
void gravarArquivo(Carro *head); // gravar no arquivo toda a lista, isso se ela exister

// ESCOPO PRINCIPAL
int main() {
    Carro *head = NULL, *novo, *antigo, *lucro;
    head = lerArquivo(head);
    int escolha, codigo;
    while((escolha = menu()) != 6) {
        switch (escolha) {
            case 1:
                novo = criarNovoCarro();
                if(head == NULL) {
                    head = novo;
                    printf("\nCarro cadastrado com sucesso!\n\n");
                }
                else{
                    //os dois jeitos estão funcionando
                    //adicionarCarroListaOrd(head, novo);
                    adicionarCarroListaFim(head, novo);
                }
                break;

            case 2:
                if(head != NULL) listarCarros(head);
                else printf("\nNada cadastrado!\n\n");
                break;
            
            case 3:
                printf("Digite o código do carro a ser excluído: ");
                scanf("%d", &codigo);
                head = excluirCarro(head, codigo);
                break;
            
            case 4:
                if(head != NULL) {
                    antigo = acharCarroAntigo(head);
                    printf("\nCarro mais antigo: \n");
                    exibirDadosCarro(antigo);
                }
                else printf("\nNenhum carro está cadastrado!\n\n");
                break;
            
            case 5:
                if(head != NULL) {
                    lucro = acharCarroLucro(head);
                    printf("\nCarro com maior porcentagem de lucro: \n");
                    exibirDadosCarro(lucro);
                }
                else printf("\nNenhum carro está cadastrado!\n\n");
                break;

            default:
                printf("\nOpção Errada!\n\n");
                break;
        }
    }
    gravarArquivo(head);
    return 0;
}

// menu com as opções
int menu() {
    int escolha;
    printf("\tSISTEMA DE REVENDA DE CARROS\n\n");
    printf("1 - Cadastrar carro\n");
    printf("2 - Listar carros cadastrados\n");
    printf("3 - Excluir carro (a partir do código)\n");
    printf("4 - Listar carro mais antigo\n");
    printf("5 - Listar carro com maior porcentagem de lucro\n");
    printf("6 - Sair\n\n");
    printf(">>: ");
    scanf("%d", &escolha);
    return escolha;
}

// essa função cria e aloca espaço para o novo carro a ser cadastrado
Carro *criarNovoCarro() {
    printf("\t\nEm caso de nome composto, usar underline ' _ ' em vez de espaço\n\n");
	Carro *novo = (Carro *)malloc(sizeof(Carro));
    printf("Codigo: ");
    scanf("%d", &novo->codigo);
    while(novo->codigo <= 0) {
        printf("Tente novamente!\nCodigo: ");
        scanf("%d", &novo->codigo);
    }
    printf("Nome: ");
    scanf("%s", novo->nome);
    printf("Marca: ");
    scanf("%s", novo->marca);
    printf("Ano: ");
    scanf("%d", &novo->ano);
    printf("Valor de compra: ");
    scanf("%f", &novo->vcompra);
    printf("Valor de revenda: ");
    scanf("%f", &novo->vrevenda);
    printf("\n");
    novo->vlucro = novo->vrevenda - novo->vcompra;
    // novo->vlucro = (100 * novo->vlucro) / novo->vcompra;
    novo->vlucro = (100 * novo->vlucro) / novo->vrevenda;
	novo->prox = NULL;
	return novo; // aqui ele retorna o novo carro
}

// essa função exibi todos os carros cadastrados na lista
void exibirDadosCarro(Carro *element) {
    printf("\nCódigo: %d\n", element->codigo);
    printf("Nome: %s\n", element->nome);
    printf("Marca: %s\n", element->marca);
    printf("Ano: %d\n", element->ano);
    printf("Valor de compra: %2.f\n", element->vcompra);
    printf("Valor de revenda: %2.f\n", element->vrevenda);
    printf("Porcentagem de lucro: %2.f%%\n\n\n", element->vlucro);
}

// essa função procura o último elemento da lista
Carro *procurarUltimo(Carro *head) {
	Carro *aux = head;
	if (aux != NULL) {
		while(aux->prox != NULL) 
            aux = aux->prox;
	}
	return aux;
}

// essa função adiciona um elemento no fim da lista
void adicionarCarroListaFim(Carro *head, Carro *novo) {
    Carro *ultimo = procurarUltimo(head);
    if(ultimo != NULL)
        ultimo->prox = novo;
}

// essa função listas todos os carros cadastrados na lista
void listarCarros(Carro *head) {
    Carro *aux = head;
    while (aux != NULL) {
        printf("\nCódigo: %d\n", aux->codigo);
        printf("Nome: %s\n", aux->nome);
        printf("Marca: %s\n", aux->marca);
        printf("Ano: %d\n", aux->ano);
        printf("Valor de compra: %2.f\n", aux->vcompra);
        printf("Valor de revenda: %2.f\n", aux->vrevenda);
        printf("Porcentagem de lucro: %2.f%%\n\n\n", aux->vlucro);
        aux = aux->prox;
    }
}

// essa função adiciona um elemento ordenadamente de acordo com o código do carro
void adicionarCarroListaOrd(Carro *head, Carro *novo) {
    Carro *a = NULL;
    Carro *p = head;
    while(p != NULL && p->codigo < novo->codigo) {
        a = p;
        p = p->prox;
    }
    if(a != NULL) {
        novo->prox = a->prox;
        a->prox = novo;
    }
    printf("\nCarro cadastrado com sucesso!\n\n");
}

// essa função exclui um carro cadastrado a partir do codigo
Carro *excluirCarro(Carro *head, int codigo) {
    Carro *a = NULL;
    Carro *p = head;
    while((p != NULL) && (p->codigo != codigo)) {
        a = p;
        p = p->prox;
    }
    if(p == NULL) {
        printf("\nEsse carro não foi cadastrado!\n\n");
        return head;
    }
    if(a == NULL) head = p->prox;
    else a->prox = p->prox;
    free(p);
    printf("\nCarro excluído com sucesso!\n\n");
    return head;
}

// essa função percorre toda a lista e retorna o carro com o ano mais antigo
Carro *acharCarroAntigo(Carro *head) {
    Carro *p = head, *a = p;
    int antigo = p->ano;
    while(p != NULL){
        if(p->ano < antigo) {
            antigo = p->ano;
            a = p;
        }
        p = p->prox;
    }
    return a;
}

// essa função percorre toda a lista e retorna o carro com a maior porcentagem de lucro
Carro *acharCarroLucro(Carro *head) {
    Carro *p = head, *a = p;
    float lucro = p->vlucro;
    while(p != NULL){
        if(p->vlucro > lucro) {
            lucro = p->vlucro;
            a = p;
        }
        p = p->prox;
    }
    return a;
}

// essa função lê do arquivo e grava na lista de acordo com a ordem gravada no arquivo
Carro *lerArquivo(Carro *head) {
    int codigo, ano;
    char nome[35], marca[35];
    float compra, revenda, lucro;
    FILE *file;
    file = fopen("dados.txt", "r");
    if(file) { // se o arquivo existir
        do {
            Carro *n, *p = head;
            n = (Carro *) malloc(sizeof(Carro));
            fscanf(file, "%d ; %s ; %s ; %d ; %f ; %f ; %f ;\n", &n->codigo, n->nome, n->marca, &n->ano, &n->vcompra, &n->vrevenda, &n->vlucro);
            if(n->codigo != 0) { // se o arquivo estiver vazio, o fscanf atribui codigo zero
                if(p != NULL){ // se a lista não for vazia
                    while(p->prox != NULL) { // procura o ultimo elemento
                        p = p->prox;
                    }
                    p->prox = n;
                    n->prox = NULL; 
                }
                else {
                    head = n; // se a lista, novo elemento é adicionado no inicio
                }
            }
        } while (!feof(file));
    }
    else {
        return NULL; // arquivo inexistente
        // o programa entende que é a primeira vez que está sendo executado
        // e nesse caso, no final da execução, o programa cria o arquivo com a função gravarArquivo()
    }
    fclose(file);
    return head; // no final a função retorna a lista com os dados lidos do arquivo
}

void gravarArquivo(Carro *head) {
    FILE *file;
    Carro *p = head;
    file = fopen("dados.txt", "w"); // caso o arquivo não exista (primeira execução), cria-se um novo
    // mas se exitir, é sobrescrevido
    if(file) { // se o arquivo existir
        while(p != NULL) {
            fprintf(file, "%d ; %s ; %s ; %d ; %f ; %f ; %f ;\n", p->codigo, p->nome, p->marca, p->ano, p->vcompra, p->vrevenda, p->vlucro);
            p = p->prox;
        }
    }
    else printf("Erro!");
    fclose(file);
}