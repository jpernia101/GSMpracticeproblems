# GSMpracticeproblems
I went ahead and commented the code in detail.
All Objectives are ran in the main.

Encoding Mechanism
I decided to turn my numbers to a base4 equivalent. That way 3333 covers all ASCII characters (0-255). That way each character can have its own unique combination of letters.
The map I used was 0-A, 1-T,2-G,3-C. So for example the character “a” has a ascii value of 97. Once converted to base4 its 1201 and then you just map it so it would be
TGAT.


DETAILS:
  Objective 1-4 uses the variable that the user inputted at the beggining 
  objective 5 gives you the option of putting in 2 new strings to find the longest substring 
