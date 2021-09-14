#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

int main( )
{
	//Vari�veis
	int i, j, k;						// Iteradores
	int num;							// Vari�vel que recebe o n�mero aleat�rio
	int cartelas[ 10 * 24 ];			// Variavel que montam as cartelas
	bool repetido = false;				// Variavel que controla se encontramos um valor repetido
	bool swapped = false;				// Variavel para otimiza��o da ordena��o
	int resultado[ 99 ];				// Array dos n�meros do sorteio
	int verificacao[ 10 ] = { 0 };		// Array de verifica��o das tabelas
	int num_ganhadores = 0;				// Controla se algu�m j� ganhou
	int index1, index2;					// Valores para embaralhar os n�meros do sorteio
	int temp;							// Vari�vel tempor�ria
	int input;							// Vari�vel para pegar input do usu�rio
	
	// Inicializa a seed do rand( )
	srand( time( NULL ) );

	// Itera as cartelas e gera os n�meros
	for ( i = 0; i < 10; i++ )
	{
		// Sub loop que itera os n�meros de cada cartela
		for ( j = 0; j < 24; j++ )
		{
			// Loop infinito para gerar os n�meros sem repeti��o
			while ( true )
			{
				// Resetar a flag e pegar um n�mero aleat�rio
				repetido = false;
				num = rand( ) % 99 + 1;

				// Checar se o n�mero est� repetido
				// O loop vai de 0, at� o n�mero atual - 1 (j - 1)
				for ( k = 0; k < j; k++ )
				{
					if ( cartelas[ i * 24 + k ] == num ) // Se estiver repetido, seta a flag e quebra o loop
					{
						repetido = true;
						break;
					}
				}

				// Se n�o encontramos um valor repetido, adicionamos na cartela atual
				if ( !repetido )
				{
					cartelas[ i * 24 + j ] = num;
					break;
				}
			}
		}


		// Ordena a tabela ( bubble sort )
		for ( j = 0; j < 24; j++ )
		{
			// Reseta a flag
			swapped = false;
			
			for ( k = 0; k < 24 - j - 1; k++ )
			{
				if ( cartelas[ i * 24 + k ] > cartelas[ i * 24 + k + 1 ] )
				{
					temp = cartelas[ i * 24 + k ];
					cartelas[ i * 24 + k ] = cartelas[ i * 24 + k + 1 ];
					cartelas[ i * 24 + k + 1 ] = temp;

					swapped = true;
				}
			}

			// Se n�o houver uma troca, a array j� est� otimizada
			if ( !swapped )
				break;
		}

		// Verifica se alguma tabela � igual a atual
		for ( j = 0; j < i; j++ ) // Loop de cartelas anteriores
		{
			for ( k = 0; k < 24; k++ ) // Loop dos n�meros das cartelas
			{
				if ( cartelas[ i * 24 + k ] != cartelas[ j * 24 + k ] ) // Se os n�meros forem diferentes, sabemos que as cartelas s�o diferentes
				{
					break;
				}

				// Se chegou aqui, as cartelas s�o iguais
				// Nesse caso, decrementamos o i para gerar uma nova cartela
				i--;
			}
		}
	}
	
	
	// Mostra as cartelas na tela
	for ( i = 0; i < 10; i++ )
	{
		printf( "Cartela %d:", i + 1 );

		for ( j = 0; j < 24; j++ )
		{
			if ( j % 6 == 0 )
				printf( "\n" );

			if ( cartelas[ i * 24 + j ] < 10 )
				printf( "0" );

			printf( "%d ", cartelas[ i * 24 + j ] );
		}

		printf( "\n\n" );
	}

	// Inicializa a array do resultado
	for ( i = 0; i < 99; i++ )
		resultado[ i ] = i + 1;

	// Embaralhar a array
	// O limite � um n�mero arbitr�rio de vezes
	// Quanto maior, mais aleat�rio
	for ( i = 0; i < 500; i++ )
	{
		index1 = rand( ) % 99;
		index2 = rand( ) % 99;

		temp = resultado[ index1 ];
		resultado[ index1 ] = resultado[ index2 ];
		resultado[ index2 ] = temp;
	}

	// Pegar a op��o do usu�rio
	input = 0;
	printf( "Escolha uma opcao:\n" );
	printf( "[1] Sorteio completo\n" );
	printf( "[2] Sorteio numero a numero\n" );
	printf( "Opcao: " );
	scanf_s( "%d", &input );
	printf( "\n" );

	if ( input == 1 || input == 2 )
	{
		for ( i = 0; i < 99; i++ )										// Iterar a array dos resultados
		{
			if ( input == 2 )
			{
				for ( j = 0; j < 30; j++ )
				{
					printf( "=" );
				}
				
				//printf( "\n          Rodada %d:\n\n", i );
				printf( "\n%16s %d:\n\n", "Rodada", i );
					
				printf( "Numero sorteado: %d\n", resultado[ i ] );
			}

			for ( j = 0; j < 10; j++ )									// Itera as cartelas
			{
				for ( k = 0; k < 24; k++ )								// Itera os n�meros das cartelas
				{
					if ( resultado[ i ] == cartelas[ j * 24 + k ] )		// Verifica se o resultado est� presente na cartela
					{
						verificacao[ j ]++;								// Soma 1 na array de verifica��o

						if ( verificacao[ j ] == 24 )					// Se a cartela atual ganhar, adicionamos um ganhador
							num_ganhadores++;
					}
				}

				if ( input == 2 )
					printf( "A cartela %d marcou %d numero%s\n", j + 1, verificacao[ j ], verificacao[ j ] == 1 ? "" : "s" );
			}
			
			if ( input == 2 )
			{
				system( "pause" );
				printf( "\n" );
			}

			// Se h� um ganhador
			if ( num_ganhadores )
			{
				printf( "Numeros sorteados: " );

				for ( j = 0; j <= i; j++ )
				{
					printf( "%d ", resultado[ j ] );
				}

				printf( "\n\nNumero de ganhadores: %d\n\n", num_ganhadores );

				printf( "Cartelas vencedoras:\n\n" );

				for ( j = 0; j < 10; j++ )
				{
					if ( verificacao[ j ] == 24 )
					{
						printf( "Cartela %d:", j + 1 );

						for ( k = 0; k < 24; k++ )
						{
							if ( k % 6 == 0 )
								printf( "\n" );

							if ( cartelas[ j * 24 + k ] < 10 )
								printf( "0" );

							printf( "%d ", cartelas[ j * 24 + k ] );
						}

						printf( "\n\n" );
					}
				}

				break;
			}
		}
	}

	system( "pause>nul" );
	return 0;
}
