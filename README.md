# Autofill_Demo

# This is a sort of proof of concept/demo of a word autofill feature.

There is a file provided with 1000 frequently used english words. These words and whatever the user types are stored in a data structure called a *Trie.*
The delimiter for the words that the user types is a space, so if the user types 'Hello, World', the program will store 'Hello,' and 'World' in the Trie.

Then the user can provide a prefix such as 'he' and all words in the trie beginning with 'he' will be output as options for autofill.

I made this as an exercise and to plan out the logic of implementing the Trie data structure. I intend to use this to create a text editor of sorts which will have this feature. 
