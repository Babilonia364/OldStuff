/* IMPORTANTE: Sleep esta em milisegundos e e do tipo long */

import java.util.concurrent.*;
import java.util.*;

public class Tribo extends Thread
{
	Semaphore sem, caldeirao;
	String tribeOcup;
	int start, id, numVillagers=3, comer=0;
	long tTotal, tInit, tEnd;
	
	public Tribo(Semaphore sem, Semaphore caldeirao, String tribeOcup, int start, int id)
	{
		super(tribeOcup);
		this.sem=sem;
		this.tribeOcup=tribeOcup;
		this.start = start;
		this.caldeirao = caldeirao;
		this.id=id;
	}
	
	public void prepara_jantar()
	{
		Caldeirao.count++;
		System.out.println("Unidade de comida cozinhada");
		System.out.println("Caldeirao contem: " + Caldeirao.count + " unidades de comida");
	}
	
	public void servir()
	{
		Caldeirao.count--;
		System.out.println("Villager servido");
		System.out.println("Caldeirao agora contem: " + Caldeirao.count + " unidades de comida");
	}
	
	public void comer()
	{
		System.out.println("Villager " + id + " comendo");
		comer++;
	}
	
	@Override
	public void run()
	{
		//Caso seja um cozinheiro, rodara esta parte
		if(this.getName().equals("Cozinheiro"))
		{
			try
			{
				if(start==0)
				{
					System.out.println("Cozinheiro iniciado");
					System.out.println("Cozinheiro dormindo");
					start++;
					tInit = new Date().getTime();
				}
				
				//Ficando bloqueado ao tentar acessar uma trava com 0 permissoes
				sem.acquire();
				while(true)
				{
					if(Caldeirao.count == 5)
					{
						System.out.println("Cozinheiro Terminou de cozinhar");

						tEnd = new Date().getTime();
						tTotal = tEnd - tInit;

						if(tTotal >= (2*60010))
						{
							caldeirao.release();
							break;
						}else
						{
							System.out.println("Cozinheiro indo dormir.");
							Caldeirao.villagerSleep=0;
							caldeirao.release();
							sem.acquire();
						}
					}else if(Caldeirao.count == 0)
					{
						//Pega a trava do caldeirao para si
						//Impedindo os canibais de acordarem
						caldeirao.acquire();
						System.out.println("Cozinheiro acordando.");
						System.out.println("Cozinheiro cozinhando.");
						
						//Acessando os recursos compartilhados, outras threads terao de esperar
						while(Caldeirao.count < 5)
						{
							prepara_jantar();
							Thread.sleep(1000);
						}
					}
				}
			}catch(InterruptedException exc)
			{
				System.out.println(exc);
			}
			
			System.out.println("Processo cozinheiro terminado");
		}
		//PROCESSO DOS VILLAGERS ENTRARAO AQUI
		else
		{
			
			try
			{
				if(start==0)
				{
					System.out.println("Villager " + id + " iniciado");
					start++;
					tInit = new Date().getTime();
					
					//Troca de contexto para todos os  villagers iniciarem
					//Tentando diminuir a diferenĂ§a do tempo inicial
					Thread.sleep(5);
				}
				
				System.out.println("Villager " + id + " acordado");
				while(true)
				{
					//Adquirindo a trava para manter sua zona critica segura
					caldeirao.acquire();
					System.out.println("Villager " + id + " verificando o caldeirao");

					if(Caldeirao.count>0)
					{
						//Acessando recursos compartilhados
						System.out.println("Villager " + id + " se servindo");
						servir();
						Thread.sleep(1000);
						
						//Liberando o caldeirao para outros canibais
						caldeirao.release();
						comer();
						Thread.sleep(3000);
						
						//Villager vai esperar no minimo o tempo de 2 villagres comerem
						//Para que cada canibal coma, pelo menos, uma vez
						Thread.sleep((numVillagers-1)*1000);
					}else
					{
						System.out.println("Caldeirao vazio");
						Caldeirao.villagerSleep++;
						
						//Caso o villager seja o ultimo villager a ir dormir
						//Ele acorda o cozinheiro
						System.out.println("villagerSleep: " + Caldeirao.villagerSleep);
						if(Caldeirao.villagerSleep==numVillagers)
						{
							System.out.println("Villager " + id + " acorda o cozinheiro");
							sem.release();
						}
						
						//Liberando o caldeirao para o cozinheiro
						tEnd = new Date().getTime();
						tTotal = tEnd - tInit;

						if(tTotal >= (2*60010))
						{
							caldeirao.release();
							break;
						}else
						{
							System.out.println("Villager " + id + " indo dormir.");
							caldeirao.release();
							//Cada Villager vai esperar no min 5s pelo cozinheiro
							//Caso os 5s acabem, eles ficarao bloqueados na trava
							Thread.sleep(5000);
						}
					}
				}
				
				
			}catch(InterruptedException exc)
			{
				System.out.println(exc);
			}
			System.out.println("Processo Villager " + id + " Terminado.");
		}
	}
}
