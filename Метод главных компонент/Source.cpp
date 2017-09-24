#include <iostream> 
#include <cmath> 

using namespace std;

// ����� ������ ������� ��������� 
class PCA {
private:
	int row; // ���������� ����� 
	int column; // ���������� �������� 
	double **arr; // ������������ ������ �������� ������� 
	double *mean_values; // ������������ ������ ������� �������� �������� 
	double **centered; // ������������ ������ �������������� �������� 
	double *expectation; // �������������� �������� 
	double *dispersion; // ��������� 
	double **covmat; // �������������� ������� 
	double EPSILON;  // ����������� ���������
	double *eigvalue;  // ����������� ��������
public:
	void init(int i, int j) { // ����������� ������ 
		EPSILON = 0.001;
		row = i; // �������������� ��������� ������� 
		column = j;

		// ������� ��������� ������ �������� ������ 
		arr = new double *[row]; // ���������� ����� � ������� 
		for (int count = 0; count < row; count++)
			arr[count] = new double[column]; // � ���������� �������� 

	   // ������� ��������� ������ �������������� �������� (��� �� ��� � �������� ������) 
		centered = new double*[row];
		for (int count = 0; count < row; count++)
			centered[count] = new double[column];

		// ������� ��������� ������ �������������� ����� �������������� ������� 
		covmat = new double*[column];
		for (int count = 0; count < column; count++)
			covmat[count] = new double[column];

		// ������� ������ ������� �������� 
		for (int count = 0; count < row; count++)
			mean_values = new double[column];

		// ������� ������ ���. �������� 
		for (int count = 0; count < row; count++)
			expectation = new double[column];

		// ������� ������ ��������� 
		for (int count = 0; count < row; count++)
			dispersion = new double[column];

		// ������� ������ ����������� ��������
		for (int count = 0; count < row; count++)
			eigvalue = new double[column];

		//��������� �������� ����, ���������� �� ���� ������ � �������-------� 
		for (int i = 0; i < row; i++)
			for (int j = 0; j < column; j++)
				cin >> arr[i][j];
		//-------------------------------------------------------------------� 

		//��������� �������� ����, ���������� �� ����� ������ �-------------� 
		cout << "Matrix:" << endl;
		for (int i = 0; i < row; i++)
		{
			cout << endl;
			for (int j = 0; j < column; j++)
				cout << arr[i][j] << " ";
		}
		cout << endl;
		//-------------------------------------------------------------------� 
	}
	float sqr(float a) {
		return a * a;
	}
	void mean_func() {//�����, ��������� ������� �������� ��� ������� ������� 
		double sum;
		for (int i = 0; i < column; i++) {
			sum = 0;
			for (int j = 0; j < row; j++)
				sum += arr[j][i];
			mean_values[i] = sum / row;
		}
		//��������� ���---------------------------------------------------� 
		for (int i = 0; i < column; i++) {
			cout << endl;
			cout << "mean_value [" << i << "]" << "= " << mean_values[i];
		}
		cout << endl;
		//----------------------------------------------------------------� 
	}
	void centered_func() {

		for (int i = 0; i < row; i++) // ������������� �������� 
			for (int j = 0; j < column; j++)
				centered[i][j] = arr[i][j];
		for (int i = 0; i < row; i++)
			for (int j = 0; j < column; j++)
				centered[i][j] -= mean_values[j];

		for (int i = 0; i < column; i++) { // ��� �������� 
			expectation[i] = 0;
			for (int j = 0; j < row; j++)
				expectation[i] += centered[j][i];
			expectation[i] = expectation[i] / row;

		}
		//��������� ���---------------------------------------------------� 
		cout << endl << "centered mass:";
		for (int i = 0; i < row; i++) {
			cout << endl;
			for (int j = 0; j < column; j++)
				cout << centered[i][j] << " ";
		}
		cout << endl << "expectation:";
		for (int i = 0; i < column; i++) {
			cout << expectation[i] << " ";
		}
		cout << endl;
		//----------------------------------------------------------------� 
	}
	void dispersion_func() {
		for (int i = 0; i < column; i++) {
			dispersion[i] = 0;
			for (int j = 0; j < row; j++)
				dispersion[i] += pow((centered[j][i] - expectation[i]), 2);
			dispersion[i] = dispersion[i] / (row - 1);
		}
		//��������� ��� 
		cout << endl;
		cout << "dispersion:" << endl;
		for (int i = 0; i <
			column; i++) {
			cout << dispersion[i] << " ";
		}
		cout << endl;
		//-----------� 
	}
	void covmat_func() {
		for (int i = 0; i < column; i++)
			for (int j = 0; j < column; j++) {
				covmat[i][j] = 0;
				for (int n = 0; n < row; n++)
					covmat[i][j] += centered[n][i] * centered[n][j];
				covmat[i][j] = covmat[i][j] / (row - 1);
			}
		//��������� ��� 
		cout << endl;
		cout << "covmat:" << endl;
		for (int i = 0; i < column; i++) {
			cout << endl;
			for (int j = 0; j < column; j++)
				cout << covmat[i][j] << " ";
		}
		//-----------� 
	}
	void eigenvalues() {
		// ���� ������������ �� ������ ������� � �������������� �������
		int ii;
		int jj;
		double min = 10;
		double amax = 0.1 * EPSILON;
		double **a;
		int count = 0;

		// ������� ��������� ������ a
		a = new double*[column];
		for (int count = 0; count < column; count++)
			a[count] = new double[column];

		double **u;
		double **ut;  //����������������� ������� U
		// ������� ��������� ������ U

		u = new double*[column];
		for (int count = 0; count < column; count++)
			u[count] = new double[column];

		// ������� ��������� ������ Ut
		ut = new double*[column];
		for (int count = 0; count < column; count++)
			ut[count] = new double[column];

		// ������� ��������� ������ a1
		double **a1;
		a1 = new double*[column];
		for (int count = 0; count < column; count++)
			a1[count] = new double[column];

		// �������� ����
		do {
			count += 1;
			double amax = 0.1 * EPSILON;
			for (int i = 0; i < column; i++)
				for (int j = 0; j < column; j++) {
					if (j > i) {
						if (fabs(amax) < fabs(a[i][j])) {
							amax = a[i][j];
							ii = i;
							jj = j;
						}
						else continue;
					}
				}
			double f = 1 / 2 * atan((2 * amax) / (a[ii][ii] - a[jj][jj]));
			double cosinus = cos(f);
			double sinus = sin(f);
			// ����������� ��������
			for (int i = 0; i < column; i++)
				for (int j = 0; j < column; j++) {
					if (i = j) {					 // ������ ����������� ��������
						eigvalue[i] = a[i][j];  // �������� �� ������� ��������� 
					}
				}
			// ������ ������� U
			// �������������� ������� U ������
			for (int i = 0; i < column; i++)
				for (int j = 0; j < column; j++)
					u[i][j] = 0;
			for (int i = 0; i < column; i++)
				for (int j = 0; j < column; j++) {
					if (i = j) {
						u[i][j] = 1;
					}
					if (i = ii) {
						u[i][i] = cosinus;
					}
					if (i = jj) {
						u[i][jj] = cosinus;
					}
					if ((j = jj) && (i = ii)) {
						u[i][j] = -sinus;
						u[j][i] = sinus;
					}
				}
			// ��������� ������� ��������
			for (int i = 0; i < column; i++)
				for (int j = 0; j < column; j++) {
					if (j > i) {
						if ((u[i][j] != 0) && (u[i][j] != 1) && (fabs(min) > fabs(u[i][j]))) {
							min = u[i][j];
						}
						else continue;
					}
				}
			// ���� ����������������� ������� U
			for (int i = 0; i < column; i++)
				for (int j = 0; j < column; j++) {
					ut[j][i] = u[i][j];
				}
			// ��������� ��������: Ut*a*U 
			for (int i = 0; i < column; i++)
				for (int j = 0; j < column; j++) {
					a1[i][j] = 0;
					for (int k = 0; k < column; k++) {
						a1[i][j] = a1[i][j] + ut[i][k] + a[k][j];
					}
				}
			for (int i = 0; i < column; i++)
				for (int j = 0; j < column; j++) {
					a[i][j] = 0;
					for (int k = 0; k < column; k++) {
						a[i][j] += a1[i][k] * u[k][j];
					}
				}
			// ������� ����������� �������
			double **u1;
			double **u2;

			// ������� u1
			u1 = new double*[column];
			for (int count = 0; count < column; count++)
				u1[count] = new double[column];

			// ������� U2
			u2 = new double*[column];
			for (int count = 0; count < column; count++)
				u2[count] = new double[column];

			if (count = 1) {
				for (int i = 0; i < column; i++)
					for (int j = 0; j < column; j++) {
						u1[i][j] = u[i][j];
					}
			}
			else {
				for (int i = 0; i < column; i++)
					for (int j = 0; j < column; j++) {
						u2[i][j] = 0;
						for (int k = 0; k < column; k++) {
							u2[i][j] += u1[i][k] * u[k][j];
						}
					}
				for (int i = 0; i < column; i++)
					for (int j = 0; j < column; j++) {
						u1[i][j] = u2[i][j];
					}
			}
			//���������� ��������� ������� ����������� ��������
			/*float temp;
			for (int j = 0; j < column; j++)
				for (int i = 0; i < (column - 1); i++) {
					if (eigvalue[i] < eigvalue[i + 1]) {
						temp = eigvalue[i];
						eigvalue[i] = eigvalue[i + 1];
						eigvalue[i + 1] = temp;
						swap(u1, i);
					}
				}*/
		} while (fabs(min) > EPSILON);
		// ��������� �������� ����
		// ������� ������ ����������� ��������
		cout << endl;
		cout << "eigvalue:" << endl;
		for (int i = 0; i <
			column; i++) {
			cout << eigvalue[i] << " ";
		}
		cout << endl;
		//----------------------------------
	}
	/*void swap(float **a, int i) {
		int j;
		// ������������� ������ eigvec
		float eigvec[1];
		for (int i = 0; i < sizeof(eigvec); i++)
			eigvec[i] = a[i][j];
	}
	*/
}; 
int main()
{
	PCA pca_obj;
	PCA* p_pca_obj = &pca_obj; // ��������� �� ������ 
							   //������� ������ (������� ������, ����� �������) 
	pca_obj.init(3, 4);
	pca_obj.mean_func();
	pca_obj.centered_func();
	pca_obj.dispersion_func();
	pca_obj.covmat_func();
	pca_obj.eigenvalues();
	int a;
	cin >> a;
	return 0;
}