import java.util.concurrent.*;
import java.util.*;

class Caldeirao
{
	static int count = 0;
	static int villagerSleep = 0;
}

public class Main
{
	public static void main(String[] args)
	{
		
		//Criando um semaforo com numero de permissoes 0
		//E outro semaforo para manter a zona critica dos canibais segura
		Semaphore sem = new Semaphore(0);
		Semaphore caldeirao = new Semaphore(1);
		
		//Criando duas threads, uma e o cozinheiro a outra um simples villager
		Tribo cozinheiro = new Tribo(sem, caldeirao, "Cozinheiro", 0, 0);
		Tribo villager1 = new Tribo(sem, caldeirao, "Caçador", 0, 1);
		Tribo villager2 = new Tribo(sem, caldeirao, "Coletor", 0, 2);
		Tribo villager3 = new Tribo(sem, caldeirao, "Artesao", 0, 3);
		
		//Iniciando as duas threads
		cozinheiro.start();
		villager1.start();
		villager2.start();
		villager3.start();
		
		//Esperando as duas threads terminar para ver o quanto sobrou no caldeirao
		try
		{
			cozinheiro.join();
			villager1.join();
			villager2.join();
			villager3.join();
		}catch(InterruptedException exc)
		{
			System.out.println(exc);
		}
		
		
		System.out.println("Ao final, caldeirao contem: " + Caldeirao.count + " unidades de comida");
		System.out.println("O tempo total decorrido foi de: " + villager1.tTotal + " milisegundos");
		System.out.println("O Caçador comeu: " + villager1.comer + " vezes");
		System.out.println("O Coletor comeu: " + villager2.comer + " vezes");
		System.out.println("O Artesao comeu: " + villager3.comer + " vezes");
	}
}
