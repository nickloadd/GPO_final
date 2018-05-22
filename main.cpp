#include "mainwindow.h"
#include <QApplication>
#include <QtDataVisualization>
#include <boost\property_tree\json_parser.hpp>
#include <boost\property_tree\ptree.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace QtDataVisualization;

    double getsimTime()
    {
        boost::property_tree::ptree pt;
        boost::property_tree::read_json("D:/Studies/Exchange/test/test2.json", pt);
        std::string st(pt.get<std::string>("simulationTime"));
        double simulationTime = atof(st.c_str());
        return simulationTime;
    }

    double getTimeStep()
    {
        boost::property_tree::ptree pt;
        boost::property_tree::read_json("D:/Studies/Exchange/test/test2.json", pt);
        std::string ts(pt.get<std::string>("timeStep"));
        double timeStep = atof(ts.c_str());
        return timeStep;
    }

    double getMaxFreq()
    {
        boost::property_tree::ptree pt;
        boost::property_tree::read_json("D:/Studies/Exchange/test/test2.json", pt);
        std::string mf(pt.get<std::string>("maxFrequency"));
        double maxFrequency = atof(mf.c_str());
        return maxFrequency;
    }

    double getfsn()
    {
        boost::property_tree::ptree pt;
        boost::property_tree::read_json("D:/Studies/Exchange/test/test2.json", pt);
        std::string stfsn(pt.get<std::string>("frequencyStepNumber"));
        double fsn = atof(stfsn.c_str());
        return fsn;
    }

    std::vector<double> getPowers()
    {
        boost::property_tree::ptree pt;
        boost::property_tree::read_json("D:/Studies/Exchange/test/test2.json", pt);
        std::vector<double> powers;
        for (auto& e : pt.get_child("powers")) {
            powers.push_back(atof(e.second.data().c_str()));
        }
        return powers;
    }



int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    Q3DScatter scatter;
    scatter.setFlags(scatter.flags() ^ Qt::FramelessWindowHint);
    QScatter3DSeries *series = new QScatter3DSeries;
    QScatterDataArray data;
    double t = getsimTime();
    double st = getTimeStep();
    double fsn = getfsn();
    double mf = getMaxFreq();
    double fs = mf/fsn;
    std::vector<double> v = getPowers();

    for (double j=0;j<=t;j+=st)
    {
    for (double i=0;i<=mf;i+=fs)
    data << QVector3D(i, v[i], j);
    }
    series->dataProxy()->addItems(data);
    scatter.addSeries(series);
    scatter.show();

    return app.exec();
}
