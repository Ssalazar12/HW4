import matplotlib.pyplot as plt
import numpy as np
pole= np.genfromtxt('polo.csv')
newdata=np.genfromtxt('datamap.txt')

#encuentra el radio
rad= np.sqrt(pole[2]/np.pi)
#escala la coordenada y

#crea la figura
plt.figure(figsize=(10,7))
ax = plt.subplot(1, 1, 1)
plt.ylim(250)
plt.xlim(0,744)

circle=plt.Circle((pole[0], pole[1] ), radius= rad ,color='r', fill=False) #crea el circulo
ax.add_artist(circle)

plt.imshow(newdata, cmap='Greys') #crea el mapa
plt.scatter(pole[0],pole[1] ,s=10, color='b') #muestra el polo

plt.savefig('PuntoNemo.pdf')