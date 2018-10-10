#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>


typedef struct cliente{
        int codigo_cuenta;
        int dia;
        int mes;
        int anio;
        int numero_libreta;
        float saldo_apertura;
        float saldo_actual;
        char nombre[50];
        int cedula;
        char activo[2];
        char direccion[60];
        int numero;

}cliente;

typedef struct transaccion{
		int numero_asiento;
        int dia;
        int mes;
        int anio;
        int numero_libreta;
        char tipo[20];
        float monto;
 

}transaccion;

typedef struct fecha{
	    int dia;
        int mes;
        int anio;
}fecha;



int prueba(SHORT x, SHORT y){                        //LA FUNCION QUE EMULA GOTOXY
   COORD coord;
   HANDLE h_stdout;
   coord.X = x;
   coord.Y = y;
   if ((h_stdout = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE)
      return 0;
   if (SetConsoleCursorPosition(h_stdout, coord) == 0)
      return 0;
   return 1;
}





//llena el registro pasado por parámetro
void llenar (cliente *informacion)
{
     puts ("ingrese codigo de cuenta");
     scanf("%d",&informacion->codigo_cuenta);

     puts ("ingrese dia");
     scanf("%d",&informacion->dia);
     puts ("ingrese mes");
     scanf("%d",&informacion->mes);
     puts ("ingrese anio");
     scanf("%d",&informacion->anio);
     puts ("Ingrese numero de libreta");
     scanf("%d",&informacion->numero_libreta);
     puts ("Ingrese saldo con que aperturo la cuenta");
     scanf("%f",&informacion->saldo_apertura);
     puts ("Ingrese saldo actual");
     scanf("%f",&informacion->saldo_actual);


     puts ("Ingrese nombre");
     scanf("%s",&informacion->nombre);
     puts ("ingrese cedula");
     scanf("%d",&informacion->cedula);
     puts ("Se encuentra activo?");
     scanf("%s",&informacion->activo);
     puts ("Ingrese direccion");
     scanf("%s",&informacion->direccion);

     puts ("Ingrese numero de telefono");
     scanf("%d",&informacion->numero);

 }


 void mostrar (cliente *informacion)
{
      printf("\n      Codigo de cuenta: %12d\n",informacion->codigo_cuenta);
      printf("      Fecha de apertura: %6d/%d/%d \n",informacion->dia,informacion->mes,informacion->anio);
      printf("      Numero de Libreta: %11d \n",informacion->numero_libreta);
      printf("      Saldo de apertura: %11.3f \n",informacion->saldo_apertura);
      printf("      Saldo actual: %16.3f \n",informacion->saldo_actual);
      printf("      Nombre: %22s\n",informacion->nombre);
      printf("      C.I: %25d \n",informacion->cedula);
      printf("      Activo: %27s \n",informacion->activo);
      printf("      Direccion: %19s \n",informacion->direccion);
      printf("      Numero de Telefono: %10d \n",informacion->numero);


 }
 
void apertura(cliente datos_cliente){
	system("cls");
	transaccion informacion;
	FILE *archivo;
	
	archivo = fopen("transacciones.dat","rb");
	
	if(archivo==NULL){
		informacion.numero_asiento = 1;
	}else{
		int numero_de_ultimo_asiento = 0;
		int asiento_leido;
		transaccion transaccion_temporal;
		
		while(!feof(archivo)){
			
			fseek(archivo,numero_de_ultimo_asiento*sizeof(transaccion),SEEK_SET);
			
			asiento_leido = fread(&transaccion_temporal,sizeof(transaccion),1,archivo);	
			numero_de_ultimo_asiento = transaccion_temporal.numero_asiento;
			if(asiento_leido == 0)
				break;
		}
		
		fclose(archivo);
		
		informacion.numero_asiento = numero_de_ultimo_asiento + 1;
	}
	
	
	

	informacion.dia = datos_cliente.dia;
	

	informacion.mes = datos_cliente.mes;
	
	
	informacion.anio = datos_cliente.anio;
	
	
	informacion.numero_libreta = datos_cliente.numero_libreta;
	
	informacion.tipo[0] ='a';
	informacion.tipo[1] ='p';
	informacion.tipo[2] ='e';
	informacion.tipo[3] ='r';
	informacion.tipo[4] ='t';
	informacion.tipo[5] ='u';
	informacion.tipo[6] ='r';
	informacion.tipo[7] ='a';
	informacion.tipo[8] ='\0';
	
	informacion.monto = datos_cliente.saldo_apertura;
	
	archivo = fopen("transacciones.dat","ab");
	
	fwrite(&informacion,sizeof(transaccion),1, archivo);
	
	fclose(archivo);
	
}


 // Escribe en el archivo binario tantos registros como desee el usuario
 void llenar_binario(FILE *binario,char *nombre)
{
 char resp;
 cliente datos;

 binario=fopen(nombre,"ab"); /*wb sobreescribe*/
 do
 {
   llenar(&datos);
   fwrite(&datos,sizeof(struct cliente),1,binario);
   apertura(datos);
   puts("Presiones cualquier tecla para continuar o s para salir");
 }while(toupper(getch())!='S');

 fclose(binario);
 
 }


 //Muestra la información contenida en el archivo binario
 void mostrar_binario(FILE *binario,char *nombre)
{
 cliente datos;
 int cont=0;
 binario=fopen(nombre,"rb");
 do
 {  fread(&datos,sizeof(struct cliente),1,binario);
    if (!feof(binario))
    {printf("%d\t",cont++);
    mostrar(&datos);}
}while(!feof(binario));
 fclose(binario);
 }



int  buscar_cliente (FILE *binario,char *nombre){
     system("cls");

     cliente datos;
     int buscar;

     printf("\n\n\n\n\n    Ingrese cedula de cliente a buscar: ");
     scanf("%d",&buscar);

    binario = fopen(nombre,"rb");
    do{
         fread(&datos,sizeof(struct cliente),1,binario);

         if (datos.cedula == buscar){
           system("cls");
           printf(" LOS DATOS DEL USUARIO SON: \n\n ");
           mostrar(&datos);
           fclose(binario);
           return 1;
         }

    }while(!feof(binario));

    printf("\n\n EL USUARIO NO SE ENCUENTRA REGISTADO ");
    fclose(binario);
    return 0;


}



int modificar_cliente (FILE *binario,char *nombre){
    system("cls");

    cliente datos;
    int buscar,i=0,opcion;

    printf("\n\n\n\n\n   Ingrese cedula de cliente a buscar: ");
    scanf("%d",&buscar);

    binario = fopen(nombre,"rb+");
    do{
         fread(&datos,sizeof(struct cliente),1,binario);
         i++;

         if (datos.cedula == buscar ){

                          printf("\n\n DESEA MODIFICAR LOS DATOS DEL CLIENTE: %s",datos.nombre);
                          printf("\n   1. SI\n   2. NO\n\n");
                          scanf("%d",&opcion);

                             if (opcion==1){
                                   llenar(&datos);
                                   fseek(binario,-1*sizeof (struct cliente),1);
                                   fwrite(&datos,sizeof (struct cliente),1,binario);
                                   fclose(binario);
                             }

            return 1;
         }

    }while(!feof(binario));

    printf("\n\n\n  EL USUARIO NO SE ENCUENTRA REGISTRADO");

    fclose(binario);
    return 0;
}


void cierre_de_cuenta(int numero_libreta, float monto){
	
	system("cls");
	transaccion informacion;
	FILE *archivo;
	int dia,mes,anio;
	
	archivo = fopen("transacciones.dat","rb");
	
	if(archivo==NULL){
		informacion.numero_asiento = 1;
	}else{
		int numero_de_ultimo_asiento = 0;
		int asiento_leido;
		transaccion transaccion_temporal;
		
		while(!feof(archivo)){
			
			fseek(archivo,numero_de_ultimo_asiento*sizeof(transaccion),SEEK_SET);
			
			asiento_leido = fread(&transaccion_temporal,sizeof(transaccion),1,archivo);	
			numero_de_ultimo_asiento = transaccion_temporal.numero_asiento;
			if(asiento_leido == 0)
				break;
		}
		
		fclose(archivo);
		
		informacion.numero_asiento = numero_de_ultimo_asiento + 1;
	}
	
	printf("\ningrese el dia actual\n");
	scanf("%d",&dia);
	printf("\ningrese el mes actual\n");
	scanf("%d",&mes);
	printf("\ningrese el anho actual\n");
	scanf("%d",&anio);
	
	informacion.dia = dia;
	informacion.mes = mes;
	informacion.anio = anio;
	
	informacion.numero_libreta = numero_libreta;
	informacion.monto = monto;
	
	informacion.tipo[0] ='c';
	informacion.tipo[1] ='i';
	informacion.tipo[2] ='e';
	informacion.tipo[3] ='r';
	informacion.tipo[4] ='r';
	informacion.tipo[5] ='e';
	informacion.tipo[6] ='\0';
	
	archivo = fopen("transacciones.dat","ab");
	
	fwrite(&informacion,sizeof(transaccion),1, archivo);
	
	fclose(archivo);	
	
}




void eliminar_cliente(FILE *banco, char *nombre){
 	FILE *auxiliar;
 	cliente cliente_temporal;
 	int cedula;
 	printf("\n\n\nIngrese cedula del cliente a eliminar: ");
 	scanf("%d",&cedula);

 	banco = fopen(nombre,"rb");
 	auxiliar = fopen("auxiliar.dat","ab");

	int numero_de_ultimo_cliente=0;
	int cliente_leido;
	bool cliente_registrado = false;
	int numero_libreta;
	float monto;	
		
	if(banco==NULL){
	printf("\nNo se pudo abrir el archivo en el cual se encuentran los datos de su cuenta.\n");
		
	}else{
		while(!feof(banco)){
			
			fseek(banco,numero_de_ultimo_cliente*sizeof(cliente),SEEK_SET);

			cliente_leido = fread(&cliente_temporal,sizeof(cliente),1,banco);	
			
			if(cliente_leido == 0)
				break;
				
			if(cliente_temporal.cedula!=cedula){
				
				fwrite(&cliente_temporal,sizeof(cliente),1,auxiliar);
			}else{
				cliente_registrado = true;
				monto = cliente_temporal.saldo_actual;
				numero_libreta = cliente_temporal.numero_libreta;
			}				
			numero_de_ultimo_cliente = numero_de_ultimo_cliente + 1;
		}
		fclose(banco);
		fclose(auxiliar);
		
		remove("binario.dat");
		rename("auxiliar.dat","binario.dat");
		
		if(!cliente_registrado){
			printf("\nla cedula ingresada no esta asociada a ninguna cuenta registrada\n");
		}else{
			cierre_de_cuenta(numero_libreta,monto);
			printf("\ncliente eliminado con exito\n");
			}
	}
}


void presentacion(){
     prueba(18,8);  printf("  __   __  __    _  _______  _______ ");
     prueba(18,9);  printf(" |  | |  ||  |  | ||       ||       |");
     prueba(18,10); printf(" |  | |  ||  |  | ||       ||       |");
     prueba(18,11); printf(" |  | |  ||   |_| ||    ___||    ___|");
     prueba(18,12); printf(" |  |_|  ||       ||   |___ |   | __ ");
     prueba(18,13); printf(" |       ||  _    ||    ___||   ||  |");
     prueba(18,14); printf(" |       || | |   ||   |___ |   |_| |");
     prueba(18,15); printf(" |_______||_|  |__||_______||_______|");
}



 void menu(){
      printf("\n\n\n\n\n\n");
      printf("         ELIGE UNA OPCION \n\n");
      printf("1.- Introducir Datos\n");
      printf("2.- Consultar Datos\n");
      printf("3.- Modificar datos de cliente\n");
      printf("4.- Eliminar cliente\n");
      printf("5.- Mostrar todos los clientes\n");
      printf("6.- Salir\n\n");
}

void menuPrincipal(){
	printf("\n\n\n\n\n\n");
    printf("         ELIGE UNA OPCION \n\n");
    printf("1.- Administrar clientes\n");
    printf("2.- Transacciones\n");
    printf("3.- Salir\n\n");
	
}

void menuTransacciones(){
	printf("\n\n\n\n\n\n");
    printf("         ELIGE UNA OPCION \n\n");
    printf("1.- Apertura\n");
    printf("2.- Retiro\n");
    printf("3.- Deposito\n");
    printf("4.- Cierre de cuenta\n");
    printf("5.- Intereses\n");
    printf("6.- Mostrar Transacciones\n");
    printf("7.- Salir\n\n");
	
}



void mostrarTransacciones(){
	system("cls");
	transaccion asiento_temporal;
	FILE *archivo;
	int numero_de_ultimo_asiento=0;
	int asiento_leido;
	
	archivo = fopen("transacciones.dat","rb");
	
	if(archivo==NULL){
		printf("\nNo se pudo abrir el archivo en el cual se encuentran las transacciones.");
		
	}else{
		
		printf("\n  Nro	    Fecha         Nro		    Tipo	Monto");
		printf("\nAsiento			Libreta		Transaccion\n\n");
		
		while(!feof(archivo)){
			
			fseek(archivo,numero_de_ultimo_asiento*sizeof(transaccion),SEEK_SET);
			
			
			
			asiento_leido = fread(&asiento_temporal,sizeof(transaccion),1,archivo);	
			
			
			
			
			
			if(asiento_leido == 0)
				break;
			
			prueba(2,numero_de_ultimo_asiento+4);		
			printf("%d",asiento_temporal.numero_asiento);
            prueba(10,numero_de_ultimo_asiento+4);
			printf("%d/%d/%d",asiento_temporal.dia,asiento_temporal.mes,asiento_temporal.anio);
			prueba(24,numero_de_ultimo_asiento+4);					
			printf("%d",asiento_temporal.numero_libreta);
			prueba(41,numero_de_ultimo_asiento+4);					
			printf("%s",asiento_temporal.tipo);
			prueba(56,numero_de_ultimo_asiento+4);					
			printf("%10.3f",asiento_temporal.monto);
		
			numero_de_ultimo_asiento = numero_de_ultimo_asiento + 1;

		}
		
		fclose(archivo);
		getch();
		
	}
	
}

void retiro(){
	system("cls");
	cliente cliente_temporal;
	FILE *archivo;
	int numero_de_ultimo_cliente=0;
	int cliente_leido;
	int cedula;
	bool cliente_registrado = false;
	int dia,mes,anio;
	int posicion_cliente;
	
	printf("\ningrese su cedula\n");
	scanf("%d",&cedula);
	
	
	
	archivo = fopen("binario.dat","rb");
	
	if(archivo==NULL){
		printf("\nNo se pudo abrir el archivo en el cual se encuentran los datos de su cuenta.\n");
		
	}else{
		while(!feof(archivo)){
			
			fseek(archivo,numero_de_ultimo_cliente*sizeof(cliente),SEEK_SET);

			cliente_leido = fread(&cliente_temporal,sizeof(cliente),1,archivo);	
			
			if(cliente_leido == 0)
				break;
				
			if(cliente_temporal.cedula==cedula){
				posicion_cliente = numero_de_ultimo_cliente;
				fclose(archivo);
				cliente_registrado = true;
				
				float monto;
				printf("\ningrese el monto que desea retirar\n");
				scanf("%d",&monto);
				
				if(monto>cliente_temporal.saldo_actual){
					printf("\nSaldo insuficiente, usted solo posee %d bs.\n",cliente_temporal.saldo_actual);
					fclose(archivo);
					break;
				}else{
					
					printf("\ningrese el dia actual\n");
					scanf("%d",&dia);
					printf("\ningrese el mes actual\n");
					scanf("%d",&mes);
					printf("\ningrese el anho actual\n");
					scanf("%d",&anio);
					
					archivo = fopen("binario.dat","wb");
					fseek(archivo,posicion_cliente*sizeof(cliente),SEEK_SET);
					cliente_temporal.saldo_actual = cliente_temporal.saldo_actual - monto;
					fwrite(&cliente_temporal,sizeof(cliente),1,archivo);
					fclose(archivo);
					printf("\nretiro exitoso, su saldo actual es %f",cliente_temporal.saldo_actual);
							
					transaccion informacion;	
					archivo = fopen("transacciones.dat","rb");
							
					if(archivo==NULL){
						informacion.numero_asiento = 1;
					}else{
						int numero_de_ultimo_asiento = 0;
						int asiento_leido;
						transaccion transaccion_temporal;
								
						while(!feof(archivo)){
									
							fseek(archivo,numero_de_ultimo_asiento*sizeof(transaccion),SEEK_SET);
									
							asiento_leido = fread(&transaccion_temporal,sizeof(transaccion),1,archivo);	
							numero_de_ultimo_asiento = transaccion_temporal.numero_asiento;
							if(asiento_leido == 0)
								break;
						}
								
						fclose(archivo);
								
						informacion.numero_asiento = numero_de_ultimo_asiento + 1;
					}
							
					informacion.dia = dia;
					informacion.mes = mes;
					informacion.anio = anio;
					informacion.numero_libreta = cliente_temporal.numero_libreta;
							
					informacion.tipo[0] ='r';
					informacion.tipo[1] ='e';
					informacion.tipo[2] ='t';
					informacion.tipo[3] ='i';
					informacion.tipo[4] ='r';
					informacion.tipo[5] ='o';
					informacion.tipo[6] ='\0';
							
					informacion.monto = monto;
							
					archivo = fopen("transacciones.dat","ab");
							
					fwrite(&informacion,sizeof(transaccion),1, archivo);
							
					fclose(archivo);
	
					
					break;
				}
			}				
			numero_de_ultimo_cliente = numero_de_ultimo_cliente + 1;
		}
		if(!cliente_registrado)
			printf("\nla cedula ingresada no esta asociada a ninguna cuenta registrada\n");
		fclose(archivo);
	}
	getch();	
}

void deposito(){
	system("cls");
	cliente cliente_temporal;
	FILE *archivo;
	int numero_de_ultimo_cliente=0;
	int cliente_leido;
	int cedula;
	bool cliente_registrado = false;
	int dia,mes,anio;
	int posicion_cliente;
	
	printf("\ningrese su cedula\n");
	scanf("%d",&cedula);
	
	
	
	archivo = fopen("binario.dat","rb");
	
	if(archivo==NULL){
		printf("\nNo se pudo abrir el archivo en el cual se encuentran los datos de su cuenta.\n");
		
	}else{
		while(!feof(archivo)){
			
			fseek(archivo,numero_de_ultimo_cliente*sizeof(cliente),SEEK_SET);

			cliente_leido = fread(&cliente_temporal,sizeof(cliente),1,archivo);	
			
			if(cliente_leido == 0)
				break;
				
			if(cliente_temporal.cedula==cedula){
				posicion_cliente = numero_de_ultimo_cliente;
				fclose(archivo);
				cliente_registrado = true;
				
				float monto;
				printf("\ningrese el monto que desea depositar\n");
				scanf("%d",&monto);
					
				printf("\ningrese el dia actual\n");
				scanf("%d",&dia);
				printf("\ningrese el mes actual\n");
				scanf("%d",&mes);
				printf("\ningrese el anho actual\n");
				scanf("%d",&anio);
					
				archivo = fopen("binario.dat","wb");
				fseek(archivo,posicion_cliente*sizeof(cliente),SEEK_SET);
				cliente_temporal.saldo_actual = cliente_temporal.saldo_actual + monto;
				fwrite(&cliente_temporal,sizeof(cliente),1,archivo);
				fclose(archivo);
				printf("\ndeposito exitoso, su saldo actual es %f",cliente_temporal.saldo_actual);
							
				transaccion informacion;	
				archivo = fopen("transacciones.dat","rb");
							
				if(archivo==NULL){
					informacion.numero_asiento = 1;
				}else{
					int numero_de_ultimo_asiento = 0;
					int asiento_leido;
					transaccion transaccion_temporal;
								
					while(!feof(archivo)){
									
						fseek(archivo,numero_de_ultimo_asiento*sizeof(transaccion),SEEK_SET);
									
						asiento_leido = fread(&transaccion_temporal,sizeof(transaccion),1,archivo);	
						numero_de_ultimo_asiento = transaccion_temporal.numero_asiento;
						if(asiento_leido == 0)
							break;
					}
								
					fclose(archivo);
								
					informacion.numero_asiento = numero_de_ultimo_asiento + 1;
				}
							
				informacion.dia = dia;
				informacion.mes = mes;
				informacion.anio = anio;
				informacion.numero_libreta = cliente_temporal.numero_libreta;
							
				informacion.tipo[0] ='d';
				informacion.tipo[1] ='e';
				informacion.tipo[2] ='p';
				informacion.tipo[3] ='o';
				informacion.tipo[4] ='s';
				informacion.tipo[5] ='i';
				informacion.tipo[6] ='t';
				informacion.tipo[7] ='o';
				informacion.tipo[8] ='\0';
				
				informacion.monto = monto;
							
				archivo = fopen("transacciones.dat","ab");
							
				fwrite(&informacion,sizeof(transaccion),1, archivo);
							
				fclose(archivo);
	
				break;
			}				
			numero_de_ultimo_cliente = numero_de_ultimo_cliente + 1;
		}
		if(!cliente_registrado)
			printf("\nla cedula ingresada no esta asociada a ninguna cuenta registrada\n");
		fclose(archivo);
	}
	getch();	
}

void intereses(){
	system("cls");
	fecha fecha_temporal;
	FILE *archivo;
	FILE *auxiliar;
	int numero_de_ultima_fecha=0;
	int fecha_leida;
	int dia,mes,anio;
	bool fecha_pagada = false;
	float tasa_de_interes;
	float monto_a_pagar;
	float monto_total_pagado=0;
	
	
	printf("\ningrese el dia actual\n");
	scanf("%d",&dia);
	printf("\ningrese el mes actual\n");
	scanf("%d",&mes);
	printf("\ningrese el anho actual\n");
	scanf("%d",&anio);
	
	archivo = fopen("fechasPagadas.dat","rb");
	
	if(archivo!=NULL){
			
		while(!feof(archivo)){
			
			fseek(archivo,numero_de_ultima_fecha*sizeof(fecha),SEEK_SET);

			fecha_leida = fread(&fecha_temporal,sizeof(fecha),1,archivo);
			
			
			
			if(fecha_leida == 0)
				break;
				
			if((fecha_temporal.mes==mes) && (fecha_temporal.anio==anio)){
				fecha_pagada = true;
				break;	
			}				
			numero_de_ultima_fecha = numero_de_ultima_fecha + 1;
		}
		fclose(archivo);
	}
	
	if(fecha_pagada == true){
		printf("\nLos intereses correspondientes a la fecha ingresada ya fueron pagados.\n");
	}else{
		archivo = fopen("fechasPagadas.dat","ab");
		fecha_temporal.dia = dia;
		fecha_temporal.mes = mes;
		fecha_temporal.anio = anio;
		fwrite(&fecha_temporal,sizeof(fecha),1,archivo);
		fclose(archivo);
		
		
		printf("\ningrese la tasa de interes a pagar\n");
		scanf("%f",&tasa_de_interes);
		
		auxiliar = fopen ("auxiliar.dat","ab");
		archivo = fopen("binario.dat","rb");
		
		if(archivo==NULL){
			printf("\nNo se pudo abrir el archivo en el cual se encuentran los datos de los clientes.\n");	
		}else{
			
		
			cliente cliente_temporal;
			
			int numero_de_ultimo_cliente=0;
			int cliente_leido;
			
			while(!feof(archivo)){
				
				fseek(archivo,numero_de_ultimo_cliente*sizeof(cliente),SEEK_SET);
	
				cliente_leido = fread(&cliente_temporal,sizeof(cliente),1,archivo);	
				
				if(cliente_leido == 0)
					break;
				
				monto_a_pagar = cliente_temporal.saldo_actual*(tasa_de_interes/100);
				
				cliente_temporal.saldo_actual = cliente_temporal.saldo_actual + monto_a_pagar;
				fwrite(&cliente_temporal,sizeof(cliente),1,auxiliar);
				
				monto_total_pagado = monto_total_pagado + monto_a_pagar;				
								
				numero_de_ultimo_cliente = numero_de_ultimo_cliente + 1;
			}	
			fclose(archivo);
			fclose(auxiliar);
			remove("binario.dat");
			rename("auxiliar.dat","binario.dat");
			
			transaccion informacion;
			archivo = fopen("transacciones.dat","rb");
			
			if(archivo==NULL){
				informacion.numero_asiento = 1;
			}else{
				int numero_de_ultimo_asiento = 0;
				int asiento_leido;
				transaccion transaccion_temporal;
				
				while(!feof(archivo)){
					
					fseek(archivo,numero_de_ultimo_asiento*sizeof(transaccion),SEEK_SET);
					
					asiento_leido = fread(&transaccion_temporal,sizeof(transaccion),1,archivo);	
					numero_de_ultimo_asiento = transaccion_temporal.numero_asiento;
					if(asiento_leido == 0)
						break;
				}
				
				fclose(archivo);
				
				informacion.numero_asiento = numero_de_ultimo_asiento + 1;
			}
			
			informacion.dia = dia;
			informacion.mes = mes;
			informacion.anio = anio;
			
			informacion.numero_libreta = -1;
			informacion.monto = monto_total_pagado;
			
			informacion.tipo[0] ='i';
			informacion.tipo[1] ='n';
			informacion.tipo[2] ='t';
			informacion.tipo[3] ='e';
			informacion.tipo[4] ='r';
			informacion.tipo[5] ='e';
			informacion.tipo[6] ='s';
			informacion.tipo[7] ='e';
			informacion.tipo[8] ='s';
			informacion.tipo[9] ='\0';
			
			archivo = fopen("transacciones.dat","ab");
			
			fwrite(&informacion,sizeof(transaccion),1, archivo);
			
			fclose(archivo);	
		}
	}
	getch();	
}


 main(){
        FILE *banco;

       int opcion;



        presentacion();
      //  Sleep(2000);


        do{
			system("cls");
            menuPrincipal();
            scanf("%d",&opcion);
            
            switch(opcion){
				
				case 1:{
						 do{
				             system("cls");
				             menu();
				             scanf("%d",&opcion);
				
				             switch(opcion){
				
				
				             case 1:
				                  system("cls");
				                  llenar_binario(banco,"binario.dat");
				                  getch();
				                  break;
				
				             case 2:
				                  system("cls");
				                  printf("Esto es para consultar datos de un clientes");
				                  buscar_cliente(banco,"binario.dat");
				                  getch();
				                  break;
				
				             case 3:
				                  system("cls");
				                  printf("Esto es para modificar datos de un cliente");
				                  modificar_cliente(banco,"binario.dat");
				                  getch();
				                  break;
				
				             case 4:
				                  system("cls");
				                  printf("Esto es para eliminar los datos de un cliente");
				                  eliminar_cliente(banco,"binario.dat");
				                  getch();
				                  break;
				
				             case 5:
				                  system("cls");
				                  mostrar_binario(banco,"binario.dat");
				                  getch();
				                  break;
				
				             default:
				                     system("cls");
				
				                     }   //FIN DEL SWITCH

			        }while( opcion!=6);	
				}break;
				
				case 2:{
					do{
				        system("cls");
				        menuTransacciones();
				        scanf("%d",&opcion);
				
				        switch(opcion){
				
				
				             case 1:{
										system("cls");
										printf("El asiento/transaccion Apertura se realiza cuando se crea una cuenta");
										getch();
									}break;
				
				             case 2:{
										system("cls");
										retiro();
									}break;
				
				             case 3:{
										system("cls");
										deposito();
									}break;
				
				             case 4:{
										system("cls");
										printf("El asiento/transaccion Cierre de Cuenta se realiza cuando elimina un cliente");
										getch();
									}break;
				
				             case 5:{
										intereses();
									}break;
				                  
				             case 6:{
										mostrarTransacciones();
									}break;
				
				             default:
				                     system("cls");
				
				        }   //FIN DEL SWITCH
				
				
			        }while( opcion!=7);						
				}break;
				
				
				
				
			
			
				default:{
							system("cls");
						}break;
						

            }   //FIN DEL SWITCH
			
			
			
		}while(opcion!=3);

}
