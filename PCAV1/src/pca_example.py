#python3 pca_example.py

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Cargar los datos desde el archivo pca_data.txt
with open('pca_data.txt', 'r') as file:
    lines = file.readlines()

# Extraer los puntos y el vector director
points = np.loadtxt(lines[1:-2])
direction = np.fromstring(lines[-1], dtype=float, sep=' ')

# Crear la figura y los ejes 3D
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Graficar los puntos
ax.scatter(points[:, 0], points[:, 1], points[:, 2], c='blue', label='Puntos')

# Graficar el vector director
origin = np.mean(points, axis=0)
#ax.quiver(origin[0], origin[1], origin[2], direction[0], direction[1], direction[2],
#          color='red', label='Vector Director')
          
          
          
# Imprimiendo la dirección
ax.plot3D(  [-5*direction[0], 5*direction[0]], 
            [-5*direction[1], 5*direction[1]], 
            [-5*direction[2], 5*direction[2]], 'red', label='Vector Director')



# Configurar los límites de los ejes
max_range = np.max(points) - np.min(points)
ax.set_xlim(np.mean(points[:, 0]) - max_range, np.mean(points[:, 0]) + max_range)
ax.set_ylim(np.mean(points[:, 1]) - max_range, np.mean(points[:, 1]) + max_range)
ax.set_zlim(np.mean(points[:, 2]) - max_range, np.mean(points[:, 2]) + max_range)

# Configurar etiquetas y leyendas
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.legend()

# Mostrar el gráfico
plt.show()



"""
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Leer los datos del archivo generado por C++
data = np.loadtxt('pca_data.txt')

# Separar las coordenadas x, y, z
x = data[:, 0]
y = data[:, 1]
z = data[:, 2]

# Visualizar los resultados en 3D
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Imprimir los puntos
ax.scatter(x, y, z)

# Imprimir el vector director
direction = data[:, 3:]
ax.plot([0, direction[0]], [0, direction[1]], [0, direction[2]], 'blue')

plt.show()
"""

