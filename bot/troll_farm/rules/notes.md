# Wood 2

1. Move to the closest tree
2. Collect the fruits
3. Return to the Shack

# Wood 1

1. Train trolls if first half of the game and always attributes set to 1
2. Move every troll like Wood 2, except that checks if the number of fruits
   available in the tree must be greater than 1

# Bronze

Hacer una implementación de un algoritmo genético (AG) para este juego de CodinGame (Spring Challenge 2026) **no es la mejor idea**, al menos no como el motor principal para controlar a los troles en tiempo real.

Aunque los algoritmos genéticos son fascinantes, la estructura de este reto particular los hace muy difíciles de implementar con éxito debido a las restricciones de tiempo y la naturaleza de las acciones.

Aquí te explico por qué puede fallar un AG y cuál es la alternativa que te llevará directo a la liga de Oro/Leyenda.

---

## 🛑 Por qué un Algoritmo Genético NO es ideal aquí

### 1. El límite de tiempo por turno (50 ms)

Los algoritmos genéticos necesitan simular cientos de "cromosomas" (secuencias de comandos) a lo largo de varios turnos para evaluar cuáles son mejores, cruzarlos y mutarlos.

* Con solo **50 ms por turno**, apenas tendrás tiempo de simular unas pocas generaciones. Si tu simulador no es extremadamente rápido (escrito en C++ optimizado a nivel de bits), te quedarás sin tiempo constantemente (`Timeout`).

### 2. El problema del "Espacio de Estados" gigante

A medida que entrenas más troles, el número de combinaciones de comandos explota exponencialmente. Si tienes 4 troles y cada uno puede hacer 5 acciones distintas (`MOVE`, `HARVEST`, `CHOP`, etc.), tienes $5^4 = 625$ combinaciones **por turno**. Evaluar esto a lo largo de un horizonte de 10 o 15 turnos mediante evolución es ineficiente.

### 3. El orden de ejecución estricto (Turn Order)

El juego tiene una fase de resolución muy específica (primero mueven, luego cosechan, luego plantan... y al final crecen los árboles). Programar un simulador perfecto que replique esto para que el AG "evalúe" el futuro es sumamente complejo y propenso a errores.

---

## 🚀 ¿Qué funciona mejor en este mapa de Bronce?

Para la liga de Bronce (y superiores), una arquitectura basada en **Reglas Heurísticas (FSM / Máquina de Estados)** o un enfoque de **Asignación de Tareas (Task Assignment)** suele ser infinitamente más competitiva, fácil de programar y rápida de ejecutar.

Aquí tienes una estrategia estructurada que puedes implementar:

### 1. Sistema de Roles/Estados para los Troles

En lugar de que una IA evolucione comandos aleatorios, asígnale un "rol" o estado a cada trol en base a sus atributos actuales:

* **Recolector de Fruta:** Si tiene alto `harvestPower` y `movementSpeed`.
* *Lógica:* Buscar el árbol con frutas más cercano $\rightarrow$ Ir hacia él $\rightarrow$ `HARVEST` hasta llenarse $\rightarrow$ Volver al Shack $\rightarrow$ `DROP`.


* **Leñador (La clave de los puntos en Bronce):** Si tiene alto `chopPower`. Recuerda que la madera da **4 puntos** (la fruta da 1).
* *Lógica:* Ir al árbol más grande cerca del agua (crecen más rápido) $\rightarrow$ `CHOP` $\rightarrow$ Volver al Shack $\rightarrow$ `DROP`.


* **Minero:** Necesitas hierro para entrenar más troles.
* *Lógica:* Quedarse quieto junto a una celda de `+` (IRON) $\rightarrow$ `MINE` $\rightarrow$ `DROP` (si está adyacente al shack) o caminar un paso para dejarlo.



### 2. Algoritmo de Emparejamiento (Min Distance / Hungarian Algorithm)

Para que tus troles no vayan todos al mismo árbol:

1. Crea una lista de "Objetivos" disponibles (Árboles con fruta, árboles para talar, hierro).
2. Calcula la distancia de cada trol a cada objetivo.
3. Asigna a cada trol el objetivo más óptimo usando una distancia simple (Manhattan).

### 3. La regla de oro para la build de `TRAIN`

El costo de entrenar aumenta con los atributos al cuadrado ($2 + \text{attr}^2$). Crear un súper-trol es carísimo. Es mucho mejor **entrenar muchos troles especializados y baratos**:

* Un trol rápido con mucha carga para recoger frutas: `TRAIN 2 2 1 0`
* Un trol leñador/minero: `TRAIN 1 2 0 2`

---

## 💡 ¿Dónde SÍ se podría usar un Algoritmo Genético?

Si tienes muchas ganas de usar un AG, hay un único lugar donde podría ser útil: **La optimización de los atributos de entrenamiento (`TRAIN`)**.

Podrías usar un algoritmo genético *offline* (en tu computadora, no durante la partida) para simular qué combinaciones de troles y en qué orden de turnos es más eficiente comprarlos para maximizar los puntos en el turno 300. Pero para el movimiento y acciones del día a día, utiliza **heurísticas puras**.

### Una pregunta para ayudarte a empezar:

¿En qué lenguaje estás programando tu bot y qué estrategia tienes pensada actualmente para decidir qué recurso priorizar (madera, fruta o hierro)?
