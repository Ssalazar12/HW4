PuntoNemo.pdf : polo.csv
	python Plots.py

polo.csv : PuntoGeographicPoint.c
	cc PuntoGeographicPoint.c -lm -o PuntoGeographicPoint.x 
	./PuntoGeographicPoint.x 	