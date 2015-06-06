# GT
This is a tool to observer the array sort, STL and numerical algorithm

Debug to find the bug is so miserable.

Sometimes, you would like to write a algorithm just like quick sort or something else, 
but the there is bugs anywhere. This tool will help you to locate the bug, 
and find the mistake in you program faster than debug.
 
for example 
 
/////////////////////////////////////////// 

AddId("id_Pi")("id_r"); 

Double Pi = 3.1415926, r; 

r = 4.1; 

AddId("id_perimeter")("id_area"); 

Double perimeter, area; 

perimeter = 2 * Pi * r; 

area = Pi * pow(r, 2); 

return 0; 
 
/////////////////////////////////////////// 

will Automatic output： 
  
EXPRES:id_Pi = 3.141593 

EXPRES:id_r = 4.1 

EXPRES:id_perimeter = (2*3.141593)*4.1 

EXPRES:id_area = 3.141593*pow(4.1, 2) 

 
 
sort an array consle will automatic will Automatic output：

///////////////////////////////////////////

TRACE: GT[0] > GT[7] = 0 

TRACE: GT[1] > GT[8] = 0 

TRACE: GT[0] > GT[3] = 0 

TRACE: GT[3] > GT[6] = 1 

3   1   3   63   11   2  [63]  23   51  

TRACE: GT[3] = 5 

3   1   3  [5]  11   2   63   23   51 

TRACE: GT[0] > GT[3] = 0 

TRACE: GT[1] > GT[4] = 0

TRACE: GT[4] > GT[7] = 0

TRACE: GT[2] > GT[5] = 1

3   1   3   5   11  [3]  63   23   51

TRACE: GT[2] = 2

3   1  [2]  5   11   3   63   23   51

TRACE: GT[5] > GT[8] = 0

TRACE: GT[0] > GT[1] = 1

3  [3]  2   5   11   3   63   23   51

TRACE: GT[0] = 1

[1]  3   2   5   11   3   63   23   51

TRACE: GT[1] > GT[2] = 1

1   3  [3]  5   11   3   63   23   51

TRACE: GT[1] = 2

1  [2]  3   5   11   3   63   23   51

TRACE: GT[0] > GT[1] = 0

TRACE: GT[2] > GT[3] = 0

TRACE: GT[3] > GT[4] = 0

TRACE: GT[4] > GT[5] = 1

1   2   3   5   11  [11]  63   23   51

TRACE: GT[4] = 3

1   2   3   5  [3]  11   63   23   51

TRACE: GT[3] > GT[4] = 1

1   2   3   5  [5]  11   63   23   51

TRACE: GT[3] = 3

1   2   3  [3]  5   11   63   23   51

TRACE: GT[2] > GT[3] = 0

TRACE: GT[5] > GT[6] = 0

TRACE: GT[6] > GT[7] = 1

1   2   3   3   5   11   63  [63]  51

TRACE: GT[6] = 23

1   2   3   3   5   11  [23]  63   51

TRACE: GT[5] > GT[6] = 0

TRACE: GT[7] > GT[8] = 1

1   2   3   3   5   11   23   63  [63]

TRACE: GT[7] = 51

1   2   3   3   5   11   23  [51]  63

TRACE: GT[6] > GT[7] = 0

1  2  3  3  5  11  23  51  63
