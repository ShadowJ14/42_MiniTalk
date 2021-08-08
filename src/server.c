/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 15:55:52 by lprates           #+#    #+#             */
/*   Updated: 2021/08/08 20:21:11 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "minitalk.h"

int sendsig( int );

void binaryToString(char* input, char* output);
volatile int sigcount=0;

char bin[1024];
char test[1024];
static int x = 0;

void catcher() {
    sigcount++;
}

void    ft_signactyes();
void    ft_signactno();

int main(void)
{
    ft_putstr_fd("Server PID: ", 1);
    ft_putstr_fd(ft_itoa(getpid()), 1);

    struct sigaction sigactyes;
    struct sigaction sigactno;

    sigemptyset(&sigactyes.sa_mask);
    sigemptyset(&sigactno.sa_mask);
    sigactyes.sa_flags = 0;
    sigactno.sa_flags = 0;
    sigactyes.sa_handler = ft_signactyes;
    sigactno.sa_handler = ft_signactno;
    sigaction(SIGUSR1, &sigactyes, NULL);
    sigaction(SIGUSR2, &sigactno, NULL);

    while (1)
    {
        pause();
        printf("\nphrase:%s\n", bin);
        int iterations = strlen(bin) / 8; // get the # of bytes

    // convert each byte into an ascii value
    for (int i = 0; i < iterations; i++){
        binaryToString(&bin[i*8], &test[i]);
    }
    printf("\n%s", test);
        //printf( "\nThe signal catching function was called %d times\n", sigcount );
    }

    printf( "Back in main\n" );
    printf( "The signal catching function was called %d times\n", \
             sigcount );

    return (0);
}

void ft_signactyes()
{
    sigcount++;
    //write(1, "1", 1);
    bin[x] = '1';
    x++;
    //printf("%s", "1");
}

void ft_signactno()
{
    sigcount++;
    //write(1, "0", 1);
    bin[x] = '0';
    x++;
    //printf("%s", "0");
}

void binaryToString(char* input, char* output){

    char binary[9] = {0}; // initialize string to 0's

    // copy 8 bits from input string
    for (int i = 0; i < 8; i ++){
        binary[i] = input[i];    
    }

    *output  = strtol(binary,NULL,2); // convert the byte to a long, using base 2 
}