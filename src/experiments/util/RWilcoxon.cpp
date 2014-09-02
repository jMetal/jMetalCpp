//  RWilcoxon.cpp
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


#include <RWilcoxon.h>


void RWilcoxon::generateScripts(vector<string> problems, string prefix, ExperimentReport * experiment) {

  // STEP 1. Creating R output directory

  string rDirectory = "R";
  rDirectory = experiment->experimentBaseDirectory_ + "/" + rDirectory;
  cout << "R    : " << rDirectory << endl;
  if (FileUtils::existsPath(rDirectory.c_str()) == 0) {
    FileUtils::createDirectory(rDirectory);
    cout << "Creating " << rDirectory << " directory" << endl;
  }

  for (int indicator = 0; indicator < experiment->indicatorList_.size(); indicator++) {
    cout << "Indicator: " << experiment->indicatorList_[indicator] << endl;
    string rFile = rDirectory + "/" + prefix + "." + experiment->indicatorList_[indicator] + ".Wilcox.R";
    string texFile = rDirectory + "/" + prefix + "." + experiment->indicatorList_[indicator] + ".Wilcox.tex";

    std::ofstream out(rFile.c_str());
    string output = "write(\"\", \"" + texFile + "\",append=FALSE)";
    out << output << endl;

    // Generate function latexHeader()
    string dataDirectory = experiment->experimentBaseDirectory_ + "/data";
    out << "resultDirectory<-\"" << dataDirectory << "\"" << endl;
    out << "latexHeader <- function() {" << endl;
    out << "  write(\"\\\\documentclass{article}\", \"" + texFile + "\", append=TRUE)" << endl;
    out << "  write(\"\\\\title{StandardStudy}\", \"" + texFile + "\", append=TRUE)" << endl;
    out << "  write(\"\\\\usepackage{amssymb}\", \"" + texFile + "\", append=TRUE)" << endl;
    out << "  write(\"\\\\author{A.J.Nebro}\", \"" + texFile + "\", append=TRUE)" << endl;
    out << "  write(\"\\\\begin{document}\", \"" + texFile + "\", append=TRUE)" << endl;
    out << "  write(\"\\\\maketitle\", \"" + texFile + "\", append=TRUE)" << endl;
    out << "  write(\"\\\\section{Tables}\", \"" + texFile + "\", append=TRUE)" << endl;
    out << "  write(\"\\\\\", \"" + texFile + "\", append=TRUE)\n}" << endl;
    //out << output << endl;

    // Write function latexTableHeader
    string latexTableLabel = "";
    string latexTabularAlignment = "";
    string latexTableFirstLine = "";
    string latexTableCaption = "";

    latexTableCaption = "  write(\"\\\\caption{\", \"" + texFile + "\", append=TRUE)" + "\n" +
            "  write(problem, \"" + texFile + "\", append=TRUE)" + "\n" +
            "  write(\"." + experiment->indicatorList_[indicator] + ".}\", \"" + texFile + "\", append=TRUE)" + "\n";
    latexTableLabel = "  write(\"\\\\label{Table:\", \"" + texFile + "\", append=TRUE)" + "\n" +
            "  write(problem, \"" + texFile + "\", append=TRUE)" + "\n" +
            "  write(\"." + experiment->indicatorList_[indicator] + ".}\", \"" + texFile + "\", append=TRUE)" + "\n";
    latexTabularAlignment = "l";
    latexTableFirstLine = "\\\\hline ";

    for (int i = 1; i < experiment->algorithmNameList_.size(); i++) {
      latexTabularAlignment += "c";
      latexTableFirstLine += " & " + experiment->algorithmNameList_[i];
    } // for
    //latexTableFirstLine += "\\\\\\\\\",\"" + texFile + "\", append=TRUE)" + "\n";
    latexTableFirstLine += "\\\\\\\\ \"";

    // Generate function latexTableHeader()
    out << "latexTableHeader <- function(problem, tabularString, latexTableFirstLine) {" << endl;
    out << "  write(\"\\\\begin{table}\", \"" + texFile + "\", append=TRUE)" << endl;
    out << latexTableCaption << endl;
    out << latexTableLabel << endl;
    out << "  write(\"\\\\centering\", \"" + texFile + "\", append=TRUE)" << endl;
    out << "  write(\"\\\\begin{scriptsize}\", \"" + texFile + "\", append=TRUE)" << endl;
    //out << "  write(\"\\\\begin{tabular}{" + latexTabularAlignment + "}\", \"" + texFile + "\", append=TRUE)" << endl;
    out << "  write(\"\\\\begin{tabular}{\", \"" + texFile + "\", append=TRUE)" << endl;
    out << "  write(tabularString, \"" + texFile + "\", append=TRUE)" << endl;
    out << "  write(\"}\", \"" + texFile + "\", append=TRUE)" << endl;
    //out << latexTableFirstLine +
    out << "  write(latexTableFirstLine, \"" + texFile + "\", append=TRUE)" << endl;
    out << "  write(\"\\\\hline \", \"" + texFile + "\", append=TRUE)" + "\n" + "}" << endl;
    //out << output << endl;

    // Generate function latexTableTail()
    out << "latexTableTail <- function() { " << endl;
    out << "  write(\"\\\\hline\", \"" + texFile + "\", append=TRUE)" << endl;
    out << "  write(\"\\\\end{tabular}\", \"" + texFile + "\", append=TRUE)" << endl;
    out << "  write(\"\\\\end{scriptsize}\", \"" + texFile + "\", append=TRUE)" << endl;
    out << "  write(\"\\\\end{table}\", \"" + texFile + "\", append=TRUE)" + "\n" + "}" << endl;
    //out << output << endl;

    // Generate function latexTail()
    out << "latexTail <- function() { " << endl;
    out << "  write(\"\\\\end{document}\", \"" + texFile + "\", append=TRUE)" + "\n" + "}" << endl;
    //out << output << endl;

    if ((bool) experiment->indicatorMinimize_[experiment->indicatorList_[indicator]] == true) {// minimize by default
      // Generate function printTableLine()
      out << "printTableLine <- function(indicator, algorithm1, algorithm2, i, j, problem) { " << endl;
      out << "  file1<-paste(resultDirectory, algorithm1, sep=\"/\")" << endl;
      out << "  file1<-paste(file1, problem, sep=\"/\")" << endl;
      out << "  file1<-paste(file1, indicator, sep=\"/\")" << endl;
      out << "  data1<-scan(file1)" << endl;
      out << "  file2<-paste(resultDirectory, algorithm2, sep=\"/\")" << endl;
      out << "  file2<-paste(file2, problem, sep=\"/\")" << endl;
      out << "  file2<-paste(file2, indicator, sep=\"/\")" << endl;
      out << "  data2<-scan(file2)" << endl;
      out << "  if (i == j) {" << endl;
      out << "    write(\"-- \", \"" + texFile + "\", append=TRUE)" << endl;
      out << "  }" << endl;
      out << "  else if (i < j) {" << endl;
      out << "    if (wilcox.test(data1, data2)$p.value <= 0.05) {" << endl;
      out << "      if (median(data1) <= median(data2)) {" << endl;
      out << "        write(\"$\\\\blacktriangle$\", \"" + texFile + "\", append=TRUE)" << endl;
      out << "      }" << endl;
      out << "      else {" << endl;
      out << "        write(\"$\\\\triangledown$\", \"" + texFile + "\", append=TRUE) " << endl;
      out << "      }" << endl;
      out << "    }" << endl;
      out << "    else {" << endl;
      out << "      write(\"--\", \"" + texFile + "\", append=TRUE) " << endl;
      out << "    }" << endl;
      out << "  }" << endl;
      out << "  else {" << endl;
      out << "    write(\" \", \"" + texFile + "\", append=TRUE)" << endl;
      out << "  }" << endl;
      out << "}" << endl;
    } // if
    else {
      // Generate function printTableLine()
      out << "printTableLine <- function(indicator, algorithm1, algorithm2, i, j, problem) { " << endl;
      out << "  file1<-paste(resultDirectory, algorithm1, sep=\"/\")" << endl;
      out << "  file1<-paste(file1, problem, sep=\"/\")" << endl;
      out << "  file1<-paste(file1, indicator, sep=\"/\")" << endl;
      out << "  data1<-scan(file1)" << endl;
      out << "  file2<-paste(resultDirectory, algorithm2, sep=\"/\")" << endl;
      out << "  file2<-paste(file2, problem, sep=\"/\")" << endl;
      out << "  file2<-paste(file2, indicator, sep=\"/\")" << endl;
      out << "  data2<-scan(file2)" << endl;
      out << "  if (i == j) {" << endl;
      out << "    write(\"--\", \"" + texFile + "\", append=TRUE)" << endl;
      out << "  }" << endl;
      out << "  else if (i < j) {" << endl;
      out << "    if (wilcox.test(data1, data2)$p.value <= 0.05) {" << endl;
      out << "      if (median(data1) >= median(data2)) {" << endl;
      out << "        write(\"$\\\\blacktriangle$\", \"" + texFile + "\", append=TRUE)" << endl;
      out << "      }" << endl;
      out << "      else {" << endl;
      out << "        write(\"$\\\\triangledown$\", \"" + texFile + "\", append=TRUE) " << endl;
      out << "      }" << endl;
      out << "    }" << endl;
      out << "    else {" << endl;
      out << "      write(\"--\", \"" + texFile + "\", append=TRUE) " << endl;
      out << "    }" << endl;
      out << "  }" << endl;
      out << "  else {" << endl;
      out << "    write(\" \", \"" + texFile + "\", append=TRUE)" << endl;
      out << "  }" << endl;
      out << "}" << endl;
    }
    //out << output << endl;

    // Start of the R script
    output = "### START OF SCRIPT ";
    out << output << endl;

    string problemList = "problemList <-c(";
    string algorithmList = "algorithmList <-c(";

    for (int i = 0; i < (problems.size() - 1); i++) {
      problemList += "\"" + problems[i] + "\", ";
    }
    problemList += "\"" + problems[problems.size() - 1] + "\") ";

    for (int i = 0; i < (experiment->algorithmNameList_.size() - 1); i++) {
      algorithmList += "\"" + experiment->algorithmNameList_[i] + "\", ";
    }
    algorithmList += "\"" + experiment->algorithmNameList_[experiment->algorithmNameList_.size() - 1] + "\") ";

    latexTabularAlignment = "l";
    for (int i = 1; i < experiment->algorithmNameList_.size(); i++) {
      latexTabularAlignment += "c";
    } // for
    string tabularString = "tabularString <-c(\""+ latexTabularAlignment + "\") ";
    string tableFirstLine = "latexTableFirstLine <-c(\"" + latexTableFirstLine + ") ";

    output = "# Constants\n" +
            problemList + "\n" +
            algorithmList + "\n" +
            tabularString + "\n" +
            tableFirstLine + "\n" +
            "indicator<-\"" + experiment->indicatorList_[indicator] + "\"";
    out << output << endl;

    out << "\n# Step 1.  Writes the latex header" << endl;
    out << "latexHeader()" << endl << endl;;
    //out << output << endl;

    // Generate tables per problem
    out << "# Step 2. Problem loop" << endl;
    out << "for (problem in problemList) {" << endl;
    out << "  latexTableHeader(problem,  tabularString, latexTableFirstLine)" << endl << endl;
    out << "  indx = 0" << endl;
    out << "  for (i in algorithmList) {" << endl;
    out << "    if (i != \"" + experiment->algorithmNameList_[experiment->algorithmNameList_.size() - 1]+ "\") {" << endl;
    out << "      write(i , \"" + texFile + "\", append=TRUE)" << endl;
    out << "      write(\" & \", \"" + texFile + "\", append=TRUE)" << endl;
    out << "      jndx = 0 " << endl;
    out << "      for (j in algorithmList) {" << endl;
    out << "        if (jndx != 0) {" << endl;
    out << "          if (indx != jndx) {" << endl;
    out << "            printTableLine(indicator, i, j, indx, jndx, problem)" << endl;
    out << "          }" << endl;
    out << "          else {" << endl;
    out << "            write(\"  \", \"" + texFile + "\", append=TRUE)" << endl;
    out << "          }" << endl;
    out << "          if (j != \"" + experiment->algorithmNameList_[experiment->algorithmNameList_.size() - 1] + "\") {" << endl;
    out << "            write(\" & \", \"" + texFile + "\", append=TRUE)" << endl;
    out << "          }" << endl;
    out << "          else {" << endl;
    out << "            write(\" \\\\\\\\ \", \"" + texFile + "\", append=TRUE)" << endl;
    out << "          }" << endl;
    out << "        }" << endl;
    out << "        jndx = jndx + 1" << endl;
    out << "      }" << endl;
    out << "      indx = indx + 1" << endl;
    out << "    }" << endl;
    out << "  }" << endl << endl;
    out << "  latexTableTail()" << endl;
    out << "} # for problem" << endl;
    //out << output << endl;

    // Generate full table
    problemList = "";
    for (int i = 0; i < problems.size(); i++) {
      problemList += problems[i] + " ";
    }
    // The tabular environment and the latexTableFirstLine variable must be redefined
    stringstream ssLatexTableFirstLine;
    latexTabularAlignment = "| l | ";
    ssLatexTableFirstLine << "\\\\hline \\\\multicolumn{1}{|c|}{}";
    for (int i = 1; i < experiment->algorithmNameList_.size(); i++) {
      for (int j = 0; j < problems.size(); j++) {
        latexTabularAlignment += "p{0.15cm}  ";
        //latexTabularAlignment += "c ";
      } // for
      ssLatexTableFirstLine << " & \\\\multicolumn{" << problems.size() << "}{c|}{"
          << experiment->algorithmNameList_[i] << "}";
      latexTabularAlignment += " | " ;
    } // for
    ssLatexTableFirstLine << " \\\\\\\\";
    latexTableFirstLine = ssLatexTableFirstLine.str();

    tabularString = "tabularString <-c(\""+ latexTabularAlignment + "\") ";
    latexTableFirstLine = "latexTableFirstLine <-c(\""+ latexTableFirstLine + "\") ";

    output = tabularString;
    out << output + "\n" << endl;
    output = latexTableFirstLine ;
    out << output + "\n" << endl;

    out << "# Step 3. Problem loop" << endl;
    out << "latexTableHeader(\"" + problemList + "\", tabularString, latexTableFirstLine)" << endl << endl;
    out << "indx = 0" << endl;
    out << "for (i in algorithmList) {" << endl;
    out << "  if (i != \"" + experiment->algorithmNameList_[experiment->algorithmNameList_.size() - 1]+ "\") {" << endl;
    out << "    write(i , \"" + texFile + "\", append=TRUE)" << endl;
    out << "    write(\" & \", \"" + texFile + "\", append=TRUE)" << endl << endl;
    out << "    jndx = 0" << endl;
    out << "    for (j in algorithmList) {" << endl;
    out << "      for (problem in problemList) {" << endl;
    out << "        if (jndx != 0) {" << endl;
    out << "          if (i != j) {" << endl;
    out << "            printTableLine(indicator, i, j, indx, jndx, problem)" << endl;
    out << "          }" << endl;
    out << "          else {" << endl;
    out << "            write(\"  \", \"" + texFile + "\", append=TRUE)" << endl;
    out << "          } " << endl;
    out << "          if (problem == \"" + problems[problems.size() - 1] + "\") {" << endl;
    out << "            if (j == \"" + experiment->algorithmNameList_[experiment->algorithmNameList_.size() - 1] + "\") {" << endl;
    out << "              write(\" \\\\\\\\ \", \"" + texFile + "\", append=TRUE)" << endl;
    out << "            } " << endl;
    out << "            else {" << endl;
    out << "              write(\" & \", \"" + texFile + "\", append=TRUE)" << endl;
    out << "            }" << endl;
    out << "          }" << endl;
    out << "     else {" << endl;
    out << "    write(\"&\", \"" + texFile + "\", append=TRUE)" << endl;
    out << "     }" << endl;
    out << "        }" << endl;
    out << "      }" << endl;
    out << "      jndx = jndx + 1" << endl;
    out << "    }" << endl;
    out << "    indx = indx + 1" << endl;
    out << "  }" << endl;
    out << "} # for algorithm" << endl << endl;
    out << "latexTableTail()" << endl;
    //out << output << endl;

    // Generate end of file
    out << "#Step 4. Writes the end of latex file " << endl;
    out << "latexTail()" << endl;

    out.close();
  } // for

} // generateScripts
