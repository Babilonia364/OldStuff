#!/usr/bin/env python											#Comecar a ler o codigo pelas ultimas 3 linhas dele, grato
from graph_tool.all import *									#Documentacao https://graph-tool.skewed.de/static/doc/index.html

def main():														#Funcao main, sera a funcao main do nosso programa, isso e bem diferente no python, seria como declarar uma funcao int main() fora do codigo principal do programa e chamar ela la.
	v = []														#Criando um "vetor" (list) em pyton, como trata - se de pyton, isto nao e apenas um vetor mas sim uma classe
	minimalPaths = []											#Por ser uma classe, teremos metodos proprios nativos da classe. Fonte: https://pt.stackoverflow.com/questions/202753/vetores-em-python
	global reliability											#Para poder alterar os valores da variavel global ja declarada nas ultimas 3 linhas do codigo, precisamos escrever global reliability, para ler apenas, isso nao precisa ser feito.

	loadGraph = input("Carregar grafo? (y/n): ")				#input vai ser tipo um scanf que printa antes entao. input retorna apenas string?
	if loadGraph == "y":										#Caso tenha sido sim, carregar o bloco de codigo abaixo
		#Carrega grafo salvo
		which = input("1- 5v7e\n2- 5v5e\n3- 7v11e\n")			#Escolha do tipo de grafo
		if which == "1" or which == "5v7e":						#Carrega grafo de 5 vertices e 7 arestas
			g = load_graph("graph5v7e.xml.gz")					#Comando de entrada e saida que vai carregar o grafo deste arquivo dado seu nome
			for vertex in g.get_vertices():						#Carrega os vertices presente no grafo g e os adiciona em v
				v.append(vertex)								#Comando inato de list, adiciona um "vertex" no final da lista/vetor v
		elif which == "2" or which == "5v5e":					#Senao se carrega grafo de 5 vertices e 5 arestas
			g = load_graph("graph5v5e.xml.gz")					#Analogo ao if anterior
			for vertex in g.get_vertices():
				v.append(vertex)
		elif which == "3" or which == "7v11e":					#Senao se carrega gravo de 7 vertices e 11 arestas
			g = load_graph("graph7v11e.xml.gz")					#Analago ao senao se anterior
			for vertex in g.get_vertices():
				v.append(vertex)
		vprob = input("Confiabilidade dos vértices: ")			#Pede para que haja a incercao do valor de probabilidade de confiabilidade dos vertices (p que estara entre [0, 1])
	else:
		#Gera novo grafo
		g = generateGraph()										#Ir para def generateGraph(), logo abaixo
		for vertex in g.get_vertices():							#Analogo a linha 15
			v.append(vertex)
		#g = randomGraph()
		vprob = input("Confiabilidade dos vértices: ")			#Definir o valor de probabilidade de confiabilidade dos vertices p = [0, 1]
		#Define uma propriedade para os vértices
		vertice_prob = g.new_vertex_property("double")
		g.vp.prob = vertice_prob
	#Carrega propriedades dos vértices
	for i in g.get_vertices():
		g.vp.prob[i] = vprob

	#Desenha novo grafo e salva
	#graph_draw(g, vertex_text=g.vertex_index, vertex_font_size=18, output_size=(200, 200), output="graph7v11e.png")
	#g.save("graph7v11e.xml.gz")

	#Encontra caminhos mínimos entre o primeiro e último vértices
	for path in all_paths(g, v[0], v[-1]):						#Quando houver um path (caminho), em todos os caminhos do grafo g do v[0] ate o v[-1](?)
		minimalPaths.append(path)								#Usar funcao para achar os minimos caminhos
	overlap(g, minimalPaths, minimalPaths[:], "sub")			#Ir para funcao overlap, linha 80
	print("Confiabilidade do grafo = {}".format(reliability))	#Printa a confiabilidade do grafo

def generateGraph():											#Funcao de geraco de novo grafo
	#Gera novo grafo
	g = Graph(directed = False)									#Gera um grafo nao orientado (orientacao = False)
	for i in range(8):											#Para i=0 ate i=8
		vertex = g.add_vertex()									#Atribuir a vertex o vertice criado na linha 52
	g.add_edge(v[0], v[1])										#Adiciona uma "edge" da fonte para o alvo add_edge(fonte, alvo)
	g.add_edge(v[0], v[2])
	g.add_edge(v[0], v[3])
	g.add_edge(v[1], v[4])
	g.add_edge(v[1], v[5])
	g.add_edge(v[2], v[5])
	g.add_edge(v[2], v[6])
	g.add_edge(v[3], v[6])
	g.add_edge(v[4], v[7])
	g.add_edge(v[5], v[7])
	g.add_edge(v[6], v[7])

	return g													#Retorna o grafo criado

def randomGraph():
	#Gera grafo aleatório com vértices definidos em n e grau de cada um definido em degree
	n = int(input("Numero de Vertices: "))
	g = random_graph(N=n, deg_sampler=degree, directed=False)
	return g

def degree():
	#Define o grau de cada vértice.
	#Deve retornar uma tupla de dois inteiros para graus interno e externo em grafos dirigidos, ou um inteiro para grafos não-dirigidos.
	return 2

def overlap(g, mainStack, stack, previousOperation):
	global reliability
	# step1
	if stack == mainStack:
		operation = "sum"
	elif stack != mainStack and previousOperation == "sub":
		operation = "sum"
	else:
		operation = "sub"
	# step2
	delete = []
	for i in range(len(stack)-2):
		for j in range(i+1, len(stack)-1):
			if set(stack[i]).intersection(stack[j]) == set(stack[i]):
				if j not in delete:
					delete.append(j)
			elif set(stack[i]).intersection(stack[j]) == set(stack[j]):
				if i not in delete:
					delete.append(i)
	delete.sort()
	for i in delete[::-1]:
		del stack[i]
	# step3
	if len(stack) == 1:
		if operation == "sum":
			for path in stack:
				pathReliability = 1
				for node in path:
					pathReliability *= g.vp.prob[node]
				reliability += pathReliability
		else:
			for path in stack:
				pathReliability = 1
				for node in path:
					pathReliability *= g.vp.prob[node]
				reliability -= pathReliability
		return
	# step4
	if operation == "sum":
		for path in stack:
			pathReliability = 1
			for node in path:
				pathReliability *= g.vp.prob[node]
			reliability += pathReliability
	else:
		for path in stack:
			pathReliability = 1
			for node in path:
				pathReliability *= g.vp.prob[node]
			reliability -= pathReliability
	# step5
	if len(stack) > 1:
		for i in range(1, len(stack)):
			newStack = []
			for j in range(i):
				newStack.append(list(set(stack[i]).union(stack[j])))
			overlap(g, mainStack, newStack, operation)
	# step6
	return

if __name__ == '__main__':				#Ao contrario de C, o codigo nao comeca direto executando na main, para isso essa linha existe algo haver com esta variavel especial chamada __name__ que recebe __main__ e nao entendi direito
	reliability = 0						#variavel global de confiabilidade
	main()								#Agora sim vamos para a def main(): la em cima e comecamos a execucao do nosso codigo
