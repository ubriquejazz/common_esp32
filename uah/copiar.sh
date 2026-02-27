#!/bin/bash

# 1. Variables de entorno
ORIGEN=$1
DESTINO="$HOME/.node-red"

# 2. Validación de entrada
if [ -z "$ORIGEN" ]; then
    echo "Uso: $0 <nombre_del_directorio_o_archivo>"
    exit 1
fi

# 3. Comprobar si el origen existe (sea carpeta o archivo)
if [ ! -e "$ORIGEN" ]; then
    echo "Error: '$ORIGEN' no existe."
    exit 1
fi

# 4. Ejecutar la copia recursiva
# -r: recursivo (para carpetas)
# -v: verbose (te dice qué está haciendo)
# -p: preserva permisos y fechas
cp -rvp "$ORIGEN" "$DESTINO/"

if [ $? -eq 0 ]; then
    echo "Todo se copió correctamente."
else
    echo "Try again."
fi