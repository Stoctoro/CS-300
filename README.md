# CS-300
portfolio addition for projects one and two of CS-300

# What was the problem you were solving in the projects for this course?
The goal of these projects was to create a program to store course information for a school's computer science program from a file. Along with checking that each of the courses read from the file were valid, the program would also need to capable of sorting, searching and printing each course.

# How did you approach the problem? Consider why data structures are important to understand.
Of the structures studied in CS-300, I decided to use a binary search tree to solve this problem. The binary search tree would be relatively quick to create and was sorted by design, requiring no dedicated sorting algorithm. Having an understanding of different data structures allows me to implement the structure that most closely suits my needs and saves me a lot of time when designing programs.

# How did you overcome any roadblocks you encountered while going through the activities or project?
One issue with a binary search tree is that its effeciency is entirely determined by the tree's shape, the distribution of elements within the tree. If the courses in the file were already sorted when my program read them, then the subsequent binary search tree would be created with the least effecient shape possible. To combat this, I first stored the elements into a vector and then into a tree. This was about the time a noticed that the file I was given wasn't actually sorted, so I didn't actually need to implement a randomization algorithm. However, I have left this "middle-man" vector in my program with the expectation that, should this program actually be utilized in the future, a random sort algorithm would be needed.

# How has your work on this project expanded your approach to designing software and developing programs?
My work on these projects has made me aware of processing effeciency and the value of learning about and using different data structures and algorithms rather than using the most obvious and simple ones that come to mind. I can already tell that the use of more thoughout data structures and algorithms will be quite prolific in my future projects

# How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
When I began coding, I quickly realized the value of writing modular, well documented code. I already try to write my programs in a way that allows it to be readable and have its parts easily swapped out. As such, I wouldn't say that my work on these projects has changed the way I write rather than giving me more practice and solidifying my ability to write clean code.
