El presente proyecto se lleva a cabo en el curso de Sistemas Operativos del ITCR, por lo estudiantes:
Armando López Cordero
Andrey Mendoza Fernández

El enfoque principal es el desarrollo de servidores y clientes



Terminar un proceso para liberar un puerto:
	fuser -n tcp 5060
	kill -9 port


Install make and Cmake(>= V.8)


Execution:
	make
	./server type port NumThreads

Parar la ejecución desde consola *liberando los recursos*:
	Ctrl+C 
