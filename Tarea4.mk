PuntoNemo.pdf : polo.csv
	cc PuntoGeographicPoint.c -lm -o PuntoGeographicPoint.x 
	./PuntoGeographicPoint.x 
	python Plots.py
	