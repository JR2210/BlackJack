#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int dealer[10];
    int jugador[10];
} manos;
manos mano;

int rand2()
{
    return 1 + rand() % ((12 + 1) - 1);
}

void limpiar_Manos()
{
    for (int i = 0; i < 10; i++)
        mano.dealer[i] = 0, mano.jugador[i] = 0;
}

void anadir1(int *sumaDealer, int *sumaJugador, int cont, int apuesta)
{
    int seleccion, salida = 1, contadorDealer = cont, aleatorio;
    while (*sumaJugador < 22 && salida != 0)
    {
        printf("\nQue quiere hacer? (1.Pedir Carta/0.Continuar): ");
        scanf("%d", &seleccion);
        switch (seleccion)
        {
        case 0:
            salida = 0;
            break;
        case 1:
            aleatorio = rand2();
            mano.jugador[cont] = aleatorio;
            if (aleatorio > 9)
                *sumaJugador += 10;
            else
                *sumaJugador += aleatorio;
            cont++;
            printf("\nTus cartas ahora son: ");
            for (int i = 0; i < cont; i++)
                printf("%d ", mano.jugador[i]);
            printf("---> %d puntos\n", *sumaJugador);
            break;
        }
    }
    fflush(stdin);
    while (*sumaDealer < *sumaJugador && *sumaDealer < 22)
    {
        if (*sumaDealer > *sumaJugador)
            break;
        if (*sumaJugador > 21)
            break;
        aleatorio = rand2();
        mano.dealer[contadorDealer] = aleatorio;
        *sumaDealer += aleatorio;
        contadorDealer++;
    }

    printf("\nCartas del dealer: ");
    for (int i = 0; i < contadorDealer; i++)
        printf("%d ", mano.dealer[i]);
    printf("---> %d puntos\n", *sumaDealer);
}

int ganador(int sumaDealer, int sumaJugador, int dinero, int apuesta)
{
    if (sumaJugador < 22)
    {
        if (sumaDealer > 21)
        {
            dinero += apuesta * 2;
            printf("Has ganado %d euros", apuesta * 2);
        }
    }
    if (sumaDealer == sumaJugador)
    {
        dinero += apuesta;
        printf("Empate");
    }
    if (sumaJugador > 21 && sumaDealer < 22 || sumaJugador < sumaDealer && sumaDealer < 22)
        printf("Perdiste %d euros", apuesta);
    return dinero;
}

void mostrar(int dealer[], int jugador[], int sumaDealer, int sumaJugador, int cont)
{
    printf("                DEALER: ");
    for (int i = 0; i < cont; i++)
        printf("%d ", dealer[i]);
    printf("---> %d puntos\n", sumaDealer);
    printf("\n");
    printf("\n");
    printf("                   TU: ");
    for (int i = 0; i < cont; i++)
        printf("%d ", jugador[i]);
    printf("---> %d puntos\n", sumaJugador);
}

int menu()
{
    printf("*****************************************************\n");
    printf("***************BIENVENIDO AL BLACKJACK***************\n");
    printf("*****************************************************\n");
    printf("                DEALER: %d %d", rand2(), rand2());
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                    TU: %d %d\n", rand2(), rand2());
    printf("*****************************************************\n");
    printf("*****************************************************\n");
    printf("*****************************************************\n");
}

int reparto_Inicial(int dinero)
{
    int apuesta, sumaDealer = 0, sumaJugador = 0, cont = 0, salida = 1;
    while (salida != 0 && dinero > 0)
    {
        printf("Cuanto quiere apostar?: ");
        scanf("%d", &apuesta);
        dinero -= apuesta;
        for (int i = 0; i < 2; i++) // reparto las cartas inciales al Dealer y al jugador
        {
            mano.dealer[i] = rand2(); //
            mano.jugador[i] = rand2();
            if (mano.dealer[i] > 9)
            {
                sumaDealer += 10;
            }
            else
            {
                sumaDealer += mano.dealer[i];
            }
            if (mano.jugador[i] > 9)
            {
                sumaJugador += 10;
            }
            else
            {
                sumaJugador += mano.jugador[i];
            }
            cont++;
        }
        mostrar(mano.dealer, mano.jugador, sumaDealer, sumaJugador, cont);
        anadir1(&sumaDealer, &sumaJugador, cont, apuesta);
        dinero = ganador(sumaDealer, sumaJugador, dinero, apuesta);
        printf("\nDinero restante --> %d", dinero);
        printf("\nQuiere volver a jugar?(0.Salir/1.Volver): ");
        scanf("%d", &salida);
        if (salida != 0)
        {
            limpiar_Manos();
            cont = 0;
            sumaDealer = 0;
            sumaJugador = 0;
        }
        system("cls");
    }
    return dinero;
}

int main()
{
    int dinero;
    srand(time(NULL));
    printf("Dinero a Ingresar: ");
    scanf("%d", &dinero);
    menu();
    dinero = reparto_Inicial(dinero);
    printf("Gracias por jugar\nDinero restante --> %d", dinero);
    return 0;
}
