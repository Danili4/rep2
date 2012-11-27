#ifndef _EVAL_H
#define _EVAL_H
#include <math.h>
double etaTwoRecognition(double etaTwoStar, double k);
double annTwoRecognition(double alpha, double etaTwo,
            double mu, double delta, double step);
double annRecognition(double annTwo, double alpha);
double etaOneRecognition(double annTwo, double alpha, double delta, double step);
double vRecognition(double ann, double etaOne, double etaTwo);
double tRecognition(double v, double mu, double s);
#endif