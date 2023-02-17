#!/bin/bash 

make 

echo "
Entrada x:
-Subconjunto
-Valor
"

I=1
for ARQ in entradas/*; do 
    echo "Entrada $I: "
    ./trab < $ARQ
    ((I=$I+1))
    echo ""
done
