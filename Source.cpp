#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>
#define PI 3.14159265\

double Rastr(double x) {
	return (10 + (pow(x, 2) - 10 * cos(2 * PI * x)));
}

void FileCleanUp(std::string s) {
    std::ofstream f;
    f.open(s, std::ofstream::out);
    f.close();
}

int main() {

    //srand(time(0)); //Turning on the continious randomizer for rand() function

	const int b = 5.12 * 2 / 0.01 + 1; //number of elements in x array
    double *x = new double[b];
    double *y = new double[b];
	int d = 100;	//a divider for creating the float array

    //Deleting the mom, dad and kid files if exist. If don't exist they will be created
    std::ofstream mom;
    std::ofstream dad;
    std::ofstream kid;
    std::ofstream minim;

    FileCleanUp("Mom.txt");
    FileCleanUp("Dad.txt");
    FileCleanUp("Kid.txt");
    FileCleanUp("Min.txt");

	std::ofstream orig;
    orig.open("RastrDan.txt");

	//Setting the x array for plotting the initial function
	for (int i = 0; i < b; i++) {
		x[i] = (-5.12) + 0.01 * i;
		y[i] = Rastr(x[i]);
		orig << x[i] << " " << y[i] << std::endl;
	}
	
	orig.close();

	//Creating an array of random X - points, that might be a minimum
	//SETTING THE FIRST POPULATION
	int n1 = 41; //number of individuals
	//random array of X
	double *x1 = new double[n1];
    double *y1 = new double[n1];

    for (int i = 0; i < n1; i++) {
        x1[i] = 0.0;
        y1[i] = 0.0;
    }

	int res, bol;
	std::cout << "\nThe first population\n";

	for (int i = 0; i < n1; i++) {
		x1[i] = rand() % 512;
		res = rand() % 2; //boolean randomizer imitation
		if (res == 0) {
			x1[i] = x1[i] / (-100);
		}
		else if (res == 1) {
			x1[i] = x1[i] / 100;
		};

        y1[i] = Rastr(x1[i]);
		//std::cout << res << std::endl;
		//std::cout << x1[i] << std::endl;
	}

    //MAIN CYCLE

    int limit = 100;
    int mind, maxd;
 
    for (int f = 0; f < limit; f++) {
        
        mind = 0;
        maxd = 0;

        std::cout << "\nPopulation " << f << std::endl;
        for (int i = 0; i < n1; i++) {
            y1[i] = Rastr(x1[i]); //The Y for this population's X
            std::cout << x1[i] << " " << y1[i] << std::endl;

            //Founding minimum
            if (y1[i] < y1[mind]) {
                mind = i;
            }

            //Founding maximum
            if (y1[i] > y1[maxd]) {
                maxd = i;
            }
        }

        std::cout << "\nThe minimum in Population " << f << " is X = " << x1[mind] 
            << " Y = " << y1[mind] << std::endl;
        std::cout << "The maximum in Population " << f << " is X = " << x1[maxd]
            << " Y = " << y1[maxd] << std::endl;

        //Writing the Min file
        minim.open("Min.txt", std::ios::app);
        minim << x1[mind] << " " << y1[mind] << std::endl;
        minim.close();

        //Checking if the current minimum answers our preffered accuracy
        if ((abs(x1[mind]) < 0.01) && (abs(y1[mind]) < 0.01)) {
            std::cout << "\nThe global minimum found after " << f << " loops, it's X = " 
                << x1[mind] << " Y = " << y1[mind] << std::endl;
            break;
        }

        //Setting Mom and Dad as 2 random elements of the population

        //MOM
        mom.open("Mom.txt", std::ios::app);
        int num = rand() % (n1 - 1);
        double *MOM = new double;
        MOM = &x1[num];
        double *Ym = new double;
        Ym = &y1[num];
        std::cout << "Mom X = " << *MOM << " Y = " << *Ym << std::endl;

        mom << *MOM << " " << *Ym << std::endl;
        mom.close();

        //DAD
        dad.open("Dad.txt", std::ios::app);
        int nud = rand() % (n1 - 1);
        double* DAD = new double;
        DAD = &x1[nud];
        double* Yd = new double;
        Yd = &y1[nud];
        std::cout << "Dad X = " << *DAD << " Y = " << *Yd << std::endl;

        dad << *DAD << " " << *Yd << std::endl;
        dad.close();

        //KID
        kid.open("Kid.txt", std::ios::app);
        double KID, Yk, koef1, koef2, testk;
        koef1 = (rand() % 100) / double(100);
        koef2 = (rand() % 100) / double(100);
        KID = koef1 * (*MOM) + koef2 * (*DAD);
        Yk = Rastr(KID);
        std::cout << "KID X = " << KID << " Y = " << Yk << std::endl;

        kid << KID << " " << Yk << std::endl;
        kid.close();
        
        //Replacing the worst element of the population with the kid
        x1[maxd] = KID;
        y1[maxd] = Rastr(x1[maxd]);

    };

    delete[] x, y, x1, y1;
	return 0;
}
