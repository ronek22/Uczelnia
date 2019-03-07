/**
 * Algorytmy Numeryczne - Zadanie 2
 * Macierze
 * Autor: Jakub Ronkiewicz, 238155
 * Informatyka: III rok sp. Tester programista gr. 1
 *
 * Generacja Macierzy dla Javy
 * Kompilowac za pomoca polecenia:
 * g++ -I sciezka_do_eigena eig.cpp -std=c++11
 */
#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <random>
#include <fstream>
#include <chrono>
#include <time.h>
#include <windows.h>
using namespace Eigen;
using namespace std;

int MIN_SIZE = 2; // minimalna wielkosc macierzy do testow
int MAX_SIZE = 20; // maksymalna wielkosc macierzy do testow
int TEST_SAME_SIZE = 1; // ilosc testow macierzy tej samej wielkosci
int TEST = 1000; // ilosc pomiarow czasu dla funkcji
double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter(){
	LARGE_INTEGER li;
	if(!QueryPerformanceFrequency(&li))
	cout << "QueryPerformanceFrequency failed!\n";

	 PCFreq = double(li.QuadPart)/1000000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

double GetCounter(){
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}

void test(MatrixXd A, MatrixXd B, MatrixXd C, VectorXd vX, VectorXd vB, int n, ofstream& file) {
	IOFormat CommaInitFmt(17, DontAlignCols, " ", " ", "", "", "", "");

	MatrixXd pr;
	double time[5];
	file << n << endl;

	auto start = chrono::high_resolution_clock::now();
	for(int i = 0; i < TEST; i++)
		pr = A*vX;

	auto finish = chrono::high_resolution_clock::now();
	auto elapsed = chrono::duration_cast<chrono::nanoseconds>(finish - start).count()/TEST;
	file << pr.format(CommaInitFmt) << "|" << elapsed << endl;

	start = chrono::high_resolution_clock::now();
	for(int i = 0; i < TEST; i++)
		pr = ((A + B + C)*vX);
	finish = chrono::high_resolution_clock::now();
	elapsed = chrono::duration_cast<chrono::nanoseconds>(finish - start).count()/TEST;
	file << pr.format(CommaInitFmt) << "|" << elapsed << endl;


	start = chrono::high_resolution_clock::now();
	for(int i = 0; i < TEST; i++)
		pr = (A*(B*C));
	finish = chrono::high_resolution_clock::now();
	elapsed = chrono::duration_cast<chrono::nanoseconds>(finish - start).count()/TEST;
	file << pr.format(CommaInitFmt) << "|" << elapsed << endl;

	start = chrono::high_resolution_clock::now();
	for(int i = 0; i < TEST; i++)
		pr = (A.partialPivLu().solve(vB));
	finish = chrono::high_resolution_clock::now();
	elapsed = chrono::duration_cast<chrono::nanoseconds>(finish - start).count()/TEST;
	file << pr.format(CommaInitFmt) << "|" << elapsed << endl;

	start = chrono::high_resolution_clock::now();
	for(int i = 0; i < TEST; i++)
		pr = (A.fullPivLu().solve(vB));
	finish = chrono::high_resolution_clock::now();
	elapsed = chrono::duration_cast<chrono::nanoseconds>(finish - start).count()/TEST;
	file << pr.format(CommaInitFmt) << "|" << elapsed << endl;
}


void test2(MatrixXd A, MatrixXd B, MatrixXd C, VectorXd vX, VectorXd vB, int n, ofstream& file) {
	//cout.precision(17);
	IOFormat CommaInitFmt(17, DontAlignCols, " ", " ", "", "", "", "");
	// Check Time

	MatrixXd pr1, pr2, pr3, pr4, pr5;
	double elapsed;
	file << n << endl;

	StartCounter();
		pr1 = A*vX;
	elapsed = GetCounter();
	file << pr1.format(CommaInitFmt) << "|" << elapsed << endl;

	StartCounter();
		pr2 = ((A + B + C)*vX);
	elapsed = GetCounter();
	file << pr2.format(CommaInitFmt) << "|" << elapsed << endl;

	StartCounter();
		pr3 = (A*(B*C));
	elapsed = GetCounter();
	file << pr3.format(CommaInitFmt) << "|" << elapsed << endl;

	StartCounter();
		pr4 = (A.partialPivLu().solve(vB));
	elapsed = GetCounter();
	file << pr4.format(CommaInitFmt) << "|" << elapsed << endl;

	StartCounter();
		pr5 = (A.fullPivLu().solve(vB));
	elapsed = GetCounter();
	file << pr5.format(CommaInitFmt) << "|" << elapsed << endl;
}



int main(int, char *[])
{
	// SETUP GENERATORS FOR RANDOM NUMBERS
		vector<int> numerators; //to store the random numbers
		vector<int> denominators;
		vector<int> variables;

		random_device rd; //seed generator
		mt19937_64 generator{ rd() }; //generator initialized with seed from rd
		uniform_int_distribution<> dist_num{ -100, 100 }; //the range is inclusive, so this produces numbers in range [0, 10), same as before
		uniform_int_distribution<> dist_den{ 1, 100 };
	// END-OF-SETUP

		// otwieramy plik z danymi na temat macierzy
		ofstream dane ("danecpp.txt");
		ofstream wyniki("wynikicpp.txt");


		for (int i = MIN_SIZE; i < MAX_SIZE; i++) {
			for (int t = 0; t < TEST_SAME_SIZE; t++) {
				dane << i << endl;
				for (int j = 0; j < i*i; j++) {
					numerators.push_back(dist_num(generator));
					denominators.push_back(dist_den(generator));
				}

				int ind = 0;
				MatrixXd A(i, i);
				for (int row = 0; row < i; row++) {
					for (int col = 0; col < i; col++) {
						dane << numerators[ind] << "/" << denominators[ind] << " "; // do pliku
						A(row, col) = (double)numerators[ind] / denominators[ind]; // do eigena
						ind++;
					}
				}
				dane << endl;

				numerators.clear();
				denominators.clear();

				for (int j = 0; j < i*i; j++) {
					numerators.push_back(dist_num(generator));
					denominators.push_back(dist_den(generator));
				}

				ind = 0;
				MatrixXd B(i, i);
				for (int row = 0; row < i; row++) {
					for (int col = 0; col < i; col++) {
						dane << numerators[ind] << "/" << denominators[ind] << " ";
						B(row, col) = (double)numerators[ind] / denominators[ind];
						ind++;
					}
				}
				dane << endl;


				numerators.clear();
				denominators.clear();


				for (int j = 0; j < i*i; j++) {
					numerators.push_back(dist_num(generator));
					denominators.push_back(dist_den(generator));
				}

				ind = 0;
				MatrixXd C(i, i);
				for (int row = 0; row < i; row++) {
					for (int col = 0; col < i; col++) {
						dane << numerators[ind] << "/" << denominators[ind] << " ";
						C(row, col) = (double)numerators[ind] / denominators[ind];
						ind++;
					}
				}
				dane << endl;

				numerators.clear();
				denominators.clear();


                // GENEROWANIE WEKTOROW
				for (int j = 0; j < i; j++) {
					numerators.push_back(dist_num(generator));
					denominators.push_back(dist_den(generator));
				}

				ind = 0;
				VectorXd vX(i);
				for (int j = 0; j < i; j++) {
					dane << numerators[ind] << "/" << denominators[ind] << " ";
					vX(j) = (double)numerators[ind] / denominators[ind];
					ind++;
				}
				dane << endl;

				numerators.clear();
				denominators.clear();

				//cout << "\nVECTOR X: " << vX << endl;

				for (int j = 0; j < i; j++) {
					numerators.push_back(dist_num(generator));
					denominators.push_back(dist_den(generator));
				}

				ind = 0;
				VectorXd vB(i);
				for (int j = 0; j < i; j++) {
					dane << numerators[ind] << "/" << denominators[ind] << " ";
					vB(j) = (double)numerators[ind] / denominators[ind];
					ind++;
				}
				dane << endl;


				numerators.clear();
				denominators.clear();


				test(A, B, C, vX, vB, i, wyniki);

			}
		}
		dane << 0;
		dane.close();
		wyniki.close();
		cout << "SKONCZONE";

	cin.get();
}
