# CS300-DataStructures_and_Algorithms
A collection of the major work I completed during this course at SNHU.

What was the problem you were solving in the projects for this course?
--
The two projects worked toward developing a console application that reads and parses college courses from a .csv file. Project 1 involved pseudocode and Big O runtime analysis while Project 2 involved coding the actual application. The application needed to successfully read a .csv file, parse its lines into separate categories of a structure, store the smaller structures (courses) into a larger overarching structure (binary search tree i.e. BST), and allow the user to view data from any or all courses.

How did you approach the problem? Consider why data structures are important to understand.
--
I approached completing these projects by referencing examples from the textbook, past assignments, and online articles. Studying these implementations taught me how to implement each data structure and write pseudocode accordingly. When I found errors in my pseudocode, I referenced the same materials to find and fix my mistakes. Data structures are important to understand because they give a programmer options, and tailoring software to match its best-fit options is part of strong problem-solving. Reviewing the advantages and disadvantages of each data structure taught me what to think about when considering future code (e.g., runtime complexity, memory requirements).

How did you overcome any roadblocks you encountered while going through the activities or project?
--
Calculating Big O runtimes by hand was challenging to understand. It was hard to know if the values I assigned to each line were accurate or missing some "bigger picture". I relied on informative videos, the textbook, and the assignment guidelines to calculate Big O runtimes for each data structure and compare them accordingly. It was also hard to know for sure which data structure was better to use-- a hash table or BST. The hash table seemed like a better choice if not for the BST's inherent ordering system, so that was what the choice came down to. I handled coding roadblocks by reading Geeks for Geeks articles and Stack Overflow posts that pointed me in the right direction for specific C++ concepts I needed brushing up on.

How has your work on this project expanded your approach to designing software and developing programs?
--
I now know to consider using hash tables and BSTs for projects whereas I'd never worked with them before. I'll also consider any data structure's runtime when choosing the best fit one for a project. It shocked me to find that an algorithm or structure with a slow runtime can take literal years to compute large amounts of data, meaning it's something necessary to pay attention to. These projects have taught me the importance of options and weighing them thoughtfully, since even fast algorithms can have the downside of increased space complexity.

How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
--
I repeatedly referenced assignments I completed previously in this course to inform work on my projects. It was useful for that code to be readable and adaptable so I could reuse similar logic. When finalizing my code for Project 2, I adapted my pseudocode from one long main() function to a modularized series of functions. This made debugging more streamlined because I could find logical issues in each function rather than in just the block for main(). I will continue to write modular code in the future to make it easier to test, debug, and refactor.
