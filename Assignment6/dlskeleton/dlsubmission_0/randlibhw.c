/*From spec:
 randlibhw.c should contain the hardware implementation of the random number generator. It should start by including randlib.h and should implement the interface described by randlib.h.
 */

#include "randlib.h"
#include <immintrin.h>  ///for _rdrand64_step

/* Initialize the hardware rand64 implementation.  */
// void
//hardware_rand64_init (void)
//{
//}

/* Return a random value, using hardware operations.  */
unsigned long long
rand64 (void)
{
    unsigned long long int x;
    while (! _rdrand64_step (&x))
        continue;
    return x;
}

/* Finalize the hardware rand64 implementation.  */
// void
//hardware_rand64_fini (void)
//{
//}
