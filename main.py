 #!/usr/bin/env python
# -*- coding: utf-8 -*-

# menuzinho com as opções
def menu():
    print('''
### SISTEMA DE REVENDA DE CARROS 2.0 ###

    1 - Cadastrar carro                            
    2 - Listar Carros                                 
    3 - Excluir carro (a partir do código)            
    4 - Listar carro mais antigo                      
    5 - Listar carro com maior porcentagem de lucro   
    6 - Sair                                          
''')

# cria um novo elemento com alocação dinâmica
def cadastrarCarro(carros):
    print("\n--- Cadastrando ---\n")
    iCodigo = int(input("Codigo: "))
    sNome = raw_input("Nome: ")
    sMarca = raw_input("Marca: ")
    iAno = int(input("Ano: "))
    fCompra = float(input("Valor de compra: "))
    fRevenda = float(input("Valor de revenda: "))
    fLucro = (((fRevenda - fCompra)) * 100) / fRevenda
    carros.append((iCodigo, sNome, sMarca, iAno, fCompra, fRevenda, fLucro))
    print("\nCarro cadastrado com sucesso!\n")

# exibi dados de todos os elementos
def listarCarros(carros):
    if(carros == []):
        print("\nNenhum carro cadastrado!\n")
    else:
        print("\n--- Carros Cadastrados ---\n")
        for carro in carros:
            iCodigo, sNome, sMarca, iAno, fCompra, fRevenda, fLucro = carro
            print("\nCodigo: " + str(iCodigo))
            print("Nome: " + str(sNome))
            print("Marca: " + str(sMarca))
            print("Ano: " + str(iAno))
            print("Valor de compra: " + str(fCompra))
            print("Valor de revenda: " + str(fRevenda))
            print("Porcentagem de lucro: " + str(fLucro) + "%")
            print("\n")

# mostrando os dados do carro
def mostrarCarro(carro):
    iCodigo, sNome, sMarca, iAno, fCompra, fRevenda, fLucro = carro 
    print("\nCodigo: " + str(iCodigo))
    print("Nome: " + str(sNome))
    print("Marca: " + str(sMarca))
    print("Ano: " + str(iAno))
    print("Valor de compra: " + str(fCompra))
    print("Valor de revenda: " + str(fRevenda))
    print("Porcentagem de lucro: " + str(fLucro) + "%")
    print("\n")

# exclui um elemento de acordo com o código
def excluirCarro(carros):
    print("\n--- Excluindo ---\n")
    excluir = int(input("Digite o código do carro que queira excluir: "))
    for carro in carros:
        iCodigo, sNome, sMarca, iAno, fCompra, fRevenda, fLucro = carro
        if(excluir == iCodigo):
            carros.remove(carro)
            print("\nCarro excluído com sucesso!\n")
        else:
            print("\nNão existe nenhum carro com esse código!\n")

# percorre toda a lista e retorna o elemento com ano mais antigo
def exibirAntigo(carros):
    print("\n--- Mais Antigo ---\n")
    antigo = 2050 # valor aleatorio
    for carro in carros:
        iCodigo, sNome, sMarca, iAno, fCompra, fRevenda, fLucro = carro
        if(antigo > iAno):
            achado = carro # guarda o carro com o ano mais antigo
            antigo = iAno
    # mostrando os dados do carro buscado
    mostrarCarro(achado)

# percorre toda a lista e retorna o elemento com maior lucro
def exibirLucro(carros): 
    print("\n--- Maior Antigo ---\n")
    lucro = 0.0
    for carro in carros:
        iCodigo, sNome, sMarca, iAno, fCompra, fRevenda, fLucro = carro
        if(lucro < fLucro):
            achado = carro
            lucro = fLucro
            
    # mostrando os dados do carro buscado
    mostrarCarro(achado)

# função que lê do arquivo e grava no arquivo
def lerArquivo(carros):
    try:
        arquivo = open("dados.txt","r")
        for linha in arquivo:
            # print(linha)
            array = linha.split(";")
            iCodigo = int(array[0])
            sNome = array[1]
            sMarca = array[2]
            iAno = int(array[3])
            fCompra = float(array[4])
            fRevenda = float(array[5]) 
            fLucro = float(array[6])
            carros.append((iCodigo, sNome, sMarca, iAno, fCompra, fRevenda, fLucro))
        arquivo.close()
        print("Dados carregados...")
    except IOError:
        print("Primeira inicialização...")
        
# função que grava a lista no arquivo
def gravarArquivo(carros):
    arquivo = open("dados.txt","w")
    for carro in carros:
        iCodigo, sNome, sMarca, iAno, fCompra, fRevenda, fLucro = carro
        arquivo.write(str(iCodigo) + ';')
        arquivo.write(sNome + ';')
        arquivo.write(sMarca + ';')
        arquivo.write(str(iAno) + ';') 
        arquivo.write(str(fCompra) + ';')
        arquivo.write(str(fRevenda) + ';')
        arquivo.write(str(fLucro) + ';')
        arquivo.write("\n")
    arquivo.close

# função principal
def main():
    carros = [] #lista
    lerArquivo(carros)
    menu()
    opcao = int(input(">>: "))
    while opcao != 6:
        if opcao == 1:
            cadastrarCarro(carros)
        elif opcao == 2:
            listarCarros(carros)
        elif opcao == 3:
            excluirCarro(carros)
        elif opcao == 4:
            exibirAntigo(carros)
        elif opcao == 5:
            exibirLucro(carros)
        else:
            print("Opção Inválida!")
        menu()
        opcao = int(input(">>: "))
    gravarArquivo(carros)

# chama a função main, que por sua vez chama todas as outras
main()