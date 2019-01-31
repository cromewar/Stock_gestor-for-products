// Proyecto Final de Progrmaci√≥n.
// @version: Alpha0.01
// @author: David Robles, Sebastian Rodriguez, Vasiliy Gualoto
/*Descripcion: Programa avanzado de gestion para supermercados o tiendas
	Capaz de identificar el tipo de producto, y clasificarlo autom√°ticamente sin tener que hacerlo
	de manera Manual y gestionar su stock de manera din√°mica.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//Valor m·ximo de productos, Modificiable
#define Numero_Prod_Max 30


//structura para los valores de cada producto

struct stock
        {
            char *nombreProducto;
            int  codigoUnico;
            int  cantidad;
            float precio;
        };
struct stock abarrotes[30];
//struct declarado como array

/*Variables Globales*/
int sec1, sec2, cant, cod;
float precio;
//Nombre del producto
char producto[30]={0};
//buffer temporal
char buffer[30]={0};
//nombre 
char name[15]={0};
//sentinelas
int i=0, h=0;
//a
int code;
//Variables para Modificar valores
int codeCambio;
//comodin para sobreEscritura
int comodin=0;


//creacion de archivos

FILE * prod;
//declaracion explicita de fclose
int fclose (FILE *stream);


//Prototipo de Funciones
//para aÒadir un producto dentro del Struct
void addProducto(char nombre[15],int codigo, float price, int cantidad);
//para leer del archivo todo el stock.
void consultarStock();
//consulta los detalles de un producto basado en su codigo
void consultarProducto(int valor);
// funcion para editar todo el contenido.
void editar();
//escribir en el archivo el struct completo.
void sobreEscribir();



int main()
{

    //Separador:
    char nombre1[3] = {'-'};
    // usar solo en caso de que el archivo se cree en otra parte.
    //char place[] 
    // = "place/Productos.txt";
    printf("*******************************************************************\n");
    printf("********** Bienvenido al sistema de Gestion de productos **********\n");
    printf("*******************************************************************\n");
    printf("***             A continuacion Digite su seleccion:             ***\n");
    printf("*******************************************************************\n");
    printf("***             1. Para ingresar un nuevo producto.             ***\n");
    printf("***             2. Para consultar el Stock.                     ***\n");
    printf("***             3. Para consultar el Stock por codigo.          ***\n");
    printf("***             4. Modificar valores.                           ***\n");
    printf("***             5. Reemplazar.                                  ***\n");
    printf("***             6. Para Salir.                                  ***\n");
	printf("*******************************************************************\n");
    printf("*** ");
    scanf("%d", &sec1);
    switch(sec1)
    {
        case 1:
        	//abre el archivo en modo adiciÛn y lectura.
            prod = fopen("productos.txt", "a+");
            //valida que el archivo se haya creado de manera eficaz.
            if(prod == NULL)
            {
                printf("No se puede crear el archivo");
            }
            printf("*******************************************************************\n");
            printf("***              Ingrese el Nombre del producto:                ***\n");
            printf("*** ");
            scanf("%s",&name);
            //valida que no se ingresen numeros usando la funcion ctype:
            while(h < sizeof(name)){
            	
            	if(isdigit(name[h]))
				{
					fflush(stdin);
					printf("El nombre del producto no debe contener numeros. \n");
					printf("Ingrese el nombre de nuevo: \n");
					scanf("%s", &name);					
				}
            	h++;
			}
			h=0;
            //escribe en el archivo el nombre del producto.
            fputs(name, prod);
            printf("***              Ingrese el codigo del producto:                ***\n");
            printf("*** ");
            scanf("%d", &sec2);
            //Valida que el codigo sea de 4 digitos.
			while(sec2 > 9999 || sec2 < 1000){
            	fflush(stdin);
            	printf("El codigo debe tener 4 digitos. \n");
            	scanf("%d", &sec2);
			}
            // aÒade el separador '-' dentro del archivo.
            fputs(nombre1, prod);
            //copia lo ingresado como valor para evitar llenar el buffer.
            sprintf(buffer,"%d",sec2);
            //escribe en el archivo el valor almenacenado del buffer, es decir codigo del producto.
            fputs(buffer,prod);
            printf("***              Ingrese el precio del Prodcuto:                ***\n");
            printf("*** ");
            scanf("%f", &precio);
            //Valida que el precio este entre 1 dolar con 11 y 9 con 99.
            while(precio > 9.99 || precio < 1.01){
            	fflush(stdin);
            	printf("El precio no esta en un rango aceptable. \n");
            	printf("Ingrese el precio nuevamente: \n");
            	scanf("%f", &precio);
			}
            //aÒade el separador '-' al archivo.
            fputs(nombre1,prod);
            //copia lo ingresado como valor para evitar llenar el buffer.
            sprintf(buffer, "%.2f", precio);
            //escribe en el archivo el valor almenacenado del buffer, es decir el precio del producto.
            fputs(buffer, prod);
            printf("***              Ingrese la cantidad del Prodcuto:              ***\n");
            printf("*** ");
            scanf("%d", &cant);
            //valida que la cantidad no sea mayor a 9999.
            while(cant > 9999){
            	fflush(stdin);
            	printf("La cantidad no esta en un rango aceptable. \n");
            	printf("Ingrese la cantidad nuevamente: \n");
            	scanf("%d", &cant);
			}
            //aÒade el separador '-' al archivo.
            fputs(nombre1, prod);
            //copia lo ingresado como valor para evitar llenar el buffer.
            sprintf(buffer,"%d\n",cant);
            //escribe en el archivo el valor almenacenado del buffer, es decir la cantidad del producto.
            fputs(buffer,prod);
            //Cierra el archivo
            fclose(prod);
            //Inicia la funciÛn que almacena los valores dentro del struct.
            addProducto(name,sec2,precio,cant);
            comodin++;
            //Imprime los datos ingresados.
            printf("***              Prodcuto ingresado con exito                   ***\n");
            printf("***              Usted Ingreso: Producto %s   codigo   %d       ***\n", name, sec2);
            printf("***                             Precio   %.2f    cantidad %d    ***\n", precio, cant);
            //Pausa de 3 segundos.
			sleep(3);
			//Limpia la pantalla.
			system("cls");
            break;
        case 2:
            printf("*******************************************************************\n");
            //abre el archivo en modo lectura.
            prod = fopen("productos.txt", "r");
            //verifica que se abrio de manera correcta.
            if(prod == NULL) {
                printf("No se puede crear el archivo");
            }
            //se invoca a la funcion para leer todo el stock desde el archivo.
            consultarStock();
            //se cierra el archivo
            fclose(prod);
            //Pausa de 5 segundos.
            sleep(5);
            //limpia la pantalla.
            system("cls");
            break;
        case 3:
            printf("*******************************************************************\n");
            printf("***              Ingrese el codigo del producto:                ***\n");
            printf("*** ");
            scanf("%d", &code);
            //valida que el codigo sea de 4 digitos:
            while(code > 9999 || code < 1000){
            	fflush(stdin);
            	printf("El codigo debe tener 4 digitos. \n");
            	scanf("%d", &code);
			}
			//invoca la funcion que toma los valores del producto desde el struct.
            consultarProducto(code);
            //pausa de 5 segundos.
            sleep(5);
            //limpa la pantalla
            system("cls");
            break;
        case 4:
        	editar();
        	break;
        case 5:
        	sobreEscribir();
			break;
		default:
            fclose(prod);
            exit(0);
            break;
    }

    main();
}


void addProducto(char nombre[15],int codigo, float price, int cantidad)
{
	//aÒade cada valor a la estructura y al final suma uno a i;
 abarrotes[i].nombreProducto = nombre;
 abarrotes[i].codigoUnico = codigo;
 abarrotes[i].cantidad = cantidad;
 abarrotes[i].precio = price;
 i++;
}

void consultarStock()
{
	//Variable para almacenar cada letra del archivo.
    char caracter;
    //Valida cuando se acaba el archivo.
    while(feof(prod)==0)
    {
    	//lee caracter por caracter y lo imprime en pantalla.
        caracter = fgetc(prod);
        printf("%c",caracter);
    }

}

void consultarProducto(int valor)
{
    int j=0;
    //se mueve por la estructura hasta encontrar el codigo.
    while(abarrotes[j].codigoUnico != valor)
    {
    	//si se llega al final del archivo y no se encuentra el codigo lo avisa,
        if(j==10 && abarrotes[j].codigoUnico != valor)
        {
            printf("*******************************************************************\n");
            printf("***              Producto no encontrado en el Stock             ***\n");
            printf("*******************************************************************\n");
            sleep(2);
            system("cls");
            main();

        }
        j++;
    }
    //Imprime los valores del producto.
    printf("*******************************************************************\n");
    printf("***           EL producto con codigo: %d es:            %s      ***\n", abarrotes[j].codigoUnico, abarrotes[j].nombreProducto);
    printf("***           Su precio es de:        %.2f y su cantidad: %d      ***\n", abarrotes[j].precio, abarrotes[j].cantidad);
    printf("*******************************************************************\n");

}

void editar()
{
	char nombre[15]={0};
	int codigo=0, cantidad=0;
	float precio=0;
	int ed, valor;
	int j=0;
	printf("*************************Editar producto***************************\n"); 
	printf("1.Editar nombre\n2.Editar codigo\n3.Editar Precio\n4.Editar Cantidad\n5.Cancelar.\n");
	printf("\nIngrese una opcion:\n");
	scanf("%d",&ed);
	switch(ed)
	{
		case 1:
			printf("Introducir codigo del producto a editar nombre: \n");
			scanf("%d", &valor);
			//valida el rango
			while(valor > 9999 || valor < 1000){
            	fflush(stdin);
            	printf("El codigo debe tener 4 digitos. \n");
            	scanf("%d", &valor);
			}
			while(abarrotes[j].codigoUnico != valor){
				if(j==10 && abarrotes[j].codigoUnico != valor)
       			 {
		            printf("*******************************************************************\n");
		            printf("***              Producto no encontrado en el Stock             ***\n");
		            printf("*******************************************************************\n");
		            sleep(2);
		            system("cls");
		            main();
       	 		}
				j++;
			}
			printf("el producto que selecciono es %s con codigo %d precio de %.2f y cantidad de %d", abarrotes[j].nombreProducto, abarrotes[j].codigoUnico, abarrotes[j].precio, abarrotes[j].cantidad);
			printf("\nIngrese el Nuevo Nombre para su producto: ");
			scanf("%s", &nombre);
			abarrotes[j].nombreProducto = nombre;
			printf("Valores modificados con exito. \n");
			sleep(2);
			system("cls");
			break;
		case 2:
			printf("Introducir codigo del producto a editar su codigo: \n");
			scanf("%d", &valor);
			//valida el rango
			while(valor > 9999 || valor < 1000){
            	fflush(stdin);
            	printf("El codigo debe tener 4 digitos. \n");
            	scanf("%d", &valor);
			}
			while(abarrotes[j].codigoUnico != valor){
				if(j==10 && abarrotes[j].codigoUnico != valor)
       			 {
		            printf("*******************************************************************\n");
		            printf("***              Producto no encontrado en el Stock             ***\n");
		            printf("*******************************************************************\n");
		            sleep(2);
		            system("cls");
		            main();
       	 		}
				j++;
			}
			printf("el producto que selecciono es %s con codigo %d precio de %.2f y cantidad de %d", abarrotes[j].nombreProducto, abarrotes[j].codigoUnico, abarrotes[j].precio, abarrotes[j].cantidad);
			printf("\nIngrese el Nuevo Codigo para su producto: ");
			scanf("%d", &codigo);
			//valida el rango
			while(codigo > 9999 || codigo < 1000){
            	fflush(stdin);
            	printf("El codigo debe tener 4 digitos. \n");
            	scanf("%d", &codigo);
			}
			abarrotes[j].codigoUnico = codigo;
			printf("Valores modificados con exito. \n");
			sleep(2);
			system("cls");
			break;
		case 3:
			printf("Introducir codigo del producto a editar su precio: \n");
			scanf("%d", &valor);
			//valida el rango
			while(valor > 9999 || valor < 1000){
            	fflush(stdin);
            	printf("El codigo debe tener 4 digitos. \n");
            	scanf("%d", &valor);
			}
			while(abarrotes[j].codigoUnico != valor){
				if(j==10 && abarrotes[j].codigoUnico != valor)
       			 {
		            printf("*******************************************************************\n");
		            printf("***              Producto no encontrado en el Stock             ***\n");
		            printf("*******************************************************************\n");
		            sleep(2);
		            system("cls");
		            main();
       	 		}
				j++;
			}
			printf("el producto que selecciono es %s con codigo %d precio de %.2f y cantidad de %d", abarrotes[j].nombreProducto, abarrotes[j].codigoUnico, abarrotes[j].precio, abarrotes[j].cantidad);
			printf("\nIngrese el Nuevo Precio para su producto: ");
			scanf("%f", &precio);
			//Valida que el precio este entre 1 dolar con 11 y 9 con 99.
            while(precio > 9.99 || precio < 1.01){
            	fflush(stdin);
            	printf("El precio no esta en un rango aceptable. \n");
            	printf("Ingrese el precio nuevamente: \n");
            	scanf("%f", &precio);
			}
			abarrotes[j].precio = precio;
			printf("Valores modificados con exito. \n");
			sleep(2);
			system("cls");
			break;
		case 4:
			printf("Introducir codigo del producto a editar su cantidad: \n");
			scanf("%d", &valor);
			//valida el rango
			while(valor > 9999 || valor < 1000){
            	fflush(stdin);
            	printf("El codigo debe tener 4 digitos. \n");
            	scanf("%d", &valor);
			}
			while(abarrotes[j].codigoUnico != valor){
				if(j==10 && abarrotes[j].codigoUnico != valor)
       			 {
		            printf("*******************************************************************\n");
		            printf("***              Producto no encontrado en el Stock             ***\n");
		            printf("*******************************************************************\n");
		            sleep(2);
		            system("cls");
		            main();
       	 		}
				j++;
			}
			printf("el producto que selecciono es %s con codigo %d precio de %.2f y cantidad de %d", abarrotes[j].nombreProducto, abarrotes[j].codigoUnico, abarrotes[j].precio, abarrotes[j].cantidad);
			printf("\n la Nueva Cantidad para su producto: ");
			scanf("%d", &cantidad);
			//valida que la cantidad no sea mayor a 9999.
            while(cantidad > 9999){
            	fflush(stdin);
            	printf("La cantidad no esta en un rango aceptable. \n");
            	printf("Ingrese la cantidad nuevamente: \n");
            	scanf("%d", &cantidad);
			abarrotes[j].cantidad = cantidad;
			printf("Valores modificados con exito. \n");
			sleep(2);
			system("cls");
			break;
		default:
			system("cls");
			main();
			break;
	}
	system("cls");
	sleep(3);
	main();
	}
}
void sobreEscribir()
{
	int comodin=0;
	comodin = feof(prod);
	char nombre1[3] = {'-'};
	char buffer[30]={0};
	int j=0;
	prod = fopen("productos.txt", "wt");
	do{
	fflush(stdin);
	fwrite(abarrotes[j].nombreProducto,1,strlen(abarrotes[j].nombreProducto), prod);
	fwrite(nombre1, 1, strlen(nombre1), prod);
	sprintf(buffer,"%d",abarrotes[j].codigoUnico);
	fwrite(buffer, 1, strlen(buffer), prod);
	fwrite(nombre1, 1, strlen(nombre1), prod);
	sprintf(buffer,"%.2f",abarrotes[j].precio);
	fwrite(buffer, 1, strlen(buffer), prod);
	fwrite(nombre1, 1, strlen(nombre1), prod);
	sprintf(buffer,"%d\n",abarrotes[j].cantidad);
	fwrite(buffer, 1, strlen(buffer), prod);
	j++;
	}while(j <= feof(prod));
	fclose(prod);
	printf("Escritura realizada con exito.");
    sleep(3);
    system("cls");
    main();
}




