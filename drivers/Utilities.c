/*
 * utilities.c
 *
 *  Created on: 07/05/2021
 *      Author: Enrique
 */

#include "Utilities.h"

/** @fn void ftoa(float n, char *res, int afterpoint)
*   @brief Convierte una variable tipo float en una cadena de char[]
*   @param[in] n:           Variable tipo float a convertir.
*   @param[in] res: char    Cadena de char.
*   @param[in] afterpoint:  El numero de decimales deseados en la conversion.
*/
void ftoa(float n, char *res, int afterpoint){
    int ipart = (int)n, fpart = 0;
    /* Convertir parte entera */
    int i = sltoa(res, ipart );
    /* Agregar parte decimal */
    if(afterpoint > 0){
        res[i] = '.';
        fpart = (int)(( n - (float)ipart ) * pow(10, afterpoint ));
        sltoa(&res[i+1], abs(fpart) );
    }

}

/** @fn size_t sltoa(char *s, long int n)
*   @brief Convierte una variable tipo float en una cadena de char[]
*   @param[in] n:    pointer tipo xGPsdata en donde guardar datos
*   @param[in] : char actual recibido por el GPS.
*   @param[in] : char actual recibido por el GPS.
*/
size_t sltoa(char *s, long int n)
{
    size_t i = 0;
    long int sign_mask;
    unsigned long int nn;

    sign_mask = n >> sizeof(long int) * 8 - 1;
    nn = (n + sign_mask) ^ sign_mask;
    do {
        s[i++] = nn % 10 + '0';
    } while (nn /= 10);

    s[i] = '-';
    i += sign_mask & 1;
    s[i] = '\0';

    reverse(s, i);
    return (i);
}

static void reverse(char *s, size_t s_len) {
    size_t i, j;
    char swap;

    for (i = 0, j = s_len - 1; i < j; ++i, --j) {
        swap = s[i];
        s[i] = s[j];
        s[j] = swap;
    }
}
