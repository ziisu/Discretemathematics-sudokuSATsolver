/*
* TEAM 4 - 21600112 김영표/ 21500341 서지수/21600631 정겨운
* Date: 2017.10.11
* Purpose: Solve the given input sudoku file by SAT solver and show the output result
*/

#include <stdio.h>
#include <stdlib.h>

void input2DIMACS(void);
void formulaSATsolver(void);
void sudokuSolution(void);

int main()
{
	input2DIMACS();
	return 0;
}

void input2DIMACS(void)
{
	FILE *input = NULL;
	FILE *formula = NULL;
	char read[200];
	int v[81];
	int readi = 0, temp;
	int p, q = 0;
	int astRow[4];
	int astCol[4];
	int astC = 0;

	//Read input.txt file and get the contents of input file
	input = fopen("input.txt", "r");
	while (!feof(input)) {
		fscanf(input, "%c%*[\n]", &read[readi]);
		readi++;
	}
	//Open formula.txt file to write DIMACS formula
	formula = fopen("formula.txt", "w");
	fprintf(formula, "p cnf 729 \n");

	//Move right, if it meets white space
	for (int i = 0; i < 200; i++) {
		if (read[i] == ' ') {
			for (int j = i; j<200; j++)
				read[j] = read[j + 1];
		}
	}
	//If it meets Asterias
	for (int i = 0; i < 81; i++) {
		if (read[i] == '*') {
			read[i] = '0';      
			temp = i + 1;
			if (temp <= 9) {
				astRow[astC] = 1;
				astCol[astC] = temp;
			}
			else {
				temp += 9;
				astRow[astC] = temp / 9;
				astCol[astC] = temp % 9;
			}
			astC++;
		}
	}

	for (int i = 0; i < 81; i++) {
		v[i] = read[i] - '0';
	}
	for (int i = 0; i < 81; i++) {
		if (v[i] != 0) {
			temp = 9 * i + v[i];
			fprintf(formula, "%d %d \n", temp, 0);
		}
	}
	//Asteria row check
	if (astC == 2) {
		for (int n = 1; n < 10; n++) {
			int c = 0;
			p = -(9 * (astCol[c] - 1) + n + 81 * (astRow[c] - 1));
			fprintf(formula, "%d ", p, 0);
			p = 9 * (astCol[c + 1] - 1) + n + 81 * (astRow[c + 1] - 1);
			fprintf(formula, "%d %d \n ", p, 0);
			p = 9 * (astCol[c] - 1) + n + 81 * (astRow[c] - 1);
			fprintf(formula, "%d ", p);
			p = -(9 * (astCol[c + 1] - 1) + n + 81 * (astRow[c + 1] - 1));
			fprintf(formula, "%d %d \n", p, 0);
		}
	}
	else if (astC == 3) {
		for (int n = 1; n < 10; n++) {
			int c = 0;
			p = -(9 * (astCol[c] - 1) + n + 81 * (astRow[c] - 1));
			fprintf(formula, "%d ", p, 0);
			p = 9 * (astCol[c + 2] - 1) + n + 81 * (astRow[c + 2] - 1);
			fprintf(formula, "%d %d \n ", p, 0);
			p = 9 * (astCol[c] - 1) + n + 81 * (astRow[c] - 1);
			fprintf(formula, "%d ", p);
			p = -(9 * (astCol[c + 1] - 1) + n + 81 * (astRow[c + 1] - 1));
			fprintf(formula, "%d %d \n", p, 0);
			p = 9 * (astCol[c + 1] - 1) + n + 81 * (astRow[c + 1] - 1);
			fprintf(formula, "%d ", p);
			p = -(9 * (astCol[c + 2] - 1) + n + 81 * (astRow[c + 2] - 1));
			fprintf(formula, "%d %d \n", p, 0);
		}
	}
	else if (astC == 4) {
		for (int n = 1; n < 10; n++) {
			int c = 0;
			p = -(9 * (astCol[c] - 1) + n + 81 * (astRow[c] - 1));
			fprintf(formula, "%d ", p, 0);
			p = 9 * (astCol[c + 3] - 1) + n + 81 * (astRow[c + 3] - 1);
			fprintf(formula, "%d %d \n ", p, 0);
			p = 9 * (astCol[c] - 1) + n + 81 * (astRow[c] - 1);
			fprintf(formula, "%d ", p);
			p = -(9 * (astCol[c + 1] - 1) + n + 81 * (astRow[c + 1] - 1));
			fprintf(formula, "%d %d \n", p, 0);
			p = 9 * (astCol[c + 1] - 1) + n + 81 * (astRow[c + 1] - 1);
			fprintf(formula, "%d ", p);
			p = -(9 * (astCol[c + 2] - 1) + n + 81 * (astRow[c + 2] - 1));
			fprintf(formula, "%d %d \n", p, 0);
			p = 9 * (astCol[c + 2] - 1) + n + 81 * (astRow[c + 2] - 1);
			fprintf(formula, "%d ", p);
			p = -(9 * (astCol[c + 3] - 1) + n + 81 * (astRow[c + 3] - 1));
			fprintf(formula, "%d %d \n", p, 0);
		}
	}
	//Row Check
	for (int i = 1; i < 10; i++) {
		for (int n = 1; n < 10; n++) {
			for (int j = 1; j < 10; j++) {
				p = 9 * (j - 1) + n + 81 * (i - 1);
				fprintf(formula, "%d ", p);
			}
			fprintf(formula, "0 \n");
		}
	}
	//Column Check
	for (int j = 1; j < 10; j++) {
		for (int n = 1; n < 10; n++) {
			for (int i = 1; i < 10; i++) {
				p = 9 * (j - 1) + n + 81 * (i - 1);
				fprintf(formula, "%d ", p);
			}
			fprintf(formula, "0 \n");
		}
	}
	//Cube Check
	for (int r = 0; r < 3; r++) {
		for (int s = 0; s < 3; s++) {
			for (int n = 1; n < 10; n++) {
				for (int i = 1; i < 4; i++) {
					for (int j = 1; j < 4; j++) {
						p = 9 * (3 * s + j - 1) + n + 81 * (3 * r + i - 1);
						fprintf(formula, "%d ", p);
					}
				}
				fprintf(formula, "0 \n");
			}
		}
	}
	//Only one value in each cell
	for (int i = 1; i < 10; i++) {
		for (int j = 1; j < 10; j++) {
			for (int n = 1; n < 9; n++) {
				for (int m = n + 1; m < 10; m++) {
					p = -(9 * (j - 1) + n + 81 * (i - 1));
					q = -(9 * (j - 1) + m + 81 * (i - 1));
					fprintf(formula, "%d %d 0 \n", p, q);
				}
			}
		}
	}
	fclose(input);
	fclose(formula);

	//Call z3 SATsolver to solve formula.txt
	formulaSATsolver();
}
void formulaSATsolver(void)
{
	FILE *result = NULL;
	system("z3 -dimacs formula.txt >> result.txt");

	//Call sudokuSolution to interpret result.txt file
	sudokuSolution();
}
void sudokuSolution(void)
{
	FILE *result = NULL;
	FILE *output = NULL;
	int temp;
	int sudoku[730];
	char is_sat[6];
	int k = 1;

	//Open result file and read it 
	result = fopen("result.txt", "r");

	while (!feof(result)) {  //read char type 
		fscanf(result, "%s", &is_sat);
		break;
	}
	while (!feof(result)) {  //read int type
		fscanf(result, "%d", &sudoku[k]);
		k++;
	}

	//Open output file to write sudoku solution
	output = fopen("output.txt", "w");
	
	//If unsat, print "no soultion"
	if (strcmp(is_sat, "unsat") == 0) {
		fprintf(output, "no solution");
	}

	else {  //the case of "sat"
		for (int i = 1; i < 730; i++) {
			if (sudoku[i] > 0) {  //Positive value is answer
				temp = sudoku[i] % 9;
				if (temp == 0)
					fprintf(output, "9 ");
				else
					fprintf(output, "%d ", temp);
			}
			if (i % 81 == 0) {
				fprintf(output, "\n");
			}
		}
	}
	fclose(result);
	fclose(output);
}
