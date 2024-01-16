#include <stdio.h> 
#include <math.h>
 
	int i,l;		
	int n_r = 20;										// Iterationsvariablen für r und die Zeit
	const double r = 0.02;								// Radius in m
	const double rho = 2786;							// Dichte in kg/m³
	const double c = 850;								// spezifische Waermekapazität in J/(kg*K)
	const double lambda = 1;							// Waermeleifähigkeit in w/(m*K)
	const double alpha = 15;							// Waermeübergangskoeffizient in W/(m²*K)
	double a = lambda/(rho*c);                          // Temperaturleitfähigkeit in m²/s
	double T_U = 1200;									// Umgebungstemperatur in Kelvin
	double T_ini = 300;									// Starttemperatur in Kelvin
	double delta_r = 0.001;								// Schrittweite in Richtung des Radius
	double t_max = 3600;								// maximale Zeit
	const double Tnull = 273.15;						// maximale Zeit der Berechnung

	

	
//-----------------------------------------------------------------------------------------------------------------------------------------------


int main(void)


    {
	
//-----------------------------------------------------------------------------------------------------------------------------------------------
    //anlegen der Files zur Ausgabe der einzelnen Werte

	FILE *f1;
	FILE *f2;
	FILE *f3;
    FILE *f4;
    FILE *f5;
    FILE *f6;


	
//-----------------------------------------------------------------------------------------------------------------------------------------------	
	
	

    // Berechnung von Fourier- und Biot-Zahl
	double Bi = alpha*delta_r/lambda;

	
	
	//Berechnung der Stabilitaetsbedingungen 
	double delta_t_krit_1 = 0.5 * delta_r * delta_r / a;
	double delta_t_krit_2 = delta_r * delta_r / a * 2 *(1 + Bi) ;
    double delta_t_krit = 1; 
	double Fo = (a * delta_t_krit)/(delta_r * delta_r);
	
	printf("a : %12.3e m*m/s \n", a);
    printf("berechnetes t-krit ohne Berücksichtigung Randbedingung: %8.2f s \n", delta_t_krit_1);
    printf("berechnetes t-krit mit Berücksichtigung Randbedingung: %8.2f s \n", delta_t_krit_2);
    printf(" gewählte t-krit: %8.2f s \n", delta_t_krit);
    printf("Fo = %8.3f\n", Fo);
	printf("Bi = %8.3f\n", Bi);
	
	
//-----------------------------------------------------------------------------------------------------------------------------------------------
	
	//Speicherung
	int m = t_max / delta_t_krit;		//Speichergroesse der Zeit unter Berücksichtigung von delta_t_krit
	double T [n_r +1 ];
	double Talt [n_r +1];
	
	printf("m = %d\n", m);
	
//-----------------------------------------------------------------------------------------------------------------------------------------------	


	//Zeitzaehlschritte
	
	int l_0 = 0/delta_t_krit;
    int l_10 = 10/delta_t_krit;
	int l_60 = 60/delta_t_krit;
	int l_600 = 600/delta_t_krit;
	int l_3600 =  3600/delta_t_krit;
	
	int zeiten[] = {0, 10, 60, 600, 3600}; //Array zur Ausgabe bestimmter Zeiten
    int num_zeiten = sizeof(zeiten) / sizeof(zeiten[0]); 
//_______________________________________________________________________________________________________________________________________________
	
	//Initialisierung der Berechnung
//_______________________________________________________________________________________________________________________________________________


	//Oeffnen und Benennen der Dateien
	f1 = fopen("T_t.dat", "w");
    f2 = fopen("T_r.dat", "w");
    f3 = fopen("T_M.dat", "w");
    f4 = fopen("T_q1.dat", "w");
    f5 = fopen("T_q2.dat", "w");
    f6 = fopen("T_Q.dat", "w");

 

// Initialisierung der Temperatur
    for (i = 0; i < n_r +1; i++) {
        Talt[i] = T_ini;
    }

// Zwischenspeicher Temperaturen

    double gespeicherte_Temperaturen [m+1][n_r+1];


// Berechnung der Temperatur

for (l = 0; l <= m; l++) {
	        

    // RB links
		T[0] = Talt[0];
		gespeicherte_Temperaturen[l][0] = T[0];
	 // RB rechts
    T[n_r] = 2 * Fo * Talt[n_r - 1] + (1. - 2. * Fo * (1. + Bi)) * Talt[n_r] + (2. * Fo * Bi * T_U);
    gespeicherte_Temperaturen[l][n_r] = T[n_r];//geändert

    // Ortsschleife
    for (i = 1; i < n_r; i++) { 

	// Mitte
     T[i] = Fo * Talt[i - 1] + (1. - 2. * Fo) * Talt[i] + Fo * Talt[i + 1];
     
    // Speicherung der Temperatur für alle Aufgaben
        gespeicherte_Temperaturen[l][i] = T[i];
    }
    

	for (i = 0; i < n_r+1; i++) {
		Talt[i] = T[i];
        }   
}

    //_______________________________________________________________________________________________________________________________________________
    //
    //Aufgabe 1 (Ort konstant)
    //_______________________________________________________________________________________________________________________________________________


fprintf(f1,"#Aufgabe 1: T(x,t=const), Zeilen = Ort x in m, Spalten = Zeit t in s\n#Zeit in s:\t");

for(l=0; l<=l_3600; l++)
{
    if(l==l_0 || l == l_10 ||  l==l_60 || l==l_600 || l==l_3600)
    {
        fprintf(f1,"%8d\t", l);
    }
}
fprintf(f1,"\n#r in mm\tT in C:\n");
for(i=0; i<=n_r; i++)
{
    fprintf(f1,"%8.1f\t", i * delta_r * 1e3);
    for(l=0; l<=l_3600; l++)
    {
        if(l==l_0 || l == l_10 || l==l_60 || l==l_600 || l==l_3600)
        {
             fprintf(f1,"%9.3f\t", gespeicherte_Temperaturen[l][i] - Tnull);
        }   
    }
    fprintf(f1,"\n");

}  

    //_______________________________________________________________________________________________________________________________________________
    //
    //Aufgabe 2 (Zeit konstant)
    //_______________________________________________________________________________________________________________________________________________
   


fprintf(f2,"#Aufgabe 2: T(t,x=const), Zeilen = t in s, Spalten = Ort in mm\n#Ort in mm:\t");
  for (i = 0; i <= n_r; i++) {
        if (i == 0 || i == 2 || i == 10 || i == 18 || i == 20) {
            fprintf(f2, "%8.1f\t", i * delta_r * 1e3);
        
        }
  }  
    fprintf(f2, "\n#Zeit in s:\t T in C:");
  for (l = 0; l <= m; l+=120) {
    fprintf(f2, "\n%8d\t", l);

    for (i = 0; i <= n_r; i++) {
        if (i == 0 || i == 2 || i == 10 || i == 18 || i == 20) {
            fprintf(f2, "%9.3f\t", gespeicherte_Temperaturen[l][i] - Tnull);
        }
    }
  }
   
        
    //_______________________________________________________________________________________________________________________________________________
   
    //Aufgabe 3: mittlere Temperatur
    //_______________________________________________________________________________________________________________________________________________
   

  fprintf(f3, "#t in Sekunden \t Tm in Grad Celsius\n");
for (int z = 0; z < num_zeiten; z++) {
    int l = zeiten[z] / delta_t_krit;

    double Tm = 0.0; 
    double V_total = 0.0; 
    
    for (i = 0; i < n_r; i++) {
        double r = i * delta_r; 
        double V = delta_r * r; 
        double Tm_next = gespeicherte_Temperaturen[l][i+1] * V;
        Tm += 0.5 * (gespeicherte_Temperaturen[l][i] * V + Tm_next); 
        V_total += V; 
    }

    Tm /= V_total; 
   
    fprintf(f3, "%d\t %f\n", zeiten[z], Tm - Tnull);
}
	//_______________________________________________________________________________________________________________________________________________
   
    //Aufgabe 4: Berechnnung der Waermestromdichte
    //1.Teil
    //_______________________________________________________________________________________________________________________________________________
   
   //Speicher für die Waermestromdichten und Gradienten
double q_values[m+1][n_r+1];
double grad_T[m+1][n_r+1];  

for (l = 0; l<=m; l++) {
    for (i =0; i<=n_r; i++) {
        if (i == 0) {
            grad_T[l][0] = -(-1.5 * gespeicherte_Temperaturen[l][0] + 2 * gespeicherte_Temperaturen[l][1] - 0.5 * gespeicherte_Temperaturen[l][2]) / delta_r; //FDS2
        } else if (i == n_r) {
            grad_T[l][n_r] = -(1.5 * gespeicherte_Temperaturen[l][n_r] - 2 * gespeicherte_Temperaturen[l][n_r - 1] + 0.5 * gespeicherte_Temperaturen[l][n_r - 2]) / delta_r; //BDS2
        } else {
            grad_T[l][i] = -(gespeicherte_Temperaturen[l][i+1] - gespeicherte_Temperaturen[l][i-1]) / (2 * delta_r); //CDS
        }
    }
}


//finale Berechnung Waermestromdichte

for (l = 0; l <= m; l++) {
    for (i = 0; i <= n_r; i++) {
        q_values[l][i] = -lambda * grad_T[l][i];
       
    }
}
for (i = 0; i <= n_r; i++){
 printf("%f\n", q_values[0][i]);
}

fprintf(f4,"#Aufgabe 4: q(x,t=const), Zeilen = Ort x in m, Spalten = Waermestrom in W/m²\n#Zeit in s:\t");

for(l=0; l<=l_3600; l++)
{
    if(l==l_0 || l == l_10 ||  l==l_60 || l==l_600 || l==l_3600)
    {
        fprintf(f4, "%8d\t", l);
    }
}
fprintf(f4,"\n#r in mm\tq in W/m²:\n\n");
for(i=0; i<=n_r; i++)
{
    fprintf(f4,"%8.1f\t", i * delta_r * 1e3);
    for(l=0; l<=l_3600; l++)
    {
        if(l==l_0 || l == l_10 || l==l_60 || l==l_600 || l==l_3600)
        {
             fprintf(f4,"%9.3f\t", q_values[l][i]);
        }   
    }
    fprintf(f4,"\n");
}  
//_______________________________________________________________________________________________________________________________________________
   
    //Aufgabe 5: Berechnnung der Waermestromdichte
    //2.Teil
//_______________________________________________________________________________________________________________________________________________
   
fprintf(f5,"#Aufgabe 5: T(x,t=const), Zeilen = t in s, Spalten = q in W/m²\n#Ort in mm:\t");
  for (i = 0; i <= n_r; i++) {
        if (i == 0 || i == 2 || i == 10 || i == 18 || i == 20) {
            fprintf(f5, "%8.1f\t", i * delta_r * 1e3);
        }
  }  
    fprintf(f5, "\n#Zeit in s:\t q in W/m²:");
  for (l = 0; l <= m; l+=120) {
    fprintf(f5, "\n%8d\t", l);

    for (i = 0; i <= n_r; i++) {
        if (i == 0 || i == 2 || i == 10 || i == 18 || i == 20) {
            fprintf(f5, "%9.3f\t", q_values[l][i]);
        }
    }
  }
   

//_______________________________________________________________________________________________________________________________________________
    //
    //Aufgabe 5: Berechnen der zugefuehrten Waermemenge pro Laengeneinheit
//_______________________________________________________________________________________________________________________________________________

double Q = 0.0;
double t1 = 0.0;
double t2 = 3600.0;
double dt = t2 - t1;

fprintf(f6, "#Zeit in s\t Q in MJ/m\n");
for (int z = 0; z < 5; z++) {
    for (int i = 0; i < n_r - 1; i++) {
        Q += 0.5 * (q_values[z][i] + q_values[z][i+1]) * dt;
    }
    fprintf(f6, "\n%8d\t", zeiten[z]);
    fprintf(f6, "%f\t", Q/1e6);
    Q = 0.0;
}

// Schliessen der Dateien
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);
    fclose(f6);
    return 0;
}
