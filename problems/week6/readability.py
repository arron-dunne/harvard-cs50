# Determine grade level needed for given text

import cs50
import re

# Get text from user
text = cs50.get_string('Text: ')

# Count number of letters, words and sentences
sentences = re.findall('[.!?]', text)
words = re.findall('^| ', text)
letters = re.findall('[a-zA-Z]', text)

# Calculate Coleman-Liau index
L = (len(letters) * 100) / len(words)
S = (len(sentences) * 100) / len(words)

i = round((0.0588 * L) - (0.296 * S) - 15.8)

# Print the grade
if i >= 16:
    print('Grade 16+')

elif i < 1:
    print('Before Grade 1')

else:
    print(f'Grade {i}')