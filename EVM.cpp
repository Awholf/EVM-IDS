#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include<windows.h>
#include<conio.h>
using namespace std;
void gotoxy(int  x, int y)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}
int main() {  
        string nombreProyecto;
        int cantidadHitos;
        string descripcionHeterogeneos;
        string descripcionHomogeneos;
        vector<double> montos;
        double pv = 0.0;
        double bac = 0.0;
        char presupuesto;
        gotoxy(30, 0);
        cout << "Bienvenido al programa de Gestion de Valor Ganado (EVM)" << endl;
        gotoxy(42, 2);
        cout << "DATOS NECESARIOS: " << endl;
        cout << endl;
        cout << "Ingrese el nombre del proyecto: ";
        getline(cin, nombreProyecto);
        cout << endl;
        cout << "Ingrese la cantidad de hitos: ";
        cin >> cantidadHitos;
        while (cantidadHitos <= 0) {
           
            cout << "La cantidad de hitos debe ser mayor que cero. Ingrese nuevamente: ";
            cin >> cantidadHitos;
        }
        cin.ignore();
        char opcionHeterogeneos;
        cout << endl;
        cout << "Los hitos son heterogeneos? (S/N): ";
        cin >> opcionHeterogeneos;
        while (opcionHeterogeneos != 'S' && opcionHeterogeneos != 's' && opcionHeterogeneos != 'N' && opcionHeterogeneos != 'n') {
            cout << "Respuesta inválida. Por favor, ingrese 'S' o 'N': ";
            cin >> opcionHeterogeneos;
        }
        if (opcionHeterogeneos == 'S' || opcionHeterogeneos == 's') {
            for (int i = 0; i < cantidadHitos; i++) {
                double monto;
                cout << "Ingrese el monto para el hito " << i + 1 << ": ";
                cin >> monto;
                while (monto < 0) {
                    cout << "El monto no puede ser negativo. Ingrese nuevamente: ";
                    cin >> monto;
                }

                montos.push_back(monto);
                pv += monto;           
            }
            cout << endl;
            cout << "El valor del PV (Valor Planeado) por hito es: " << endl;
            cout << endl;
            for (int i = 0; i < cantidadHitos; i++) {
                
                cout << "       Hito " << i + 1 << ": " << montos[i] << endl;
            }
            for (double monto : montos) {
                bac += monto;
            }
            cout << endl;
            cout << "El valor del BAC (Budget at Completion) es: " << bac << endl;
            cout << endl;
            cout << "Para continuar por favor verifique que el BAC coincida con el presupuesto general del proyecto. Desea continuar? (S/N): "; cin >> presupuesto;
            while (presupuesto != 'S' && presupuesto != 's' && presupuesto != 'N' && presupuesto != 'n') {
                cout << "Respuesta inválida. Por favor, ingrese 'S' o 'N': ";
                cin >> presupuesto;
            }
            if (presupuesto == 'n' || presupuesto == 'N') {
                exit(0);
            }
        }
        else {
            double monto;
            cout << "Ingrese el monto total: ";
            cin >> monto;
            while (monto < 0) {
                cout << "El monto no puede ser negativo. Ingrese nuevamente: ";
                cin >> monto;
            }
            for (int i = 0; i < cantidadHitos; i++) {
                montos.push_back(monto);
                pv += monto;
            }
            cout << "El valor del PV (Valor Planeado) por hito es: " << endl;
            for (int i = 0; i < cantidadHitos; i++) {
                cout << "Hito " << i + 1 << ": " << montos[i] / cantidadHitos << endl;
            }

            for (int i = 0; i < cantidadHitos; i++) {
                bac = monto;
            }
            cout << "El valor del BAC (Budget at Completion) es: " << bac << endl;
        }
        gotoxy(30, 100);
        cout << "EVALUACION DE HITOS" << endl;
        int opcionEvaluar;
        cout << "\n1.Evaluacion total de hitos. \n2.Evaluacion Parcial de hitos" << endl;
        cout << "  Que opcion elige?: "; cin >> opcionEvaluar;
        while (opcionEvaluar < 0 || opcionEvaluar > 2) {
            cout << "Por favor vuelva a ingresar un valor valido: ";
            cin >> opcionEvaluar;
        }
        if (opcionEvaluar == 1) {
            char opcionTipo;
            cout << "Es un caso tipico o atipico? (T/A): ";
            cin >> opcionTipo;
            while (opcionTipo != 'T' && opcionTipo != 't' && opcionTipo != 'A' && opcionTipo != 'a') {
                cout << "Respuesta inválida. Por favor, ingrese 'T' o 'A': ";
                cin >> opcionTipo;
            }
            vector<double> ev(cantidadHitos);
            vector<double> ac(cantidadHitos);
            for (int i = 0; i < cantidadHitos; i++) {

                cout << "\nHito numero " << i + 1 << endl;
                cout << "Ingrese el valor de EV (Valor Ganado): ";
                cin >> ev[i];

                cout << "Ingrese el valor de AC (Costo Real): ";
                cin >> ac[i];
            }
            cout << endl;
            cout << "\tANALISIS COMPLETO DE HITOS"<<endl; 
            double evcom = 0.0, accom = 0.0;

            for (int i = 0; i < cantidadHitos; i++) {
                evcom += ev[i];
                accom += ac[i];
            }
            cout << "\t======================" << endl;
            cout << "\n1.Variacion del coste (CV): " << endl;
            if ((evcom - accom) >= 0) {
                cout << "Se a detectado una eficiencia de: " << evcom - accom << endl;
            }
            else
                cout << "Se a detectado una ineficiencia de: " << evcom - accom << endl;
            cout << "\t======================" << endl;
            cout << "\n2.Indice de Rendimiento de Costo (CPI): " << endl;
            if ((evcom / accom) > 1) {
                cout << "Se a detectado un rendimiento favorable de " << (evcom / accom) << endl;
            }
            else
                cout << "Se a detectado un rendimiento desfavorable de "<< (evcom / accom) << endl;
            cout << "\t======================" << endl;
            cout << "\n3.Variacion de cronograma (SV): " << endl;
            if ((evcom - pv) > 0) {
                cout << "Se a detectado que el trabajo va por delante del cronograma en "<< evcom - pv << endl;
            }
            else
                cout << "Se a detectado que el trabajo esta retrasado en "<< evcom - (pv) << endl;
            cout << "\t======================" << endl;
            cout << "\n4.Indice de Rendimiento de Programa (SPI): " << endl;
            if ((evcom / pv)> 0) {
                cout << "Se a detectado que existe un rendimiento favorable (progreso) de: " << (evcom / pv) << "%" << endl;
            }
            else
                cout << "Se a detectado que existe un rendimiento desfavorable (progreso) de: " << (evcom / pv) << "%" << endl;
            cout << "\t======================" << endl;
            cout << "\n5.Indice de Rendimiento de Costo para Completar (TCPI): " << endl;
            if ((bac - evcom) / (bac - accom) > 1) {
                cout << "Se a detectado que se necesita un mejor rendimiento para no exceder el presupuesto original en "<< ((bac - evcom) / (bac - accom)) << endl;
            }
            else
                cout << "Se a detectado que el equipo tiene la capacidad de gastar menos de lo planeado para terminar el proyecto dentro del presupuesto establecido en " << ((bac - evcom) / (bac - accom)) << endl;
            cout << "\t======================" << endl;
            cout << " \n6.Costo Estimado al Completar (EAC): " << endl;
            if (opcionTipo == 'T') {
                cout << "Calculo de la EAC: ";
                if ((accom+((bac-evcom)/(evcom/accom))) > 0) {
                    cout << "Se espera que el proyecto se complete por encima del presupuesto planificado en "<< ((accom + ((bac - evcom) / (evcom / accom)))) << endl;
                }
                else
                    cout << "Se espera que el proyecto se complete por debajo del presupuesto planificado en "<< ((accom + ((bac - evcom) / (evcom / accom)))) << endl;
            }
            else if (opcionTipo == 'A') {
                cout << "Calculo de la EAC: " << endl;
                if ((accom + (bac - evcom)) > 0) {
                    cout << "Se espera que el proyecto se complete por encima del presupuesto planificado en "<< (accom + (bac - evcom)) << endl;
                }
                else
                    cout << "Se espera que el proyecto se complete por debajo del presupuesto planificado en "<< (accom + (bac - evcom)) << endl;
            }
            cout << "\t======================" << endl;
            cout << "\n7.Costo Estimado para Terminar (ETC): ";
            if (opcionTipo == 'T') {
                cout << "Calculo de la ETC: " << endl;
                if ((bac - evcom )/ (evcom / accom) > 0) {
                    cout << "El proyecto excedera a su presupuesto en: " << ((bac - evcom) / (evcom / accom)) << endl;
                }
                else
                    cout << "El proyecto tendra un ahorro de: " << ((bac - evcom) / (evcom / accom)) * (-1) << endl;
            }
            else if (opcionTipo == 'A') {
                cout << "Calculo de la ETC: " << endl;
                if ((bac - evcom) > 0) {
                    cout << "Se espera que el proyecto se complete por encima del presupuesto planificado en " << bac - evcom << " indica una situacion desfavorable" << endl;
                }
                else
                    cout << "Se espera que el proyecto se complete por debajo del presupuesto planificado." << bac - evcom << " indica ahorro en el presupuesto total del proyecto." << endl;
            }
            cout << "\t======================" << endl;
            cout << "\n8.Variacion a la conclusion (VAC): ";
            if (opcionTipo == 'T') {
                cout << "Calculo de la VAC: " << endl;
                if ((bac - (accom + ((bac - evcom) / (evcom / accom)))) > 0) {
                    cout << "Se puede apreciar que el costo es mucho menor al presupuestado en " << (bac - (bac / (evcom / accom))) << endl;
                }
                else
                    cout << "Se puede apreciar que el costo es mucho mayor al presupuestado en  " << (bac - (bac / (evcom / accom))) * (-1) << endl;

            }
            else if (opcionTipo == 'A') {
                cout << "Calculo de la VAC: "<<endl;
                if ((bac - (accom + (bac - evcom))) > 0) {
                    cout << "Se puede apreciar que el costo es mucho menor al presupuestado en "<< ((bac - (accom + (bac - evcom)))) <<endl;
                }
                else
                    cout << "Se puede apreciar que el costo es mucho mayor al presupuestado en "<< ((bac - (accom + (bac - evcom)))) <<endl;

            }
            cout << "\t======================" << endl;
        }
        if (opcionEvaluar == 2) {
            int H_a;
            char opcionTipo;
            cout << "Ingrese hasta que hito desea el analisis: "; cin >> H_a;
            while (H_a < 0 || H_a > cantidadHitos) {
                cout << "Por favor vuelva a ingresar un valor valido: ";
                cin >> H_a;
            }
            cout << "Es un caso tipico o atipico? (T/A): ";
            cin >> opcionTipo;
            while (opcionTipo != 'T' && opcionTipo != 't' && opcionTipo != 'A' && opcionTipo != 'a') {
                cout << "Respuesta inválida. Por favor, ingrese 'T' o 'A': ";
                cin >> opcionTipo;
            }
            vector <double> evs(cantidadHitos);
            vector <double> acs(cantidadHitos);
            bool exit = true;
            char respuesDeSalida;
            do {
                for (int i = 0; i < H_a; i++)
                {
                    cout << "\t===== Hito ===== " << i + 1 << " =====" << endl;
                    cout << "Ingrese el valor del EV: "; cin >> evs[i];
                    cout << "Ingrese el valor del AC: "; cin >> acs[i];
                }
                cout << "  EVS " << "   " << "  ACS " << endl;
                for (int i = 0; i < H_a; i++) {

                    cout << "   " << evs[i] << "   " << "     " << acs[i] << endl;

                }
                cout << "¿Desea rehacer el llenado de los datos? (S/N) :"; cin >> respuesDeSalida;
                if (respuesDeSalida == 'S' || respuesDeSalida == 's') {
                    exit = false;
                }
                else if (respuesDeSalida == 'N' || respuesDeSalida == 'n') {
                    exit = true;
                }
            } while (exit == false);
            cout << "\nEl analisis hasta el hito numero " << H_a << " es el siguiente: " << endl;
            cout << "\t======================" << endl;
            cout << "\n1.Variacion del coste (CV): " << endl;
            double ev = 0.0;
            double ac = 0.0;
            double mnts = 0.0;
            for (int i = 0; i < H_a; i++) {
                ev = (evs[i] += 1);
                ac = (acs[i] += 1);
                mnts = (montos[i] += 1);
            }
            if ((ev - ac) >= 0) {
                cout << "Se a detectado una eficiencia de: " << ev - ac << endl;
            }
            else
                cout << "Se a detectado una ineficiencia de: " << ev - ac << endl;
            cout << "\t======================" << endl;
            cout << "\n2.Indice de Rendimiento de Costo (CPI): " << endl;
            if ((ev / ac) > 1) {
                cout << "Se a detectado un rendimiento favorable en un "<< (ev / ac)*100<<"%. "<< endl;
            }
            else
                cout << "Se a detectado un rendimiento desfavorable en un " << (ev / ac) * 100 << "%. " << endl;
            cout << "\t======================" << endl;
            cout << "\n3.Variacion de cronograma (SV): " << endl;
            if ((ev - mnts ) > 0) {
                cout << "Se a detectado que el trabajo va por delante del cronograma en "<< (ev - mnts) << endl;
            }
            else
                cout << "Se a detectado que el trabajo esta retrasado en " << (ev - (mnts / cantidadHitos)) << endl;
            cout << "\t======================" << endl;
            cout << "\n4.Indice de Rendimiento de Programa (SPI): " << endl;
            if (ev / ac > 0) {
                cout << "Se a detectado que existe un rendimiento favorable (progreso) de: " << (ev / ac) << "%" << endl;
            }
            else
                cout << "Se a detectado que existe un rendimiento desfavorable (progreso) de: " << (ev / ac) << "%" << endl;
            cout << "\t======================" << endl;
            cout << "\n5.Indice de Rendimiento de Costo para Completar (TCPI): " << endl;
            if ((bac - ev) / (bac - ac) > 1) {
                cout << "Se a detectado que se necesita un mejor rendimiento para no exceder el presupuesto original de a´" << endl;
            }
            else
                cout << "Se a detectado que el equipo tiene la capacidad de gastar menos de lo planeado para terminar el proyecto dentro del presupuesto establecido. " << endl;
            cout << "\t======================" << endl;
            cout << " \n6.Costo Estimado al Completar (EAC): ";
            if (opcionTipo == 'T') {
                cout << "El calculo de la EAC sera: " << endl;
                if (ac + ((bac-ev)/(ev/ac)) > 0) {
                    cout << "Se espera que el proyecto se complete por encima del presupuesto planificado en "<< (ac + ((bac - ev) / (ev / ac))) << endl;
                }
                else
                    cout << "Se espera que el proyecto se complete por debajo del presupuesto planificado en " << (ac + ((bac - ev) / (ev / ac))) << endl;
            }
            else if (opcionTipo == 'A') {
                cout << "El calculo de la EAC sera: " << endl;
                if ((ac + (bac - ev)) > 0) {
                    cout << "Se espera que el proyecto se complete por encima del presupuesto planificado en "<< ((ac + (bac - ev))) << endl;
                }
                else
                    cout << "Se espera que el proyecto se complete por debajo del presupuesto planificado en " << ((ac + (bac - ev))) << endl;
            }
            cout << "\t======================" << endl;
            cout << "\n7.Costo Estimado para Terminar (ETC): ";
            if (opcionTipo == 'T') {
                cout << "El calculo de la ETC sera: " << endl;
                if (bac - ev / (ev / ac) > 0) {
                    cout << "El proyecto excedera a su presupuesto en: " << bac - ev / (ev / ac) << endl;
                }
                else
                    cout << "El proyecto tendra un ahorro de: " << bac - ev / (ev / ac) * (-1) << endl;
            }
            else if (opcionTipo == 'A') {
                cout << "El calculo de la ETC sera: "<<endl;
                if ((bac - ev) > 0) {
                    cout << "Se espera que el proyecto se complete por encima del presupuesto planificado en " << bac - ev << " indica una situacion desfavorable" << endl;
                }
                else
                    cout << "Se espera que el proyecto se complete por debajo del presupuesto planificado." << bac - ev << " indica ahorro en el presupuesto total del proyecto." << endl;
            }
            cout << "\t======================" << endl;
            cout << "\n8.Variacion a la conclusion (VAC): ";
            if (opcionTipo == 'T') {
                cout << "El calculo de la VAC sera: "<< endl;
                if (bac - (ac + ((bac - ev) / (ev / ac))) > 0) {
                    cout << "Se puede apreciar que el costo es mucho menor al presupuestado en "<< (bac - (bac / (ev / ac))) <<endl;
                }
                else
                    cout << "Se puede apreciar que el costo es mucho mayor al presupuestado en " << (bac - (bac / (ev / ac))) << endl;

            }
            else if (opcionTipo == 'A') {
                cout << "El calculo de la VAC sera: " << endl;
                if ((bac - (ac + (bac - ev))) > 0) {
                    cout << "Se puede apreciar que el costo es mucho menor al presupuestado en "<< (bac - (ac + (bac - ev))) <<endl;
                }
                else
                    cout << "Se puede apreciar que el costo es mucho mayor al presupuestado en " << (bac - (ac + (bac - ev))) << endl;

            }
            cout << "\t======================" << endl;
        }
        cout << endl;
        cout << "Fin del analisis, agradecemos su tiempo y confiablididad. " << endl;    
    return 0;
}
