Para **"Code vs Zombies"** en CodinGame (que es un juego de optimización de puntuación), los mejores jugadores de la comunidad no usan IA complejas, sino algoritmos basados en **simulación heurística** y **búsqueda estocástica**.

La clave de este juego es su sistema de puntuación: **los combos te dan puntos exponenciales**. A veces, dejar morir a un humano lejos para agrupar zombies y matarlos a todos juntos en el mismo turno te dará diez veces más puntos que salvarlos a todos uno por uno.

Aquí tienes los 3 algoritmos más eficientes y sugeridos para dominar este mapa:

---

## 1. Algoritmo Genético (AG) — El más recomendado

Es el rey indiscutible para este tipo de retos de optimización en CodinGame. En lugar de calcular reglas lógicas complejas, dejas que la "evolución" encuentre la ruta perfecta.

- **Cómo aplicarlo:**

1. Un **"Cromosoma"** (o individuo) es una secuencia de movimientos futuros de Ash (por ejemplo, una lista de 5 a 10 coordenadas a las que Ash se moverá en los próximos turnos).
2. Generas una "población" inicial de 100 secuencias aleatorias.
3. **Simulas** cada secuencia en tu código local y calculas cuántos puntos obtendría Ash al final de esos turnos (esta es la función de _fitness_).
4. Cruzas las mejores secuencias entre sí, aplicas pequeñas mutaciones aleatorias y repites el proceso en bucle durante los 100ms que dura tu turno.
5. Al final del tiempo, ejecutas **solo el primer movimiento** de la mejor secuencia encontrada. En el siguiente turno, repites todo.

---

## 2. Búsqueda Aleatoria Pura con Simulación (Monte Carlo Simplificado)

Sorprendentemente, uno de los ganadores históricos del concurso original de _Code vs Zombies_ usó una variante de este método debido a lo rápido que se ejecuta en lenguajes como C++, Java o Rust.

- **Cómo aplicarlo:**

1. Creas un bucle `while` que corra frenéticamente hasta que falten 2ms para que se acabe tu tiempo de turno (puedes llegar a simular más de 100,000 estrategias por turno).
2. En cada iteración, generas una estrategia loca al azar. Por ejemplo: _"Moverse a una posición X aleatoria durante 2 turnos, y luego ir a cazar al Zombie id=4"_ o _"Matar a los zombies en orden aleatorio [3, 1, 5, 2]"_.
3. Ejecutas la simulación matemática de esa estrategia y guardas el puntaje.
4. Te quedas con la que dio el combo más masivo. Al simular tantos miles de opciones por segundo, el azar estadísticamente encuentra jugadas maestras de agrupación de zombies que a un humano jamás se le ocurrirían.

---

## 3. Algoritmo Codicioso con Heurística de Centroides (Greedy + Centroids)

Si no quieres programar un simulador completo de turnos futuros (requisito obligatorio para los dos anteriores) y prefieres un enfoque puramente matemático y lógico turno a turno, este es el camino.

- **Cómo aplicarlo:**

1. Calcula el tiempo de vida de cada humano: `Distancia(Zombie, Humano) / Velocidad_Zombie`.
2. Identifica cuáles humanos están en peligro de muerte inminente (menos turnos de vida de los que Ash tarda en llegar).
3. Si hay humanos en peligro crítico, calcula el **Centroide** (el punto geométrico medio) del grupo de zombies que los amenaza.
4. Dirige a Ash hacia ese centroide. Al disparar en el centro de masa de un grupo, maximizas la probabilidad de matar a varios zombies a la vez, activando los multiplicadores de combo de la fórmula de Fibonacci del juego.

---

### 💡 Mi consejo para ganar:

Empieza con el **Enfoque 3 (Centroides)** para salir de las ligas bajas rápidamente con pocas líneas de código. Si quieres escalar al Top 100 de la tabla global, la ruta obligatoria es escribir un simulador preciso del juego y montar un **Algoritmo Genético** sobre él.
