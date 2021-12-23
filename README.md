# Robotica UCM

## Descripción

Aquí está todo el código que hice junto a mi compañero* para Robótica (grado de Ingeniería Informática) en el curso 2020-2021.

Tuvimos que construir un robot usando una Raspberry PI capaz de seguir líneas o de moverse por un pasillo sin chocarse contra la pared.

*_No me sé su nombre de GitHub_

## Cómo compilar el código

Se puede usar el Makefile con el comando `make`, pero para no tener que compilar y luego tener que escribir otro comando para ejecutar el ejecutable, existe un fichero `make-and-run` justo para eso. Por ejemplo, se pasaría de esto:

```bash
make motores
./motores
```

A tener que escribir solamente `make-and-run motores`.
