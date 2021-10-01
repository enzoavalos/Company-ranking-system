# Company Ranking System
### Rankign system for the top companies to work for, according to employees opinions!   
### It provides varous efficient search services for user queries.

##
### About the project:
Project developed for "Analisis and Design of Algorithms I" of System Engineering.

## 
### Topics involved:
- Binary search trees
- Priority search trees
- Linked Lists
- Templates
- Pointers
- File handling
- Modularization and classes

## 
### Steps to get started:
**Prerequisites:** It will be needed for you to download the files present in the repo and save them all in the same directory.

**Windows & Linux:** A .cbp file is included in the repo so you can open and run the entire project directly. However, it is needed for you to have [code::blocks](https://www.codeblocks.org/) installed on your computer, since this file was created with this IDE.
**Mac:** If you are using Mac, the .cbp file won´t work for you, and a few extra steps will be needed:
- To compile the program you must download either an IDE or a (surprise) compiler:
  - I recommend [VS Code](https://code.visualstudio.com/) or [Xcode](https://developer.apple.com/xcode/).


## 
### App structure:
The app consists of a ranking that contains information about the best companies to work for, such as its legal name, work area, amount of employees and country of origin. All of this information is extracted from the company_ranking.csv file included in the repo.   
It offers different search services that retrieve certain companies based on user queries. Each service is implemented with a particular auxiliary data structure built upon an array with the actual information, specifically selected based on the characteristics of the particular service, to improve its performance and theoretical complexity.    
The search services offered are:
- Get the position in the ranking given a certain company.
- Get the information of the company in a given position.
- List the companies with an amount of employees within a given range.
- List the "n" first companies of the ranking with an amount of employees within a given range.
