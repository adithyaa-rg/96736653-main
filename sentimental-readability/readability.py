sentence=input("Text: ")
length=len(sentence)

sentences=[]
temp=0
for i in range(length):
    if sentence[i] in ['.','!','?']:
        sentences+=[sentence[temp:i]]
        temp=i+1

words=[]
len_sen=len(sentences)
for i in range(len_sen):
    words+=sentences[i].split()

letters=0
len_words=len(words)
for i in range(len_words):
    letters+=len(words[i])

L,S=100*letters/len_words,len_sen/len_words*100
readability=0.0588 * L - 0.296 * S - 15.8

if readability>=16:
    print("Grade 16+")
elif 1<=readability<16:
    print(f"Grade {int(readability)}")
else:
    print("Before Grade 1")