package main

import (
	"fmt"
	"html/template"
	"net/http"
	"io/ioutil"
)

//Structs

type Dados struct {
	Nome string
	Email string
	Senha string
}

type Cadastro struct {
    Arquivo string
    Cadastrados []byte
}

//Métodos
//Método atrelado ao struct, feito meramente para demonstração
//Cria um arquivo para salvar dados, persistência de dados
func (c *Cadastro) save() error {
    filename := c.Arquivo + ".txt"
    return ioutil.WriteFile(filename, c.Cadastrados, 0600)
}

//Funções
//Funcção para dar load no arquivo criado
func loadCad(arqu string) (*Cadastro, error) {
    filename := arqu + ".txt"
    corno, err := ioutil.ReadFile(filename)
    if err != nil {
        return nil, err
    }
    return &Cadastro{Arquivo: arqu, Cadastrados: corno}, nil
}

//Faz parte da biblioteca net/http
//Parâmetro w vai escrever na página enquanto o r retorna os inputs do usuário
//Os parâmetros de r vem do template
func handler_cadastro (w http.ResponseWriter, r *http.Request) {
		tmpl := template.Must(template.ParseFiles("templatinho.html"))
		
		if r.Method != http.MethodPost {
			tmpl.Execute(w, nil)
			return
		}

		dados := Dados{
			Nome: r.FormValue("nome"),
			Email: r.FormValue("email"),
			Senha: r.FormValue("senha"),
		}

		
		c1 := &Cadastro{Arquivo: "TestPage", Cadastrados: []byte(dados.Nome + ": " +dados.Email + "\nSenha: " +dados.Senha + "\n")}
		c1.save()
		c2, _ := loadCad("TestPage")
		fmt.Println(string(c2.Cadastrados))
		//fmt.Println(dados)

		tmpl.Execute(w, struct{ Success bool }{true})
	}

//Main
//Primeira funcao recebe 2 parâmetros, um para executar no local host e outro uma funcao handler
//Segunda funcao serve para ouvir a porta 80, padrão da http, e recebe nulo como segundo parâmetro
func main() {

	http.HandleFunc("/", handler_cadastro)

	http.ListenAndServe(":80", nil)
}
