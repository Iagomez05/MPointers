# MPointers
Este proyecto se desarrolla como parte del curso Algoritmos y Estructuras de Datos II (CE 2103) en el Instituto Tecnológico de Costa Rica. Su objetivo principal es diseñar e implementar una clase llamada MPointer en C++ que encapsule el uso de punteros, permitiendo una gestión más eficiente de la memoria y evitando fugas (memory leaks). Este proyecto busca también aplicar conceptos avanzados de manejo de memoria, programación orientada a objetos y patrones de diseño.

## Descripción
El proyecto implementa una clase template MPointer<T>, la cual actúa como una envoltura para los punteros tradicionales, facilitando el manejo de la memoria en C++ de una forma más segura. Cada instancia de MPointer es administrada por un recolector de basura (GC) denominado MPointerGC, el cual se encarga de la asignación y liberación automática de memoria según el conteo de referencias, evitando así fugas de memoria.

Además, se sobrecargan operadores clave como & y * para que los desarrolladores puedan interactuar con los punteros de una manera similar a los punteros tradicionales, pero con las ventajas de la gestión automatizada de memoria.

## Características
Implementación de la clase MPointer con sobrecarga de operadores.
Gestión de memoria automatizada mediante la clase singleton MPointerGC.
Implementación de algoritmos de ordenamiento (QuickSort, BubbleSort e InsertionSort) usando listas doblemente enlazadas que emplean internamente MPointer.
Pruebas unitarias con cobertura del 100% utilizando GTest.
