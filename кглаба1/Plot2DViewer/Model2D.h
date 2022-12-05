#ifndef MODEL_2D_H
#define MODEL_2D_H
#include <string>
#include <fstream>
#include "Matrix.h"
#include "AffineTransform.h"

class Model2D
{
private:
	Matrix<> Vertices;
	Matrix<> Edges;
    Matrix<> CumulativeAT;
    Matrix<> InitialVertices;
    double u3;
public:
	Model2D() : Vertices(), Edges(), CumulativeAT(Identity()), InitialVertices(), u3(1) {};
    Model2D(const Matrix<> Vertices, const Matrix<> Edges) : Vertices(Vertices), Edges(Edges), CumulativeAT(Identity()), InitialVertices(Vertices) { u3 = this->Vertices(1, 3); }
	Model2D(string, string, double);
	Matrix<> GetVertices() { return Vertices; }
	Matrix<> GetEdges() { return Edges; }
    double GetVertexX(int);
    double GetVertexY(int);
    void Apply(Matrix<>);
    void Transfer(double x, double y);
};

Model2D::Model2D(string vertex, string edges, double _u3) : CumulativeAT(Identity())
{
    u3 = _u3;
    string line;
    int count = 0;
    ifstream in("D:\\labacg\\"+vertex+".txt"); //in1 è in !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if (in.is_open())
    {
        while (getline(in, line))
        {
            for (int i=0;i<line.size();i++)
                if(line[i]==';')
                    count++;
           
        }
    }
    in.close();
    in.open("D:\\labacg\\" + vertex + ".txt");
    double* x = new double[count];
    double* y = new double[count];
    string str;
    if (in.is_open())
    {
        while (getline(in, line))
        {
           int i = 0,j=0;
           while (i < line.size())
           {
               while (i < line.size() && line[i] != '.')
               {
                   str += line[i];
                   i++;
               }
               x[j] = stod(str);
               i++;
               str = "";
               while (i < line.size() && line[i] != ';')
               {
                   str += line[i];
                   i++;
               }
               y[j] = stod(str);
               i++;
               j++;
               str = "";
           }
           
        }
    }
    in.close();
    
    double* u = new double[3 * count];

    for (int i = 0; i < count; i++)
    {
        u[i] = x[i]*_u3;
        u[count + i] = y[i]*_u3;
        u[2 * count + i] = _u3;
    }
    InitialVertices = *new Matrix<>(3,count,u);
    Vertices = InitialVertices;
//////
    count = 0;

    in.open("D:\\labacg\\" + edges+".txt");
    
    if (in.is_open())
    {
       
        while (getline(in, line))
        {
            for (int i = 0; i < line.size(); i++)
                if (line[i] == ';')
                    count++;

        }
    }
    in.close();

    in.open("D:\\labacg\\" + edges + ".txt");
     x = new double[count];
     y = new double[count];
     str="";
     if (in.is_open())
     {
         while (getline(in, line))
         {
             int i = 0, j = 0;
             while (i < line.size())
             {
                 while (i < line.size() && line[i] != '.')
                 {
                     str += line[i];
                     i++;
                 }
                 x[j] = stod(str);
                 i++;
                 str = "";
                 while (i < line.size() && line[i] != ';')
                 {
                     str += line[i];
                     i++;
                 }
                 y[j] = stod(str);
                 i++;
                 j++;
                 str = "";
             }

         }
     }
     in.close();

     u = new double[2 * count];

     for (int i = 0; i < count; i++)
     {
         u[2*i] = x[i];
         u[2 * i + 1] = y[i];
     }
     Edges = *new Matrix<>(count, 2, u);
}

double Model2D:: GetVertexX(int position)
{
   return Vertices(1, position+1)/ Vertices(3, position + 1);
}
double Model2D::GetVertexY(int position)
{
    return Vertices(2, position + 1)/ Vertices(3, position + 1);
}
void Model2D::Apply(Matrix<> matrix)
{
    CumulativeAT = matrix * CumulativeAT;
    Vertices = CumulativeAT * InitialVertices;
}

void Model2D::Transfer(double x, double y)
{
    int count = Vertices.getCols();
    double* u = new double[3*count];
    for (int i = 0; i < count; i++)
    {
        u[i] = x * u3;
        u[count + i] = y * u3;
        u[2 * count + i] = 0;
    }
    Matrix<> InitialVertices1 = *new Matrix<>(3, count, u);
    
    InitialVertices = InitialVertices + InitialVertices1;
    Vertices = InitialVertices;
  
}




#endif MODEL_2D_H