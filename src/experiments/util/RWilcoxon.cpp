//  RWilcoxon.cpp
//
//  Author:
//       Esteban López-Camacho <esteban@lcc.uma.es>
//       Sérgio Vieira <sergiosvieira@gmail.com>
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


void RWilcoxon::generateScripts(VectorOfString problems, std::string prefix, ExperimentReport * experiment)
{

    // STEP 1. Creating R output directory

    std::string rDirectory = "R";
    rDirectory = experiment->experimentBaseDirectory_ + "/" + rDirectory;
    std::cout << "R    : " << rDirectory << std::endl;
    if (FileUtils::existsPath(rDirectory.c_str()) == 0)
    {
        FileUtils::createDirectory(rDirectory);
        std::cout << "Creating " << rDirectory << " directory" << std::endl;
    }

    for (int indicator = 0; indicator < experiment->indicatorList_.size(); indicator++)
    {
        std::cout << "Indicator: " << experiment->indicatorList_[indicator] << std::endl;
        std::string rFile = rDirectory + "/" + prefix + "." + experiment->indicatorList_[indicator] + ".Wilcox.R";
        std::string texFile = rDirectory + "/" + prefix + "." + experiment->indicatorList_[indicator] + ".Wilcox.tex";

        std::ofstream out(rFile.c_str());
        std::string output = "write(\"\", \"" + texFile + "\",append=FALSE)";
        out << output << std::endl;

        // Generate function latexHeader()
        std::string dataDirectory = experiment->experimentBaseDirectory_ + "/data";
        out << "resultDirectory<-\"" << dataDirectory << "\"" << std::endl;
        out << "latexHeader <- function() {" << std::endl;
        out << "  write(\"\\\\documentclass{article}\", \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "  write(\"\\\\title{StandardStudy}\", \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "  write(\"\\\\usepackage{amssymb}\", \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "  write(\"\\\\author{A.J.Nebro}\", \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "  write(\"\\\\begin{document}\", \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "  write(\"\\\\maketitle\", \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "  write(\"\\\\section{Tables}\", \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "  write(\"\\\\\", \"" + texFile + "\", append=TRUE)\n}" << std::endl;
        //out << output << std::endl;

        // Write function latexTableHeader
        std::string latexTableLabel = "";
        std::string latexTabularAlignment = "";
        std::string latexTableFirstLine = "";
        std::string latexTableCaption = "";

        latexTableCaption = "  write(\"\\\\caption{\", \"" + texFile + "\", append=TRUE)" + "\n" +
                            "  write(problem, \"" + texFile + "\", append=TRUE)" + "\n" +
                            "  write(\"." + experiment->indicatorList_[indicator] + ".}\", \"" + texFile + "\", append=TRUE)" + "\n";
        latexTableLabel = "  write(\"\\\\label{Table:\", \"" + texFile + "\", append=TRUE)" + "\n" +
                          "  write(problem, \"" + texFile + "\", append=TRUE)" + "\n" +
                          "  write(\"." + experiment->indicatorList_[indicator] + ".}\", \"" + texFile + "\", append=TRUE)" + "\n";
        latexTabularAlignment = "l";
        latexTableFirstLine = "\\\\hline ";

        for (int i = 1; i < experiment->algorithmNameList_.size(); i++)
        {
            latexTabularAlignment += "c";
            latexTableFirstLine += " & " + experiment->algorithmNameList_[i];
        } // for
        //latexTableFirstLine += "\\\\\\\\\",\"" + texFile + "\", append=TRUE)" + "\n";
        latexTableFirstLine += "\\\\\\\\ \"";

        // Generate function latexTableHeader()
        out << "latexTableHeader <- function(problem, tabularString, latexTableFirstLine) {" << std::endl;
        out << "  write(\"\\\\begin{table}\", \"" + texFile + "\", append=TRUE)" << std::endl;
        out << latexTableCaption << std::endl;
        out << latexTableLabel << std::endl;
        out << "  write(\"\\\\centering\", \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "  write(\"\\\\begin{scriptsize}\", \"" + texFile + "\", append=TRUE)" << std::endl;
        //out << "  write(\"\\\\begin{tabular}{" + latexTabularAlignment + "}\", \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "  write(\"\\\\begin{tabular}{\", \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "  write(tabularString, \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "  write(\"}\", \"" + texFile + "\", append=TRUE)" << std::endl;
        //out << latexTableFirstLine +
        out << "  write(latexTableFirstLine, \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "  write(\"\\\\hline \", \"" + texFile + "\", append=TRUE)" + "\n" + "}" << std::endl;
        //out << output << std::endl;

        // Generate function latexTableTail()
        out << "latexTableTail <- function() { " << std::endl;
        out << "  write(\"\\\\hline\", \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "  write(\"\\\\end{tabular}\", \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "  write(\"\\\\end{scriptsize}\", \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "  write(\"\\\\end{table}\", \"" + texFile + "\", append=TRUE)" + "\n" + "}" << std::endl;
        //out << output << std::endl;

        // Generate function latexTail()
        out << "latexTail <- function() { " << std::endl;
        out << "  write(\"\\\\end{document}\", \"" + texFile + "\", append=TRUE)" + "\n" + "}" << std::endl;
        //out << output << std::endl;

        if ((bool) experiment->indicatorMinimize_[experiment->indicatorList_[indicator]] == true)  // minimize by default
        {
            // Generate function printTableLine()
            out << "printTableLine <- function(indicator, algorithm1, algorithm2, i, j, problem) { " << std::endl;
            out << "  file1<-paste(resultDirectory, algorithm1, sep=\"/\")" << std::endl;
            out << "  file1<-paste(file1, problem, sep=\"/\")" << std::endl;
            out << "  file1<-paste(file1, indicator, sep=\"/\")" << std::endl;
            out << "  data1<-scan(file1)" << std::endl;
            out << "  file2<-paste(resultDirectory, algorithm2, sep=\"/\")" << std::endl;
            out << "  file2<-paste(file2, problem, sep=\"/\")" << std::endl;
            out << "  file2<-paste(file2, indicator, sep=\"/\")" << std::endl;
            out << "  data2<-scan(file2)" << std::endl;
            out << "  if (i == j) {" << std::endl;
            out << "    write(\"-- \", \"" + texFile + "\", append=TRUE)" << std::endl;
            out << "  }" << std::endl;
            out << "  else if (i < j) {" << std::endl;
            out << "    if (wilcox.test(data1, data2)$p.value <= 0.05) {" << std::endl;
            out << "      if (median(data1) <= median(data2)) {" << std::endl;
            out << "        write(\"$\\\\blacktriangle$\", \"" + texFile + "\", append=TRUE)" << std::endl;
            out << "      }" << std::endl;
            out << "      else {" << std::endl;
            out << "        write(\"$\\\\triangledown$\", \"" + texFile + "\", append=TRUE) " << std::endl;
            out << "      }" << std::endl;
            out << "    }" << std::endl;
            out << "    else {" << std::endl;
            out << "      write(\"--\", \"" + texFile + "\", append=TRUE) " << std::endl;
            out << "    }" << std::endl;
            out << "  }" << std::endl;
            out << "  else {" << std::endl;
            out << "    write(\" \", \"" + texFile + "\", append=TRUE)" << std::endl;
            out << "  }" << std::endl;
            out << "}" << std::endl;
        } // if
        else
        {
            // Generate function printTableLine()
            out << "printTableLine <- function(indicator, algorithm1, algorithm2, i, j, problem) { " << std::endl;
            out << "  file1<-paste(resultDirectory, algorithm1, sep=\"/\")" << std::endl;
            out << "  file1<-paste(file1, problem, sep=\"/\")" << std::endl;
            out << "  file1<-paste(file1, indicator, sep=\"/\")" << std::endl;
            out << "  data1<-scan(file1)" << std::endl;
            out << "  file2<-paste(resultDirectory, algorithm2, sep=\"/\")" << std::endl;
            out << "  file2<-paste(file2, problem, sep=\"/\")" << std::endl;
            out << "  file2<-paste(file2, indicator, sep=\"/\")" << std::endl;
            out << "  data2<-scan(file2)" << std::endl;
            out << "  if (i == j) {" << std::endl;
            out << "    write(\"--\", \"" + texFile + "\", append=TRUE)" << std::endl;
            out << "  }" << std::endl;
            out << "  else if (i < j) {" << std::endl;
            out << "    if (wilcox.test(data1, data2)$p.value <= 0.05) {" << std::endl;
            out << "      if (median(data1) >= median(data2)) {" << std::endl;
            out << "        write(\"$\\\\blacktriangle$\", \"" + texFile + "\", append=TRUE)" << std::endl;
            out << "      }" << std::endl;
            out << "      else {" << std::endl;
            out << "        write(\"$\\\\triangledown$\", \"" + texFile + "\", append=TRUE) " << std::endl;
            out << "      }" << std::endl;
            out << "    }" << std::endl;
            out << "    else {" << std::endl;
            out << "      write(\"--\", \"" + texFile + "\", append=TRUE) " << std::endl;
            out << "    }" << std::endl;
            out << "  }" << std::endl;
            out << "  else {" << std::endl;
            out << "    write(\" \", \"" + texFile + "\", append=TRUE)" << std::endl;
            out << "  }" << std::endl;
            out << "}" << std::endl;
        }
        //out << output << std::endl;

        // Start of the R script
        output = "### START OF SCRIPT ";
        out << output << std::endl;

        std::string problemList = "problemList <-c(";
        std::string algorithmList = "algorithmList <-c(";

        for (int i = 0; i < (problems.size() - 1); i++)
        {
            problemList += "\"" + problems[i] + "\", ";
        }
        problemList += "\"" + problems[problems.size() - 1] + "\") ";

        for (int i = 0; i < (experiment->algorithmNameList_.size() - 1); i++)
        {
            algorithmList += "\"" + experiment->algorithmNameList_[i] + "\", ";
        }
        algorithmList += "\"" + experiment->algorithmNameList_[experiment->algorithmNameList_.size() - 1] + "\") ";

        latexTabularAlignment = "l";
        for (int i = 1; i < experiment->algorithmNameList_.size(); i++)
        {
            latexTabularAlignment += "c";
        } // for
        std::string tabularString = "tabularString <-c(\""+ latexTabularAlignment + "\") ";
        std::string tableFirstLine = "latexTableFirstLine <-c(\"" + latexTableFirstLine + ") ";

        output = "# Constants\n" +
                 problemList + "\n" +
                 algorithmList + "\n" +
                 tabularString + "\n" +
                 tableFirstLine + "\n" +
                 "indicator<-\"" + experiment->indicatorList_[indicator] + "\"";
        out << output << std::endl;

        out << "\n# Step 1.  Writes the latex header" << std::endl;
        out << "latexHeader()" << std::endl << std::endl;;
        //out << output << std::endl;

        // Generate tables per problem
        out << "# Step 2. Problem loop" << std::endl;
        out << "for (problem in problemList) {" << std::endl;
        out << "  latexTableHeader(problem,  tabularString, latexTableFirstLine)" << std::endl << std::endl;
        out << "  indx = 0" << std::endl;
        out << "  for (i in algorithmList) {" << std::endl;
        out << "    if (i != \"" + experiment->algorithmNameList_[experiment->algorithmNameList_.size() - 1]+ "\") {" << std::endl;
        out << "      write(i , \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "      write(\" & \", \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "      jndx = 0 " << std::endl;
        out << "      for (j in algorithmList) {" << std::endl;
        out << "        if (jndx != 0) {" << std::endl;
        out << "          if (indx != jndx) {" << std::endl;
        out << "            printTableLine(indicator, i, j, indx, jndx, problem)" << std::endl;
        out << "          }" << std::endl;
        out << "          else {" << std::endl;
        out << "            write(\"  \", \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "          }" << std::endl;
        out << "          if (j != \"" + experiment->algorithmNameList_[experiment->algorithmNameList_.size() - 1] + "\") {" << std::endl;
        out << "            write(\" & \", \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "          }" << std::endl;
        out << "          else {" << std::endl;
        out << "            write(\" \\\\\\\\ \", \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "          }" << std::endl;
        out << "        }" << std::endl;
        out << "        jndx = jndx + 1" << std::endl;
        out << "      }" << std::endl;
        out << "      indx = indx + 1" << std::endl;
        out << "    }" << std::endl;
        out << "  }" << std::endl << std::endl;
        out << "  latexTableTail()" << std::endl;
        out << "} # for problem" << std::endl;
        //out << output << std::endl;

        // Generate full table
        problemList = "";
        for (int i = 0; i < problems.size(); i++)
        {
            problemList += problems[i] + " ";
        }
        // The tabular environment and the latexTableFirstLine variable must be redefined
        stringstream ssLatexTableFirstLine;
        latexTabularAlignment = "| l | ";
        ssLatexTableFirstLine << "\\\\hline \\\\multicolumn{1}{|c|}{}";
        for (int i = 1; i < experiment->algorithmNameList_.size(); i++)
        {
            for (int j = 0; j < problems.size(); j++)
            {
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
        out << output + "\n" << std::endl;
        output = latexTableFirstLine ;
        out << output + "\n" << std::endl;

        out << "# Step 3. Problem loop" << std::endl;
        out << "latexTableHeader(\"" + problemList + "\", tabularString, latexTableFirstLine)" << std::endl << std::endl;
        out << "indx = 0" << std::endl;
        out << "for (i in algorithmList) {" << std::endl;
        out << "  if (i != \"" + experiment->algorithmNameList_[experiment->algorithmNameList_.size() - 1]+ "\") {" << std::endl;
        out << "    write(i , \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "    write(\" & \", \"" + texFile + "\", append=TRUE)" << std::endl << std::endl;
        out << "    jndx = 0" << std::endl;
        out << "    for (j in algorithmList) {" << std::endl;
        out << "      for (problem in problemList) {" << std::endl;
        out << "        if (jndx != 0) {" << std::endl;
        out << "          if (i != j) {" << std::endl;
        out << "            printTableLine(indicator, i, j, indx, jndx, problem)" << std::endl;
        out << "          }" << std::endl;
        out << "          else {" << std::endl;
        out << "            write(\"  \", \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "          } " << std::endl;
        out << "          if (problem == \"" + problems[problems.size() - 1] + "\") {" << std::endl;
        out << "            if (j == \"" + experiment->algorithmNameList_[experiment->algorithmNameList_.size() - 1] + "\") {" << std::endl;
        out << "              write(\" \\\\\\\\ \", \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "            } " << std::endl;
        out << "            else {" << std::endl;
        out << "              write(\" & \", \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "            }" << std::endl;
        out << "          }" << std::endl;
        out << "     else {" << std::endl;
        out << "    write(\"&\", \"" + texFile + "\", append=TRUE)" << std::endl;
        out << "     }" << std::endl;
        out << "        }" << std::endl;
        out << "      }" << std::endl;
        out << "      jndx = jndx + 1" << std::endl;
        out << "    }" << std::endl;
        out << "    indx = indx + 1" << std::endl;
        out << "  }" << std::endl;
        out << "} # for algorithm" << std::endl << std::endl;
        out << "latexTableTail()" << std::endl;
        //out << output << std::endl;

        // Generate end of file
        out << "#Step 4. Writes the end of latex file " << std::endl;
        out << "latexTail()" << std::endl;

        out.close();
    } // for

} // generateScripts
