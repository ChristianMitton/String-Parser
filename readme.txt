
My code can be split into 3 major parts: 

1.) Converting a filtered user's string into an array
2.) Sorting the array, where uppercase letters are greater than lowercase letter
3.) Printing the sored array

----------------------------------------------------------------------------------------------------------------------------------
1.) Converting a filtered user string into an array

The idea was to iterate through the string until I hit the length of it. While iterating, each 
character would be checked to see if it was a letter or not. If it was, the letter would be added to a letter linked list where each node contained a single letter. Once I hit a character that wasn't a letter, the letter linked list would be converted into a single word node that contained all the letter nodes combined together, and this would form an entire word. For example, if this was the input:

	"Test"

it would be first be turned into a letter linked list:

	T--> e--> s--> t-->

and then each node in this letter linked list would be combined into one node to form a word node:

	Test-->

After handling cases such as multiple seperators next to each other, empty strings, etc. this approach allows the algorithim to handle a string of any length, and to handle extreme cases where words are very far apart. The final linked list of words is then converted to an array.

-----------------------------------------------------------------------------------------------------------------------------------
2.) Sorting the word array

The first step was to split the word array into 2 seperate arrays: one that contained words where the first letters were uppercase, and another where the first letters were lowercase. Since the algorthim needed to have capital letters be greater than lower case letters, I used a modified version of selection sort where whenever it encounered a capital letter it added 33 to it. The ascii values of lowercase letters have a difference of 32 from there capital versions. Adding 33 to the capital versions ensure that they will still maintain an order that is sequential relative to other capital letters, yet at the same time it makes all capital letters greater than lowercase letters.


-----------------------------------------------------------------------------------------------------------------------------------
3.) Printing the sored array

At this stage in the algorithm there are two arrays sorted in ascending order: an array where the first letters are lowercase, and an array where the first letters are uppercase. Inorder to have have the words be in descending order, each array is added backwards to a final array. First the words from the uppercase array are transferred, then the words from the lowercase array. So the process would look like this:

uppercase sorted: [A, B, C]
lowercase sorted: [a, b, c]

finalList becomes: [C, B, A, c, b, a]

Then the finalList would be printed.



