import csv
import sys

argv=sys.argv
argc=len(argv)

def main(argc,argv):

    # TODO: Check for command-line usage
    if (argc!=3):
        print("Usage: python dna.py data.csv sequence.txt")
        exit()
    data_people={}
    csv_file=argv[1]

    data=[]
    # TODO: Read database file into a variable
    with open(csv_file,"r") as data_file:
        reader_data=csv.reader(data_file)

        for row in reader_data:
            if row[0]=='name':
                data+=row[1:]
            else:
                data_people[row[0]]=row[1:]

    sequence_data=argv[2]
    # TODO: Read DNA sequence file into a variable
    with open(sequence_data,'r') as seq_file:
        sequence=seq_file.read()

    # TODO: Find longest match of each STR in DNA sequence
    values=[]
    for i in data:
        values+=[str(longest_match(sequence,i))]

    for x,y in data_people.items():
        if y==values:
            print(x)


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main(argc,argv)
