# Reading Level Calculator and Suggestions
The first document passed will be the base document. Its reading level will be calculated then compared to the list of other documents to find the most similar (in terms of reading level).
Each document that gets passed through the program goes through a series of steps.
1. Each document gets read and its words are counted and stemmed
2. Then words are given IDF values
3. Each docoument has its words TFIDF values computed
