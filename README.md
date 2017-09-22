El presente proyecto se lleva a cabo en el curso de Sistemas Operativos del ITCR, por lo estudiantes: Armando López Cordero Andrey Mendoza Fernández


<--- Compilación --->
Respecto a la compilación del proyecto se debe tener en cuenta que es necesario tener instalado Cmake & Make en el ordenador, esto con la finalidad de poder generar el makefile y otros archivos necesarios para la ejecución del programa. A continuación se presenta una sugerencia de instalación con los respectivos pasos que se deben llevar a cabo para instalar dichos complementos.

sudo apt-get install build-essential
wget http://www.cmake.org/files/v3.2/cmake-3.2.2.tar.gz
tar xf cmake-3.2.2.tar.gz 
cd cmake-3.2.2 ./configure 
make
sudo apt-get install checkinstall
sudo checkinstall

Una vez completados estos pasos ya se contará con los complementos necesarios para ejecutar tanto el servidor como los clientes desde la terminal, no obstante, primero se debe contar con una carpeta la cual almacenará los ejecutables de la aplicación, para ello hay que dirigirse a la ubicación del proyecto e ingresar el siguiente comando para crear dicha carpeta <mkdir Bin>. Luego hay que ubicarse dentro de la carpeta recién creada (Bin) y posteriormente realizar <cmake ..> dentro de la misma.
Llegando a este punto bastará con ingresar el comando <make> con el cual el programa estará compilado y por ende permitirá la ejecución de la aplicación.




<--- Ejecución --->
La ejecución del proyecto se debe llevar a cabo una vez que el mismo se encuentra compilado correctamente, sólo bastará con ubicarse dentro de la carpeta Bin creada con el <mkdir Bin>, note que si ya existe dicha carpeta sólo bastará con dirigirse dentro. 
Una vez hecho esto se deberán ingresar los parámetros que se van a enviar desde consola y por supuesto el nombre de la aplicación que se está intentando ejecutar. En este caso se cuenta con dos proyectos, donde el cliente y servidor se encuentran separados, por ende para ejecutar cada uno se debe ingresar en terminales distintas que se encuentren ubicadas dentro de la carpeta Bin correspondiente.

Servidor
Este se ejecuta con la siguiente instrucción, pero se debe tener claro que el parámetro numThreads sólo será útil en el caso de que el executionType sea igual a “pt” que hace referencia al servidor Pre-Thread. En el resto de los casos este parámetro se puede obviar/eliminar:

< ./Server	executionType	port	numThreads >

Ahora bien, los tipos de ejecución representan los tipos de servers que se tienen, donde estos se mencionan a continuación:
fi -> Server tipo FIFO
fo -> Server tipo FORK
th -> Server tipo THREAD
pt -> Server tipo PRE-THREAD
Entonces un ejemplo de ejecución funcional sería : ./Server fi 5050

Cliente
El cliente al ser un programa totalmente aparte del server, la instrucción de ejecución es totalmente distinta ya que los parámetros no son los mismos. A continuación se puede visualizar la estructura de la instrucción necesaria para ejecutarlo.

< ./Client	port	storagePath	files >

Donde storagePath es la localización donde se quiere guardar el conjunto de files, que vendrían a ser todos los archivos que se le van a pedir al servidor. Se debe tener claro que el parámetro files debe contener los nombres de archivos separados por una coma(,) y sin espacios.
Entonces un ejemplo de ejecución funcional sería : 

./Client 5050 /home/armando/Escritorio test1.html,test2.txt,test3.png,test4.jpg

