# Sistema Inteligente con Integración Multi-Sensorial y Aprendizaje de Abstracciones

En este proyecto se desarrolló la arquitectura de un agente inteligente basado en aprendizaje por refuerzo y aprendizaje no-supervisado, específicamente se usó una versión del algoritmo Q-learning, y el mapa auto-organizado, respectivamente.

El objetivo del robot es ejecutar acciones para moverse de un punto inicial a un punto meta de una manera óptima Fig. 1b. 

Figura 1 En a) se observa que el robot utiliza telémetros para determinar su ubicación en su mundo. En b) muestra dos posibles trayectorias desde el punto inicial hasta el punto meta.

<img width="975" alt="image" src="https://github.com/user-attachments/assets/dc91b253-5fa3-4464-b1c1-29cb24f54733">

La Fig. 2 muestra la arquitectura del resultado de la integración del algoritmo Q-learning, y el mapa auto-organizado, y la llamamos Intra-options + Som. Según la arquitectura, primero los sensores procesan las señales de entrada vt que vienen del ambiente. Cada sensor tiene como salida un punto (x,y). Estos puntos que vienen de los tres sensores va a la red neuronal ya entranada. La red neuronal procesa los puntos, y entrega como salida un estado. Dicho estado sirve al agente inteligente para elegir una option ot , esta es ejecutada sobre el ambiente, el cual responde con una señal vt+1 y una recompensa rt+1. Cabe resaltar que una tabla Q(s,o) es actualizada con la recompensa que viene del ambiente o mundo real y de acuerdo con la regla de actualización Intra-options Q-learning de un sólo paso.

Figura 2 Arquitecura de agente inteligente con integración multisensorial y aprendizaje de abstracciones, Intra-options + Som.

<img width="964" alt="image" src="https://github.com/user-attachments/assets/859109b7-b271-4e45-b4f0-a41aa0d91b4c">

El modelo de ambiente y agente propuestos fueron implementados en el lenguaje de programación C++, en el cual también fue simulado la interacción del agente inteligente con su ambiente.

Fig. 3, curva de aprendizaje del agente, en el cual los primeros episodios tiene el mayor número de pasos los cuales estan alrededor de los 170, alcanza la tendencia estable en menos de los 50 episodios.

<img width="781" alt="image" src="https://github.com/user-attachments/assets/4227a20c-0ef4-46f5-9c15-641983dc1ea1">
