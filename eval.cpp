#include "eval.h"

double etaTwoRecognition(double etaTwoStar, double k)
{
        return (etaTwoStar * (k * (log10(etaTwoStar)/log10(2.0)) + 1.0));
}

double annTwoRecognition(double alpha, double etaTwo,
            double mu, double delta, double step)
{
        double annTwo = 300.0;
        double difference;
        double a = 1.0 - (log10(alpha)) / (log10(1.0 + alpha));
        double b = 2.0 * (log10(annTwo)) / (log10(1.0 + alpha));
        double d = 2.0 * (log10(etaTwo)) / (log10(1.0 + alpha));
        double tempAnnTwo = mu * etaTwo / (a + b - d);
        bool checkNeg = false;
        bool checkPos = false;
        while (abs(tempAnnTwo - annTwo) > delta) {
            difference = tempAnnTwo - annTwo;
            if (difference < 0) {
                if (checkPos) {
                    step = step / 2.0;
                }
                annTwo -= step;
                checkNeg = true;
                checkPos = false;
            } else {
                if (checkNeg) {
                    step = step / 2.0;
                }
                annTwo += step;
                checkPos = true;
                checkNeg = false;
            }
            a = 1.0 - (log10(alpha)) / (log10(1.0 + alpha));
            b = 2.0 * (log10(annTwo)) / (log10(1.0 + alpha));
            d = 2.0 * (log10(etaTwo)) / (log10(1.0 + alpha));
            tempAnnTwo = mu * etaTwo / (a + b - d);
        }
        return tempAnnTwo;
}

double annRecognition(double annTwo, double alpha)
{
        return ((alpha+1.0)/alpha)*annTwo;
}

double etaOneRecognition(double annTwo, double alpha, double delta, double step)
{
        double etaOne = 100.0;
        double difference;
        double tempEtaOne = (annTwo*(log10(2.0)))/(alpha*(log10(etaOne)));
        bool checkNeg = false;
        bool checkPos = false;
        while (abs(tempEtaOne - etaOne) > delta) {
            difference = tempEtaOne - etaOne;
            if (difference < 0) {
                if (checkPos) {
                    step = step / 2.0;
                }
                etaOne -= step;
                checkNeg = true;
                checkPos = false;
            } else {
                if (checkNeg) {
                    step = step / 2.0;
                }
                etaOne += step;
                checkPos = true;
                checkNeg = false;
            }
            tempEtaOne = (annTwo*(log10(2.0)))/(alpha*(log10(etaOne)));
        }
        return tempEtaOne;
}

double vRecognition(double ann, double etaOne, double etaTwo)
{
        return ann*log10(etaOne+etaTwo)/log10(2.0);
}

double tRecognition(double v, double mu, double s)
{
        return v*mu/s;
}