//  RBoxplot.cpp
//
//  Author:
//       Esteban López-Camacho <esteban@lcc.uma.es>
//
//  Copyright (c) 2011 Antonio J. Nebro, Juan J. Durillo
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include <RBoxplot.h>

void RBoxplot::generateScripts(int rows, int cols, vector<string> problems, string prefix,
      bool notch, ExperimentReport * experiment) {

  // STEP 1. Creating R output directory

  string rDirectory = "R";
  rDirectory = experiment->experimentBaseDirectory_ + "/" +  rDirectory;
  cout << "R    : " << rDirectory << endl;
  if (FileUtils::existsPath(rDirectory.c_str()) == 0) {
    FileUtils::createDirectory(rDirectory);
    cout << "Creating " << rDirectory << " directory" << endl;
  }

  for (int indicator = 0; indicator < experiment->indicatorList_.size(); indicator++) {
    cout << "Indicator: " <<  experiment->indicatorList_[indicator] << endl;
    string rFile =  rDirectory + "/" + prefix + "." +  experiment->indicatorList_[indicator] + ".Boxplot.R";

    std::ofstream out(rFile.c_str());
    out << "postscript(\"" << prefix << "." << experiment->indicatorList_[indicator] <<
        ".Boxplot.eps\", horizontal=FALSE, onefile=FALSE, height=8, width=12, pointsize=10)" <<
        endl;
    //out << "resultDirectory<-\"../data/" << experimentName_ << "\"" << endl;
    out << "resultDirectory<-\"../data/" << "\"" << endl;
    out << "qIndicator <- function(indicator, problem)" << endl;
    out << "{" << endl;

    for (int i = 0; i <  experiment->algorithmNameList_.size(); i++) {
      out << "file" << experiment->algorithmNameList_[i] << "<-paste(resultDirectory, \"" <<
          experiment->algorithmNameList_[i] << "\", sep=\"/\")" << endl;
      out << "file" <<  experiment->algorithmNameList_[i] << "<-paste(file" <<
          experiment->algorithmNameList_[i] << ", " << "problem, sep=\"/\")" << endl;
      out << "file" <<  experiment->algorithmNameList_[i] << "<-paste(file" <<
          experiment->algorithmNameList_[i] << ", " << "indicator, sep=\"/\")" << endl;
      out << experiment->algorithmNameList_[i] << "<-scan(" << "file" <<
          experiment->algorithmNameList_[i] << ")" << endl;
      out << endl;
    } // for

    out << "algs<-c(";
    for (int i = 0; i <  experiment->algorithmNameList_.size() - 1; i++) {
      out << "\"" << experiment->algorithmNameList_[i] << "\",";
    } // for
    out << "\"" << experiment->algorithmNameList_[ experiment->algorithmNameList_.size() - 1] <<
        "\")" << endl;

    out << "boxplot(";
    for (int i = 0; i <  experiment->algorithmNameList_.size(); i++) {
      out << experiment->algorithmNameList_[i] << ",";
    } // for
    if (notch) {
      out << "names=algs, notch = TRUE)" << endl;
    } else {
      out << "names=algs, notch = FALSE)" << endl;
    }
    out << "titulo <-paste(indicator, problem, sep=\":\")" << endl;
    out << "title(main=titulo)" << endl;

    out << "}" << endl;

    out << "par(mfrow=c(" << rows << "," << cols << "))" << endl;

    out << "indicator<-\"" <<  experiment->indicatorList_[indicator] << "\"" << endl;

    for (int i = 0; i < problems.size(); i++) {
      out << "qIndicator(indicator, \"" << problems[i] << "\")" << endl;
    }

    out.close();
  } // for

} // generateScripts
