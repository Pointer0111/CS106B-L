#include "Plotter.h"
#include <strlib.h>
using namespace std;

void MoveAbs(double pos[], double x, double y, int status, PenStyle style);
void MoveRel(double pos[], double x, double y, int status, PenStyle style);
void PenDown(int &status);
void PenUp(int &status);
void PenColor(string color, PenStyle &style);
void PenWidth(double width, PenStyle &style);


void runPlotterScript(istream& input) {
    // Initialize the plotter
    PenStyle style = {1, "black"};
    double pos[2] = {0, 0};
    int status = 0;//0 stands for penup, 1 stands for pendown

    for (string line; getline(input, line); ) {
        Vector<string> v = stringSplit(line, " ");
        if (startsWith(toLowerCase(v[0]), "moveabs")) {
            MoveAbs(pos, stringToReal(v[1]), stringToReal(v[2]), status, style);
            pos[0] = stringToReal(v[1]);
            pos[1] = stringToReal(v[2]);
        }
        else if (startsWith(toLowerCase(v[0]), "moverel")){
            MoveRel(pos, stringToReal(v[1]), stringToReal(v[2]), status, style);
            pos[0] += stringToReal(v[1]);
            pos[1] += stringToReal(v[2]);
        }
        else if (startsWith(toLowerCase(v[0]), "pendown")) PenDown(status);

        else if (startsWith(toLowerCase(v[0]), "penup")) PenUp(status);

        else if (startsWith(toLowerCase(v[0]), "penwidth")) PenWidth(stringToReal(v[1]), style);

        else if (startsWith(toLowerCase(v[0]), "pencolor")) PenColor(v[1], style);
    }

}

void MoveAbs(double pos[], double x, double y, int status, PenStyle style){
    if (status) drawLine(pos[0], pos[1], x, y, style);
    return;
}

void MoveRel(double pos[], double x, double y, int status, PenStyle style){
    if (status) drawLine(pos[0], pos[1], pos[0] + x, pos[1] + y, style);
    return;
}

void PenDown(int &status){
    status = 1;
}

void PenUp(int &status){
    status = 0;
}

void PenColor(string color, PenStyle &style){
    style.color = color;
}

void PenWidth(double width, PenStyle &style){
    style.width = width;
}

