# Dynamic Programming 
def question4(s, dictionary):

    n = len(s)

    # base case:
    t = [False] * (n + 1)
    t[0] = True # empty string is always valid. 

    nextWord = [0] * (n + 1)

    # Recurrence
    for i in range(1, n + 1):
        for j in range(1, i + 1):
            subString = s[j - 1:i] # Substring s[j,...,i]

            if dictionary.get(subString, False) and t[j - 1]:
                t[i] = True
                nextWord[j - 1] = i
                break # No need to search more for this i, cuz we found a valid split. 
    
    # Result
    if t[n]:
        print("The string s contains a valid sentence:")
        print(t[n])

        #Extract words back
        prev = 0
        words = []

        for i in nextWord:

            if i != 0:
                word = s[prev:i]
                words.append(word)
                prev = i
            
        print("The words in the sentence are:")
        print(words)
    
    else:
        print("The string s cant be reconstructed into valid words.")

# Test cases:

dictionary = {
    "it": True,
    "was": True,
    "the": True,
    "best": True,
    "of": True,
    "times": True,
    "pie": True,
    "apple": True,
    "pen": True,
    "applepen": True
}

s1 = "itwasthebestoftimes"
question4(s1, dictionary)

s2 = "applepenapple"
question4(s2, dictionary)

s3 = "catsanddog"
question4(s3, dictionary)

s4 = "applepie"
question4(s4, dictionary)
