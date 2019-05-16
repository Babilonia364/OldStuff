%Criatura 1
quantidade_poupada(investidor, 22000).
ganho(investidor, 25000, estavel).
dependentes(investidor, 3).

%Criatura 2
quantidade_poupada(joao, 45000).
ganho(joao, 90000, estavel).
dependentes(joao, 4).


%Investidor com poupança inadequada deve priorizar poupança
investimento(X, poupanca):-
	poupanca(X, inadequada).

%Caso contrário, investimentos melhores
investimento(X, acoes):-
	poupanca(X, adequada),
	renda(X, adequada).
	
investimento(X, combinacao):-
	poupanca(X, adequada),
	renda(X, inadequada).
	
%Para determinar a mínima poupança adequada, a função min_poupança tem como argumento
%o número de dependentes e retorna 5000 vezes este número:
min_poupanca(Z, X):-
	X is 5000*Z.

%de maneira similar, a renda
min_renda(Z, X):-
	X is (15000+(4000*Z)).
	
%maior_que teste aritmetico
maior_que(X, Y):-
	X>Y.

/*%Gambiarra para rodar o programa
%Parte de poupanca
quantidade_poupada(X, Y).
dependentes(X, Z).

%Parte de renda
ganho(X, Y, estavel).*/

%A adequação da poupança pode ser definida pelas seguintes regras:
poupanca(X, adequada):-
	quantidade_poupada(X, Y),
	dependentes(X, Z),
	min_poupanca(Z, W),
	maior_que(Y, W).
	
poupanca(X, inadequada):-
	quantidade_poupada(X, Y),
	dependentes(X, Z),
	min_poupanca(Z, W),
	not(maior_que(Y, W)).

%A renda do investidor considera o predicado ganho com três argumentos:	
renda(X, adequada):-
	ganho(X, Y, estavel),
	dependentes(X, Z),
	min_renda(Z, W),
	maior_que(Y, W).

renda(X, inadequada):-
	ganho(X, Y, estavel),
	dependentes(X, Z),
	min_renda(Z, W),
	not(maior_que(Y, W)).

renda(X, inadequada):-
	(ganho(X, Y, instavel)).
