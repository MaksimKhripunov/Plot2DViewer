#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H


Matrix<> Translation(double x, double y)
{
	double T[9] = {
		1, 0, x,
		0, 1, y,
		0, 0, 1};
	return Matrix<>(3,3, T);
}

Matrix<> Identity()
{
	double T[9] = {
		1, 0, 0,
		0, 1, 0,
		0, 0, 1 };
	return Matrix<>(3, 3, T);
}

Matrix<> Rotation(int t)
{
	double T[9] = {
		cos(t), -sin(t), 0,
		sin(t), cos(t), 0,
		0, 0, 1 };
	return Matrix<>(3, 3, T);
}

Matrix<> Rotation(double c, double s)
{
	double T[9] = {
		c, -s, 0,
		c, s, 0,
		0, 0, 1 };
	return Matrix<>(3, 3, T);
}

Matrix<> Scaling(double kx, double ky)
{
	double T[9] = {
		kx, 0, 0,
		0, ky, 0,
		0, 0, 1 };
	return Matrix<>(3, 3, T);
}

// ����� ��������� ����������� �������, ������������ ������� ������� ��:
// Identity() - ������������� ��;
// Rotation(t) - ������� �� ���� t;
// Rotation(c, s) - ������� �� ����, ������� � ����� �������� ��������������� ��������� c � s;
// Scaling(kx, ky) - ���������������;
// Mapping (��������� ���� ���������) - �� �������, ��� �������� ������ ��������� ����� ������������ ������� Scaling.

// � ���������� ������� ������������ ����������� ������� �� ������.
// �������������� ���� � ������ �������� �������� ������.
// ��������, ����� �������, ��������� ��������� �������,
// � ����������� ���������������� ��������� � �������������.

#endif AFFINE_TRANSFORM_H
